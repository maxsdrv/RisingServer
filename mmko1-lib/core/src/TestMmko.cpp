#include "TestMmko.h"
#include "Actions.h"

TestMmko::TestMmko() :
			searchMko(std::make_unique<Common>())
{
}
TestMmko::~TestMmko() {
	MKOTEXT("~TestMmko()");
}
void TestMmko::InitialiseMezzanine()
{
	try {
		searchMko->getStatus();
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what() << '\n';
	}

	unmmko1_init(const_cast<char*>(searchMko->resourceName.c_str()),
			VI_TRUE, VI_TRUE, &searchMko->session);

	unmmko1_connect(searchMko->session, searchMko->carrierSession, searchMko->position,
			VI_TRUE, VI_TRUE);
}
void TestMmko::SelfTest()
{
	char message[256];
	int16_t resultCode{};
	unmmko1_self_test(searchMko->session, &resultCode, message);
	printf("Self-test result: %s (%d)\n", message, resultCode);
	SFileLogger::getInstance().writeToLog(resultCode, message);
}
void TestMmko::GetInfoMezz()
{
	char softwareVersion[256];
	char hardwareVersion[256];
	unmmko1_revision_query(searchMko->session, softwareVersion, hardwareVersion);
	std::cout << "Software version: " << softwareVersion << '\n' <<
			  "Hardware version: " << hardwareVersion << '\n';
}
void TestMmko::UnmkoTestExchange()
{

}
void TestMmko::TestMemory()
{

}
void TestMmko::CloseSession()
{

}
void TestMmko::MonitorConfigure()
{

}
