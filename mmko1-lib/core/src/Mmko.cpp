#include <iomanip>

#include "Mmko.h"
#include "ControllerMode.h"
#include "MonitorMode.h"
#include "AbonentMode.h"

Mmko::Mmko(BUSLINE line)
		:lineBus(line)
{
	MkoText("Mmko()");
	try
	{
		DeviceInit();
	}
	catch (const MkoExceptions& ex)
	{
		std::ios state(nullptr);
		state.copyfmt(std::cerr);
		std::cerr << ex.what() << std::endl;
		std::cerr << "Error code: 0x" << std::hex << std::uppercase << std::setw(8) << std::setfill('0')
			<< ex.GetError() << std::endl;
		std::cerr.copyfmt(state);
	}
}

Mmko::~Mmko()
{
	CloseSession();
	MkoText("MMKOInterface()");
}
void Mmko::SelfTest()
{
	// TODO It was copied from common.h, should rewrite for C++
	char message[256];
	int16_t resultCode{};
	char softwareVersion[256];
	char hardwareVersion[256];

	unmmko1_self_test(Common::getInstance().session, &resultCode, message);
	printf("Self-test result: %s (%d)\n", message, resultCode);
	SFileLogger::getInstance().writeToLog(resultCode, message);

	unmmko1_revision_query(Common::getInstance().session, softwareVersion, hardwareVersion);
	std::cout << "Software version: " << softwareVersion << '\n' <<
			  "Hardware version: " << hardwareVersion << '\n';

	unmmko1_test_exchange(Common::getInstance().session, &resultCode, message);
	printf("Exchange test result: %s (%d)\n", message, resultCode);

	unmmko1_test_memory(Common::getInstance().session, &resultCode, message);
	printf("Memory test result: %s (%d)\n", message, resultCode);
}

void Mmko::CloseSession()
{
	std::cout << "Called close session in Mmko class " << std::endl;
	unmbase_close(getCarrierSession());
	unmmko1_close(getMkoSession());
}
int32_t Mmko::getStatus()
{
	return Common::getInstance().status;
}
BUSLINE Mmko::getLine() const
{
	return lineBus;
}
uint32_t Mmko::getCarrierSession()
{
	return Common::getInstance().carrierSession;
}
uint32_t Mmko::getMkoSession()
{
	return Common::getInstance().session;
}

