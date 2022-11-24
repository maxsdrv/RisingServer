#include <iostream>

#include "ControllerMode.h"
#include "MonitorMode.h"
#include "MMKOErrors.h"

void test()
{
	/* Example how to work Transmitting Message by MKO1 */
	uint16_t dataWords[5]{ 1, 2, 3, 4, 5 };
	auto test = std::make_unique<Mmko>(UNMMKO1_BUS_A);
	/*const std::vector<std::unique_ptr<unmmko1_message>>& v =
			test->addMonitor()->PullMessage();*/
}


int main(int argc, char* argv[])
{
	/*const std::string log_name{ "../../core/logs/common_log.txt" }; //file for logging
	SFileLogger::getInstance().openLogFile(log_name);

	SFileLogger::getInstance().closeLogFile();*/

	test();

	return 0;
}
















