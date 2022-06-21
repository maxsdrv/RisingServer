#include "common.h"

static ViUInt16 data_words[32] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32};

int main() {
    ViStatus status = VI_SUCCESS;
    unmkocheck(search_unmmko1(resource_name, &position));

    unmbasecheck(unmbase_init(resource_name, VI_TRUE, VI_TRUE, &carrier_session));
    unmkocheck(unmmko1_init(resource_name, VI_TRUE, VI_TRUE, &session));
    unmkocheck(unmmko1_connect(session, carrier_session, position, VI_TRUE, VI_TRUE));

    // Настраиваем оконечные устройства с адресами 0 и 1
    // Оконечные устройства, настроенные с опцией UNMMKO1_RT_CUSTOM_RESPONSES, будут отвечать только
    // на обращения к тем подадресам, для которых непосредственно установлены слова данных
    unmkocheck(unmmko1_rt_configure(session, (1 << RT_0) | (1 << RT_1), UNMMKO1_RT_TRANSFORM | UNMMKO1_RT_BUS_A_AND_B | UNMMKO1_RT_CUSTOM_RESPONSES));

    // Оконечные устройства будут отвечать только на обращения к 1 и 30 подадресам
    unmkocheck(unmmko1_rt_set_subaddress_data(session, RT_0, SA_1,  32, data_words));
    unmkocheck(unmmko1_rt_set_subaddress_data(session, RT_0, SA_30, 32, data_words));
    unmkocheck(unmmko1_rt_set_subaddress_data(session, RT_1, SA_1,  32, data_words));
    unmkocheck(unmmko1_rt_set_subaddress_data(session, RT_1, SA_30, 32, data_words));

    unmkocheck(unmmko1_rt_start(session));

    printf("Press a key to continue\n");
    while (!key_pressed())
        Sleep(1);

    unmkocheck(unmmko1_rt_stop(session));

    unmkocheck(unmmko1_close(session));
    unmbasecheck(unmbase_close(carrier_session));

    return status;
}
