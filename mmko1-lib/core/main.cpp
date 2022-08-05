#include <iostream>

#include "aik_unmmko.h"
#include "common.h"


int main(int argc, char *argv[])
{
    std::cout << "Test MMKO1: " << std::endl;

    ViStatus status = VI_SUCCESS;
    ViChar software_version[256];
    ViChar hardware_version[256];
    ViInt16 result_code;
    ViChar message[256];

	auto su = std::make_unique<SearchUnmmko>(resource_name, &position);
	unmkocheck(su.get()->search());
    unmbasecheck(unmbase_init(resource_name, VI_TRUE, VI_TRUE, &carrier_session));
    unmkocheck(unmmko1_init(resource_name, VI_TRUE, VI_TRUE, &session));
    unmkocheck(unmmko1_connect(session, carrier_session, position, VI_TRUE, VI_TRUE));

    // Информация о мезонине
    unmkocheck(unmmko1_revision_query(session, software_version, hardware_version));
    printf("Software version: %s\n", software_version);
    printf("Hardware version: %s\n", hardware_version);
    // Проводим самоконтроль мезонина
    unmkocheck(unmmko1_self_test(session, &result_code, message));
    printf("Selftest result: %s (%d)\n", message, result_code);

    // Проводим тест обмена
    unmkocheck(unmmko1_test_exchange(session, &result_code, message));
    printf("Exchange test result: %s (%d)\n", message, result_code);

    // Проводим тест памяти
    unmkocheck(unmmko1_test_memory(session, &result_code, message));
    printf("Memory test result: %s (%d)\n", message, result_code);

    unmkocheck(unmmko1_close(session));
    unmbasecheck(unmbase_close(carrier_session));

    return 0;
}
















