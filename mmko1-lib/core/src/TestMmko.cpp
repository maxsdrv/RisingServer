#include "TestMmko.h"

bool TestMmko::statusInit = false;

TestMmko::TestMmko(unmmko1_bus bus_) :
									bus(bus_),
                                    common(std::make_unique<Common>())
{
	MKOTEXT("TestMmko()");
}

TestMmko::~TestMmko() {
	MKOTEXT("~TestMmko()");
	statusInit = false;
}
void TestMmko::Init()
{
	try {
		common->getStatus();
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what() << '\n';
	}

	unmmko1_init(common->resourceName,
			VI_TRUE, VI_TRUE, &common->session);

	unmmko1_connect(common->session, common->carrierSession, common->position,
			VI_TRUE, VI_TRUE);

	statusInit = true;
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

void TestMmko::Close()
{
	unmmko1_close(common->session);
	unmbase_close(common->carrierSession);

}
uint16_t TestMmko::PackCw(uint16_t address, uint16_t RxTx, uint16_t subAddress, uint16_t wordCount)
{
	return unmmko1_pack_cw(address, RxTx, subAddress, wordCount);
}
void TestMmko::setBus(unmmko1_bus bus_)
{
	bus = bus_;
}
unmmko1_bus TestMmko::getBus() const
{
	return bus;
}
bool TestMmko::isInit() const
{
	return statusInit > 0;
}
















