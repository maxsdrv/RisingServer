#include "TestMmko.h"

TestMmko::TestMmko(unmmko1_bus bus_)
		:
		lineBus(bus_),
		initStatus(false)
{

	MKOTEXT("TestMmko()");
}

TestMmko::~TestMmko() {
	initStatus = false;
	MKOTEXT("~TestMmko()");
}
void TestMmko::Init()
{
	Common::getInstance().status = Common::getInstance().search();
	try {
		Common::getInstance().processUnmbaseError();
		Common::getInstance().processUnmmkoError();
	}
    catch (MkoErrors& ex) {

		std::cerr << ex.what() << '\n';
	}
	unmmko1_init(Common::getInstance().resourceName,
			VI_TRUE, VI_TRUE, &Common::getInstance().session);

	unmmko1_connect(Common::getInstance().session,
			Common::getInstance().carrierSession, Common::getInstance().position,
			VI_TRUE, VI_TRUE);

	initStatus = true;
}
void TestMmko::SelfTest()
{
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

void TestMmko::CloseSession()
{
	unmmko1_close(Common::getInstance().session);
	unmbase_close(Common::getInstance().carrierSession);
	initStatus = false;
}
int32_t TestMmko::getStatus()
{
	return Common::getInstance().status;
}
unmmko1_bus TestMmko::getLine() const
{
	return lineBus;
}
uint32_t TestMmko::getSession()
{
	return Common::getInstance().session;
}
bool TestMmko::isInit() const
{
	return !initStatus;
}






















