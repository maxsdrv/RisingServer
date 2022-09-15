#include <iostream>

#include "Actions.h"
#include "ControllerMode.h"
#include "MkoErrors.h"


void test() {
	/* Example how to work Transmitting Message by MKO1 */
	uint16_t dataWords[5]{1, 2, 3, 4, 5};
	try {
		auto test = std::make_unique<TestMmko>(UNMMKO1_BUS_A);
	}
	catch (MkoErrors& er) {
		std::cerr << er.what();
	}

	/*auto testInstance = test->addController(0, 0);
	testInstance->transmitCmdF1(RT_3, SA_2, 5, dataWords);
	test->CloseSession();*/


//	TestMmko test(UNMMKO1_BUS_A);
//	test.Init();
	/*ControllerMode controller(test);
	controller.transmitCmdF1(RT_3, SA_2, 5, dataWords);*/
//	test.CloseSession();
}


int main(int argc, char *argv[])
{
	const std::string log_name {"../../core/logs/common_log.txt"}; //file for logging
	SFileLogger::getInstance().openLogFile(log_name);
	test();

	SFileLogger::getInstance().closeLogFile();

    return 0;
}
















