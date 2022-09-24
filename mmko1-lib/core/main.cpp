#include <iostream>

#include "Actions.h"
#include "ControllerMode.h"
#include "MonitorMode.h"
#include "MkoErrors.h"

void test()
{
	/* Example how to work Transmitting Message by MKO1 */
	uint16_t dataWords[5]{ 1, 2, 3, 4, 5 };
	auto test = std::make_unique<TestMmko>(UNMMKO1_BUS_A);

}

int main(int argc, char* argv[])
{
	const std::string log_name{ "../../core/logs/common_log.txt" }; //file for logging
	SFileLogger::getInstance().openLogFile(log_name);
	test();

	SFileLogger::getInstance().closeLogFile();

	return 0;
}
















