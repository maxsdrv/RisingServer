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
	catch (MMKOErrors& ex)
	{
		std::cerr << ex.what();
		CloseSession();
		throw;
	}
	Common::getInstance().status = mkoStatus;
}

Mmko::~Mmko()
{
	MkoText("MMKOInterfacerface()");
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
ControllerMode* Mmko::addController(const uint16_t& rxtx)
{
	return add<ControllerMode, uint16_t>(rxtx);
}
template<class T, class TBit>
std::shared_ptr<T>& Mmko::insertObject(const TBit& rt)
{
	return controllers =
			std::shared_ptr<ControllerMode>(new ControllerMode(this, rt));
}
void Mmko::DeviceInit()
{
	mkoStatus = Common::getInstance().search();
	if (mkoStatus < 0)
	{
		auto errMsg = MMKOErrors::ErrorMessage(getMkoSession(), &unmmko1_error_message);
		throw MMKOErrors("Error config MKO is not found, " + std::get<0>(errMsg), std::get<1>(errMsg));
	}
	if (unmbase_init(Common::getInstance().resourceName, true, true,
			&Common::getInstance().carrierSession) < 0)
	{
		auto errMsg = MMKOErrors::ErrorMessage(Common::getInstance().carrierSession,
				&unmmko1_error_message);
		throw MMKOErrors("Unmbase activate error" + std::get<0>(errMsg),
				std::get<1>(errMsg));
	}
	if (unmmko1_init(Common::getInstance().resourceName, true, true,
			&Common::getInstance().session) < 0)
	{
		auto errMsg = MMKOErrors::ErrorMessage(Common::getInstance().session,
				&unmmko1_error_message);
		throw MMKOErrors("Unmmko1 activate error" + std::get<0>(errMsg),
				std::get<1>(errMsg));
	}
	if (unmmko1_connect
			(Common::getInstance().session, Common::getInstance().carrierSession,
					Common::getInstance().position,
					VI_TRUE, VI_TRUE) < 0)
	{
		auto errMsg = MMKOErrors::ErrorMessage(Common::getInstance().session, &unmmko1_error_message);
		throw MMKOErrors("Unmmko1 connect error " + std::get<0>(errMsg), std::get<1>(errMsg));
	}
}
MonitorMode* Mmko::addMonitor()
{
	monitor = std::unique_ptr<MonitorMode>(new MonitorMode(this));
	return getMonitor();
}
MonitorMode* Mmko::getMonitor() const
{
	return monitor.get();
}

AbonentMode* Mmko::addAbonent(uint32_t address) {
	abonent = std::unique_ptr<AbonentMode>
	        (new AbonentMode(this, address));
}



























