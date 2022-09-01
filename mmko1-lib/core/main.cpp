#include <iostream>

#include "Actions.h"
#include "ITestMmko.h"
#include "ControllerMode.h"



void testPol() {
	auto controller = Object::CreateDefaultObject<ControllerMode>();
	controller->BaseTransmitCmd(0, 0, 0);
}


int main(int argc, char *argv[])
{
	const std::string log_name {"../../core/logs/common_log.txt"}; //file for logging
	SFileLogger::getInstance().openLogFile(log_name);
	testPol();

	SFileLogger::getInstance().closeLogFile();

    return 0;
}
















