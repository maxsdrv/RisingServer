#include "TestMmko.h"

TestMmko::TestMmko(unmmko1_bus bus_)
		:
		lineBus(bus_),
		common(std::make_unique<Common>()),
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
	common->status = common->search();
	try {
		common->processUnmbaseError();
		common->processUnmmkoError();
	}
    catch (MkoErrors& ex) {

		std::cerr << ex.what() << '\n';
	}
	unmmko1_init(common->resourceName,
			VI_TRUE, VI_TRUE, &common->session);

	unmmko1_connect(common->session, common->carrierSession, common->position,
			VI_TRUE, VI_TRUE);

	initStatus = true;
}
void TestMmko::SelfTest()
{
	char message[256];
	int16_t resultCode{};
	char softwareVersion[256];
	char hardwareVersion[256];

	unmmko1_self_test(common->session, &resultCode, message);
	printf("Self-test result: %s (%d)\n", message, resultCode);
	SFileLogger::getInstance().writeToLog(resultCode, message);

	unmmko1_revision_query(common->session, softwareVersion, hardwareVersion);
	std::cout << "Software version: " << softwareVersion << '\n' <<
			  "Hardware version: " << hardwareVersion << '\n';

	unmmko1_test_exchange(common->session, &resultCode, message);
	printf("Exchange test result: %s (%d)\n", message, resultCode);

	unmmko1_test_memory(common->session, &resultCode, message);
	printf("Memory test result: %s (%d)\n", message, resultCode);
}

void TestMmko::CloseSession()
{
	unmmko1_close(common->session);
	unmbase_close(common->carrierSession);
	initStatus = false;
}
int32_t TestMmko::getStatus() const
{
	return common->status;
}
unmmko1_bus TestMmko::getLine() const
{
	return lineBus;
}
uint32_t TestMmko::getSession() const
{
	return common->session;
}
bool TestMmko::isInit() const
{
	return !initStatus;
}






















