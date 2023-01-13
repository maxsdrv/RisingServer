#include <iomanip>
#include <boost/format.hpp>
#include <cstring>

#include "MainBus.h"
#include "ControllerMode.h"
#include "MonitorMode.h"
#include "AbonentMode.h"
#include "MMKOErrors.h"
#include "unmbase.h"


MainBus::MainBus() :
					position(0),
					status(0),
					m_Session(0),
					carrier_session(0)
{
	try {
		device_init();
	}
	catch (const MkoExceptions& ex) {
		std::cerr << ex.what();
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what();
	}
	std::cout << "MainBus()" << '\n';
}

MainBus::~MainBus() {
	close_session();
	std::cout << "~MainBus()" << '\n';
}
bool MainBus::self_test() {
	char message[256];
	int16_t resultCode{};
	status = MkoExceptions::check_functions("Mko self-test", m_Session, unmmko1_self_test,
			m_Session, &resultCode, message);
	std::cout << boost::format("Self-test result %s %d \n")%message%resultCode;
	return true;
}

void MainBus::close_session() const {
	std::cout << "MainBus close session" << '\n';
	unmbase_close(carrier_session);
	unmmko1_close(m_Session);
}
int32_t MainBus::get_mko_status() const {
	return status;
}
uint32_t MainBus::get_mko_session() const {
	return m_Session;
}
int32_t MainBus::search() {

	uint32_t resource_manager_session{};
	const std::string search_pattern{ "?*[0-9]?*::?*::INSTR" };
	uint32_t find_list{};
	int32_t found = VI_ERROR_RSRC_NFOUND;
	uint32_t index{}, count{};
	uint32_t device_session{};
	uint16_t interface_type{};
	int16_t mezzanine_number = 1;
	char address[256];
	const std::string id_str{ "*IDN?\n" };
	const std::string tab{ "%t" };

	/* Lambdas instead goto definitions in C implementation common.h */
	auto Error = [=]() {
	  if (resource_manager_session)
		  viClose(resource_manager_session);
	};
	auto CloseDevice = [=]() {
	  viClose(device_session);
	  if (VI_SUCCESS==found)
		  return;
	};

	//  Open Session with VISA
	if (viOpenDefaultRM(&resource_manager_session)<0)
		Error();

	// Find devices
	if (viFindRsrc(resource_manager_session, const_cast<char*>(search_pattern.c_str()), &find_list, &count, address)<0)
		Error();

	// Pass to all found devices
	for (index = 0; index<count; ++index) {
		// Devices not found
		if (index && viFindNext(find_list, address)<0)
			Error();

		// Open device
		if (viOpen(resource_manager_session, address, VI_NULL, VI_NULL, &device_session)<0)

			continue;

		// Read interface type
		viGetAttribute(device_session, VI_ATTR_INTF_TYPE, &interface_type);

		// Interface type VXI или GPIB-VXI
		if (VI_INTF_VXI==interface_type || VI_INTF_GPIB_VXI==interface_type) {
			ViUInt32 slot_number = 0;
			ViUInt16 manufactory_id = 0, model_code = 0;

			// Don't work in slot number 0
			if (viGetAttribute(device_session, VI_ATTR_SLOT, &slot_number)<0 || 0==slot_number)
				CloseDevice();

			// Request the manufacturer's identifier and device model code
			if (viGetAttribute(device_session, VI_ATTR_MANF_ID, &manufactory_id)<0)
				CloseDevice();
			if (viGetAttribute(device_session, VI_ATTR_MODEL_CODE, &model_code)<0)
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
		else if (VI_INTF_TCPIP==interface_type || VI_INTF_USB==interface_type || VI_INTF_GPIB==interface_type
				|| VI_INTF_ASRL==interface_type) {
			ViChar idn[256];

			if (viLock(device_session, VI_EXCLUSIVE_LOCK, 2000, nullptr, nullptr)<0)
				CloseDevice();

			status = viQueryf(device_session, const_cast<char*>(id_str.c_str()),
					const_cast<char*>(tab.c_str()), idn);
			viUnlock(device_session);

			if (status<0)
				CloseDevice();

			if (0!=strncmp(idn, UNMBASE_MEZABOX_IDN, strlen(UNMBASE_MEZABOX_IDN)))
				CloseDevice();
		}

		// Initialise Carrier Mezzanine and read code of mezzanines
		if (unmbase_init(address, VI_ON, VI_ON, &carrier_session)<0)
			CloseDevice();

		for (mezzanine_number = 1; mezzanine_number<=8; ++mezzanine_number) {
			ViInt16 present, model_code;
			if (unmbase_m_type_q(carrier_session, mezzanine_number, &present, &model_code)<0 || 0==present)
				continue;

			if (UNMMKO1_MODEL_CODE==(model_code & 0x0fff)) {
				strcpy(resource_name, address);
				position = (ViUInt16)mezzanine_number;
				found = VI_SUCCESS;
				break;
			}
		}

		unmbase_close(carrier_session);

	}

	if (VI_SUCCESS==found)
		std::cout << "Mezzanine MKO found at "
				  << resource_name << "on " << position << '\n';
	status = found;

	return status;
}
void MainBus::device_init() {
	status = MkoExceptions::check_functions("Search MKO", m_Session, search()); // Search MKO
	MkoExceptions::check_functions("Mbase init", m_Session, unmbase_init, resource_name,
			true, true, &carrier_session);
	MkoExceptions::check_functions("Mko init", m_Session, unmmko1_init, resource_name, true,
			true, &m_Session);
	MkoExceptions::check_functions("Mko connect", m_Session, unmmko1_connect, m_Session,
			carrier_session, position, true, true); // Connect to MKO*/
}

ControllerMode* MainBus::create_controller(BUSLINE bus_line) {
	auto* res = create_mode<ControllerMode>(this, bus_line);
	if (res != nullptr)
		return res;
	else
		throw MkoExceptions(status, "Error create controller");
}
MonitorMode* MainBus::create_monitor() {
	monitor = std::unique_ptr<MonitorMode>(new MonitorMode(this));
	return monitor.get();
}

AbonentMode* MainBus::create_abonent(BUSLINE bus_line, uint32_t address) {
	auto* res = create_mode<AbonentMode>(this, bus_line, address);
	if (res != nullptr)
		return res;
	else
		throw MkoExceptions(status, "Error create abonent");
}

void MainBus::reset(uint32_t session) const{
	MkoExceptions::check_functions("Reset MKO", m_Session, unmmko1_reset(session));
}
void MainBus::remove_controller(BUSLINE bus_line) {
	const auto itr = controllers.find(bus_line);
	if (itr != controllers.end()) {
		controllers.erase(itr);
	}
}
void MainBus::remove_abonent(BUSLINE bus_line, uint32_t address) {
	const auto itr = terminal_devices.find(bus_line);
	if (itr != terminal_devices.end()) {
		if (itr->second->get_address() == address) {
			terminal_devices.erase(itr);
		}
	}
}
void MainBus::remove_monitor() {
	monitor.reset();
}





