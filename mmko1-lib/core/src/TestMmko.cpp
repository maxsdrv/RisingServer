#include "TestMmko.h"
#include "ControllerMode.h"

TestMmko::TestMmko(BUSLINE line)
		:
		lineBus(line),
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
	if (Common::getInstance().status < 0) {
		Common::getInstance().processUnmbaseError();
		initStatus = false;
		return;
	}
	else if (unmmko1_init(Common::getInstance().resourceName,
			VI_TRUE, VI_TRUE, &Common::getInstance().session) < 0) {
		Common::getInstance().processUnmmkoError();
		initStatus = false;
	}
	unmmko1_connect(Common::getInstance().session,
			Common::getInstance().carrierSession, Common::getInstance().position,
			VI_TRUE, VI_TRUE);
	initStatus = true;
}
void TestMmko::SelfTest()
{
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
	if (!initStatus) {
		MKOTEXT("MKO is not activate ", getStatus(), getSession());
		return;
	}
	unmmko1_close(Common::getInstance().session);
	unmbase_close(Common::getInstance().carrierSession);

	initStatus = false;
}
int32 TestMmko::getStatus()
{
	return Common::getInstance().status;
}
BUSLINE TestMmko::getLine() const
{
	return lineBus;
}
uint32 TestMmko::getSession()
{
	return Common::getInstance().session;
}
bool TestMmko::isInit() const
{
	return !initStatus;
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




























