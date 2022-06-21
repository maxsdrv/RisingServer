#include "common.h"

static ViUInt16 data_words_3[3] = {0x03, 0x03, 0x03};
static ViUInt16 data_words_9[9] = {0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9};
static ViUInt16 data_words_32[32] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32};

int main() {
    ViStatus status = VI_SUCCESS;
    unmkocheck(search_unmmko1(resource_name, &position));

    unmbasecheck(unmbase_init(resource_name, VI_TRUE, VI_TRUE, &carrier_session));
    unmkocheck(unmmko1_init(resource_name, VI_TRUE, VI_TRUE, &session));
    unmkocheck(unmmko1_connect(session, carrier_session, position, VI_TRUE, VI_TRUE));

    // Настраиваем оконечные устройства с адресами 0, 2 и 3
    // Оконечные устройства, настроенные с опцией UNMMKO1_RT_DEFAULT_RESPONSES, инициализируют слова данных нулями для всех подадресов
    unmkocheck(unmmko1_rt_configure(session, (1 << RT_0) | (1 << RT_2) | (1 << RT_3), UNMMKO1_RT_TRANSFORM | UNMMKO1_RT_BUS_A_AND_B | UNMMKO1_RT_DEFAULT_RESPONSES));

    // Изменяем слова данных для оконечных устройств
    unmkocheck(unmmko1_rt_set_subaddress_data(session, RT_0, SA_1, 3, data_words_3));
    unmkocheck(unmmko1_rt_set_subaddress_data(session, RT_0, SA_2, 9, data_words_9));
    unmkocheck(unmmko1_rt_set_subaddress_data(session, RT_2, SA_2, 9, data_words_9));
    unmkocheck(unmmko1_rt_set_subaddress_data(session, RT_3, SA_1, 32, data_words_32));

    unmkocheck(unmmko1_rt_start(session));

    printf("Press a key to continue\n");
    while (!key_pressed())
        Sleep(1);

    unmkocheck(unmmko1_rt_stop(session));

    unmkocheck(unmmko1_close(session));
    unmbasecheck(unmbase_close(carrier_session));

    return status;
}
