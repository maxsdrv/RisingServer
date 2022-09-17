#include "TestMmko.h"
#include "ControllerMode.h"


TestMmko::TestMmko(BUSLINE line) : lineBus(line)
{
	MkoText("TestMmko()");
	auto errStatus = Common::getInstance().search();
	BaseInit(MkoEnums::DeviceNames::CarrierMezzanine);

	try {
		if (errStatus < 0) {
            auto errMsg = MkoErrors::ErrorMessage(getMkoSession(), &unmmko1_error_message);
            throw MkoErrors("Error config MKO is not found, " + std::get<0>(errMsg), std::get<1>(errMsg));
		}
		if (unmbase_init(Common::getInstance().resourceName, VI_ON, VI_ON,
				&Common::getInstance().carrierSession) < 0){
			auto errMsg = MkoErrors::ErrorMessage(getCarrierSession(), &unmmko1_error_message);
			throw MkoErrors("Error initialisation of carrier mezzanine " +
			std::get<0>(errMsg), std::get<1>(errMsg));
		}
		if (unmmko1_init
				(Common::getInstance().resourceName, VI_ON, VI_ON,
						&Common::getInstance().session) < 0) {
			throw MkoErrors("Error MKO initialisation ", static_cast<int>(Common::getInstance().session));
		}
		if (unmmko1_connect
				(Common::getInstance().session, Common::getInstance().carrierSession,
						Common::getInstance().position,
						VI_TRUE, VI_TRUE) < 0) {
			throw MkoErrors("Error connection to MKO ", static_cast<int>(Common::getInstance().session));
		}
	}
	catch(MkoErrors& ex) {
		Common::getInstance().status = errStatus;
		CloseSession();
		ex.what();
		throw;
	}

}

TestMmko::~TestMmko() {
	MkoText("~TestMmko()");
}
void TestMmko::SelfTest()
{
	// TODO It was copied from common.h, should rewrite for C++
	char message[256];
	int16 resultCode{};
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

void TestMmko::CloseSession()
{
	unmbase_close(getCarrierSession());
	unmmko1_close(getMkoSession());
}
int32 TestMmko::getStatus()
{
	return Common::getInstance().status;
}
BUSLINE TestMmko::getLine() const
{
	return lineBus;
}
uint32 TestMmko::getCarrierSession()
{
	return Common::getInstance().carrierSession;
}
uint32 TestMmko::getMkoSession()
{
	return Common::getInstance().session;
}
ControllerMode* TestMmko::addController(const uint16& rxtx, int options)
{
	return add<ControllerMode, uint16, int>(rxtx, options);
}
template<class T, class TBit, class TOptions>
std::shared_ptr<T>& TestMmko::insertObject(const TBit& rt, TOptions options)
{
	return controllers =
			std::shared_ptr<ControllerMode>(new ControllerMode(this, rt, options));
}
bool TestMmko::BaseInit(MkoEnums::DeviceNames md)
{



	return false;
}





























