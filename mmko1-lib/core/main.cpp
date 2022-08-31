#include <iostream>

#include "AikUnmmko.h"
#include "Actions.h"
#include "TestMmko.h"
#include "ControllerMode.h"



void testPol() {
	/*ITestMmko* test = new TestMmko(UNMMKO1_BUS_A);
	test->Init();
	test->SelfTest();
	test->Close();
	delete test;*/
}




int main(int argc, char *argv[])
{
	const std::string log_name {"../../core/logs/common_log.txt"}; //file for logging
	SFileLogger::getInstance().openLogFile(log_name);
	testPol();

    /*unmbasecheck(unmbase_init(resource_name, VI_TRUE, VI_TRUE, &carrier_session));
    unmkocheck(unmmko1_init(resource_name, VI_TRUE, VI_TRUE, &session));
    unmkocheck(unmmko1_connect(session, carrier_session, position, VI_TRUE, VI_TRUE));

    // Информация о мезонине
    unmkocheck(unmmko1_revision_query(session, software_version, hardware_version));
    printf("Software version: %s\n", software_version);
    printf("Hardware version: %s\n", hardware_version);*/

   /*unmkocheck(unmmko1_close(session));
    unmbasecheck(unmbase_close(carrier_session));*/

	SFileLogger::getInstance().closeLogFile();

    return 0;
}
















