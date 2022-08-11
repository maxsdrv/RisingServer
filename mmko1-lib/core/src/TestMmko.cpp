
#include "TestMmko.h"
#include "Actions.h"


TestMmko::TestMmko() : searchMko(std::make_unique<Common>()),
					   statusInit(false)
{
}
TestMmko::~TestMmko() {
	MKOTEXT("~TestMmko()");
	statusInit = false;
}
void TestMmko::Init()
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

	statusInit = true;
}
void TestMmko::SelfTest()
{
	char message[256];
	int16_t resultCode{};
	char softwareVersion[256];
	char hardwareVersion[256];

	unmmko1_self_test(searchMko->session, &resultCode, message);
	printf("Self-test result: %s (%d)\n", message, resultCode);
	SFileLogger::getInstance().writeToLog(resultCode, message);

	unmmko1_revision_query(searchMko->session, softwareVersion, hardwareVersion);
	std::cout << "Software version: " << softwareVersion << '\n' <<
			  "Hardware version: " << hardwareVersion << '\n';

	unmmko1_test_exchange(searchMko->session, &resultCode, message);
	printf("Exchange test result: %s (%d)\n", message, resultCode);

	unmmko1_test_memory(searchMko->session, &resultCode, message);
	printf("Memory test result: %s (%d)\n", message, resultCode);
}

void TestMmko::Close()
{
	unmmko1_close(searchMko->session);
	unmbase_close(searchMko->carrierSession);
}
int32_t TestMmko::MonitorConfigure()
{
	uint32_t messages_count{0};
	unmmko1_message* msg{nullptr};

	if (!statusInit)
		Init();

	unmmko1_mon_configure(searchMko->session, UNMMKO1_MON_TRANSFORM | UNMMKO1_MON_BUS_A_AND_B);
	unmmko1_mon_start(searchMko->session);

	/*std::cout << "Press a key to continue\n";
	while (!key_pressed())
		Sleep(1);*/
	unmmko1_mon_stop(searchMko->session);
	unmmko1_mon_messages_count(searchMko->session, &messages_count);

	auto messages = std::make_unique<unmmko1_message>(); //allocate memory for struct unmmko1_message
	unmmko1_mon_messages_read(searchMko->session, messages_count,
			messages.get(), &messages_count);
	Common::printMessages(messages_count, messages.get());

	return searchMko->status;
}
int32_t TestMmko::SendMessage(const std::vector<uint16_t>& words)
{
	return 0;
}








