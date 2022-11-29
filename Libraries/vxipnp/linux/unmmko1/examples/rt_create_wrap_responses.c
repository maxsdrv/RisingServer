#include "common.h"

int main() {
    ViStatus status = VI_SUCCESS;
    unmkocheck(search_unmmko1(resource_name, &position));

    unmbasecheck(unmbase_init(resource_name, VI_TRUE, VI_TRUE, &carrier_session));
    unmkocheck(unmmko1_init(resource_name, VI_TRUE, VI_TRUE, &session));
    unmkocheck(unmmko1_connect(session, carrier_session, position, VI_TRUE, VI_TRUE));

    // Настраиваем оконечное устройство с адресами 0
    unmkocheck(unmmko1_rt_configure(session, 1 << RT_0, UNMMKO1_RT_TRANSFORM | UNMMKO1_RT_BUS_A_AND_B | UNMMKO1_RT_DEFAULT_RESPONSES));

    // Устанавливаем режим циклического возврата данных для 30 подадреса
    unmkocheck(unmmko1_rt_set_subaddress_options(session, RT_0, SA_30, UNMMKO1_RT_SUBADDRESS_WRAP));

    unmkocheck(unmmko1_rt_start(session));

    printf("Press a key to continue\n");
    while (!key_pressed())
        Sleep(1);

    unmkocheck(unmmko1_rt_stop(session));

    unmkocheck(unmmko1_close(session));
    unmbasecheck(unmbase_close(carrier_session));

    return status;
}
