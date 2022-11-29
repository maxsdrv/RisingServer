#include "common.h"

static ViUInt16 data_words_count = 256;
static ViUInt16* data_words = NULL;

int main() {
    ViStatus status = VI_SUCCESS;
    ViUInt16 index = 0;
    unmkocheck(search_unmmko1(resource_name, &position));

    unmbasecheck(unmbase_init(resource_name, VI_TRUE, VI_TRUE, &carrier_session));
    unmkocheck(unmmko1_init(resource_name, VI_TRUE, VI_TRUE, &session));
    unmkocheck(unmmko1_connect(session, carrier_session, position, VI_TRUE, VI_TRUE));

    // Настраиваем оконечное устройство с адресами 0
    unmkocheck(unmmko1_rt_configure(session, 1 << RT_0, UNMMKO1_RT_TRANSFORM | UNMMKO1_RT_BUS_A_AND_B | UNMMKO1_RT_DEFAULT_RESPONSES));

    // Создаём массив слов данных
    data_words = (ViUInt16*)calloc(data_words_count, sizeof(ViUInt16));
    for (index = 0; index < data_words_count; ++index)
        data_words[index] = index + 1;

    // Устанавливаем режим очереди и слова данных для 1 и 3 подадресов
    unmkocheck(unmmko1_rt_set_subaddress_options(session, RT_0, SA_1, UNMMKO1_RT_SUBADDRESS_QUEUE));
    unmkocheck(unmmko1_rt_set_subaddress_options(session, RT_0, SA_3, UNMMKO1_RT_SUBADDRESS_QUEUE));
    unmkocheck(unmmko1_rt_set_subaddress_data(session, RT_0, SA_1,  data_words_count, data_words));
    unmkocheck(unmmko1_rt_set_subaddress_data(session, RT_0, SA_3,  data_words_count, data_words));

    free(data_words);

    unmkocheck(unmmko1_rt_start(session));

    printf("Press a key to continue\n");
    while (!key_pressed())
        Sleep(1);

    unmkocheck(unmmko1_rt_stop(session));

    unmkocheck(unmmko1_close(session));
    unmbasecheck(unmbase_close(carrier_session));

    return status;
}
