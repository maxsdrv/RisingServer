#include <iostream>

#include "Actions.h"
#include "ITestMmko.h"
#include "ControllerMode.h"



void testPol() {
	/* Example how to work Transmitting Message by MKO1 */
	uint16_t dataWords[2]{1,2};
	auto test = Object::CreateDefaultObject<TestMmko>(UNMMKO1_BUS_A);
	auto controller = Object::CreateDefaultObject<ControllerMode>();
	test->Init();
	test->SelfTest();
	controller->baseTransmitCmd(0, 0, 1, dataWords);
	test->Close();
}


int main(int argc, char *argv[])
{
	const std::string log_name {"../../core/logs/common_log.txt"}; //file for logging
	SFileLogger::getInstance().openLogFile(log_name);
	testPol();

	SFileLogger::getInstance().closeLogFile();

    return 0;
}
















