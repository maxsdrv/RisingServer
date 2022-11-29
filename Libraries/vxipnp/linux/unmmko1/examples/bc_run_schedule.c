#include "common.h"

int main() {
    ViStatus status = VI_SUCCESS;
    ViUInt16 data_words[32] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32};
    size_t command_index = 0;
    unmmko1_command commands[10];
    commands[0] = unmmko1_f1 (UNMMKO1_BUS_A, RT_3, SA_2, 32, data_words);
    commands[1] = unmmko1_f2 (UNMMKO1_BUS_B, RT_3, SA_2, 2);
    commands[2] = unmmko1_f3 (UNMMKO1_BUS_A, RT_1, SA_2, RT_3, SA_2, 5);
    commands[3] = unmmko1_f4 (UNMMKO1_BUS_A, RT_1, SA_MC0, 2);
    commands[4] = unmmko1_f5 (UNMMKO1_BUS_A, RT_1, SA_MC31, 19);
    commands[5] = unmmko1_f6 (UNMMKO1_BUS_A, RT_1, SA_MC0, 17, 0);
    commands[6] = unmmko1_f7 (UNMMKO1_BUS_A, SA_2, 32, data_words);
    commands[7] = unmmko1_f8 (UNMMKO1_BUS_A, SA_2, RT_1, SA_2, 5);
    commands[8] = unmmko1_f9 (UNMMKO1_BUS_A, SA_MC0, 1);
    commands[9] = unmmko1_f10(UNMMKO1_BUS_A, SA_MC31, 17, 0);

    unmkocheck(search_unmmko1(resource_name, &position));

    unmbasecheck(unmbase_init(resource_name, VI_TRUE, VI_TRUE, &carrier_session));
    unmkocheck(unmmko1_init(resource_name, VI_TRUE, VI_TRUE, &session));
    unmkocheck(unmmko1_connect(session, carrier_session, position, VI_TRUE, VI_TRUE));

    unmkocheck(unmmko1_bc_configure(session, UNMMKO1_BC_DEFAULT));
    for (command_index = 0; command_index < 10; ++command_index)
        unmkocheck(unmmko1_bc_schedule_command(session, commands[command_index]));

    unmkocheck(unmmko1_bc_start(session));
    Sleep(1000);
    unmkocheck(unmmko1_bc_stop(session));

    unmkocheck(unmmko1_close(session));
    unmbasecheck(unmbase_close(carrier_session));

    return status;
}
