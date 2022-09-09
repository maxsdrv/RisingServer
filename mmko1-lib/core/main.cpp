#include <iostream>

#include "Actions.h"
#include "ControllerMode.h"



void test() {
	/* Example how to work Transmitting Message by MKO1 */
	uint16_t dataWords[2]{1,2};
	TestMmko test(UNMMKO1_BUS_A);
	test.Init();
	ControllerMode controller(test);
	auto res = controller.BusToTerminalReceive(0, 0, 0, nullptr);
}


int main(int argc, char *argv[])
{
	const std::string log_name {"../../core/logs/common_log.txt"}; //file for logging
	SFileLogger::getInstance().openLogFile(log_name);
	test();

	SFileLogger::getInstance().closeLogFile();

    return 0;
}
