/*template<class T, class TBit>
std::shared_ptr<T>& Mmko::insertObject(const TBit& rt)
{
	return controllers =
			std::shared_ptr<ControllerMode>(new ControllerMode(this, rt));
}*/
int32_t search(StateMko* state)
{
	MkoText("Debug information about search MKO");

	uint32_t resourceManagerSession {};
	const std::string searchPattern{"?*[0-9]?*::?*::INSTR"};
	uint32_t findList {};
	int32_t found = VI_ERROR_RSRC_NFOUND;
	uint32_t index {}, count {};
	uint32_t deviceSession {};
	uint16_t interfaceType {};
	int16_t mezzanineNumber = 1;
	char address[256];
	const std::string idStr{"*IDN?\n"};
	const std::string tab{"%t"};

	/* Lambdas instead goto definitions in C implementation common.h */
	auto Error = [=]() {
	  if (resourceManagerSession)
		  viClose(resourceManagerSession);
	};
	auto CloseDevice = [=]() {
	  viClose(deviceSession);
	  if (VI_SUCCESS == found)
		  return;
	};

	//  Open Session with VISA
	if (viOpenDefaultRM(&resourceManagerSession) < 0)
		Error();

	// Find devices
	if (viFindRsrc(resourceManagerSession, const_cast<char*>(searchPattern.c_str()), &findList, &count, address)<0)
		Error();

	// Pass to all found devices
	for (index = 0; index<count; ++index) {
		// Devices not found
		if (index && viFindNext(findList, address)<0)
			Error();

		// Open device
		if (viOpen(resourceManagerSession, address, VI_NULL, VI_NULL, &deviceSession)<0)
			continue;

		// Read interface type
		viGetAttribute(deviceSession, VI_ATTR_INTF_TYPE, &interfaceType);

		// Interface type VXI или GPIB-VXI
		if (VI_INTF_VXI==interfaceType || VI_INTF_GPIB_VXI==interfaceType) {
			ViUInt32 slot_number = 0;
			ViUInt16 manufactory_id = 0, model_code = 0;

			// Don't work in slot number 0
			if (viGetAttribute(deviceSession, VI_ATTR_SLOT, &slot_number)<0 || 0==slot_number)
				CloseDevice();

			// Request the manufacturer's identifier and device model code
			if (viGetAttribute(deviceSession, VI_ATTR_MANF_ID, &manufactory_id)<0)
				CloseDevice();
			if (viGetAttribute(deviceSession, VI_ATTR_MODEL_CODE, &model_code)<0)
				CloseDevice();

			//Compare ID with ID any version Carriers Mezzanines
			if (UN_MANUFACTURER_ID!=manufactory_id)
				CloseDevice();

			model_code &= 0x0fff;
			if (UNMBASE_MODEL_CODE!=model_code && UNMBASEU_MODEL_CODE!=model_code
					&& UNMBASE_MODEL_ARMVXI!=model_code)
				CloseDevice();
		}
			//Interface type VXI or GPIB-VXI
		else if (VI_INTF_TCPIP==interfaceType || VI_INTF_USB==interfaceType || VI_INTF_GPIB==interfaceType
				|| VI_INTF_ASRL==interfaceType) {
			ViChar idn[256];

			if (viLock(deviceSession, VI_EXCLUSIVE_LOCK, 2000, nullptr, nullptr)<0)
				CloseDevice();

			state->status = viQueryf(deviceSession, const_cast<char*>(idStr.c_str()),
					const_cast<char*>(tab.c_str()), idn);
			viUnlock(deviceSession);

			if (state->status < 0)
				CloseDevice();

			if (0!=strncmp(idn, UNMBASE_MEZABOX_IDN, strlen(UNMBASE_MEZABOX_IDN)))
				CloseDevice();
		}

		// Initialise Carrier Mezzanine and read code of mezzanines
		if (unmbase_init(address, VI_ON, VI_ON, &state->carrierSession) < 0)
			CloseDevice();

		for (mezzanineNumber = 1; mezzanineNumber<=8; ++mezzanineNumber) {
			ViInt16 present, model_code;
			if (unmbase_m_type_q(state->carrierSession, mezzanineNumber, &present, &model_code)<0 || 0==present)
				continue;

			if (UNMMKO1_MODEL_CODE==(model_code & 0x0fff)) {
				strcpy(state->resourceName, address);
				state->position = (ViUInt16)mezzanineNumber;
				found = VI_SUCCESS;
				break;
			}
		}

		unmbase_close(state->carrierSession);

	}

	if (VI_SUCCESS == found)
		  std::cout << "Mezzanine MKO found at "
					   << state->resourceName << "on " << state->position << '\n';
	state->status = found;

	return found;
}
void Mmko::DeviceInit()
{
	m_State = std::make_unique<StateMko>();
	ThrowErrorIf(search(m_State.get()) < 0, m_State->session, m_State->status, ErDevices::UNMMKO); // Search Mko device
	ThrowErrorIf(unmbase_init(m_State->resourceName, true, true, &m_State->carrierSession) < 0,
			m_State->session, m_State->status, ErDevices::UNMBASE); // Initialization Mezzanine Carrier
	ThrowErrorIf(unmmko1_init(m_State->resourceName, true, true, &m_State->session) < 0,
			m_State->session, m_State->status, ErDevices::UNMMKO);	// Initialization Mezzanine Mko
	ThrowErrorIf(unmmko1_connect(m_State->session, m_State->carrierSession, m_State->position,
			true, true) < 0, m_State->session, m_State->status, ErDevices::UNMMKO);	// Connect to Mko
}
MonitorMode* Mmko::addMonitor()
{
	monitor = std::unique_ptr<MonitorMode>(new MonitorMode(this));
	return monitor.get();
}

AbonentMode* Mmko::addAbonent(uint32_t address) {
	abonent = std::unique_ptr<AbonentMode>(new AbonentMode(this, address));
	return abonent.get();
}
ControllerMode* Mmko::addController(int bcOptions)
{
	controllers = std::unique_ptr<ControllerMode>(new ControllerMode(this, bcOptions));
	return controllers.get();
}















