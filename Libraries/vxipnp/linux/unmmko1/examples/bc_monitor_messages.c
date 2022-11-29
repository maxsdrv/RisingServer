#include "common.h"

int main() {
    ViStatus status = VI_SUCCESS;
    ViUInt16 data_words[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    unmmko1_command command_f1 = unmmko1_f1(UNMMKO1_BUS_A, RT_3, SA_2, 10, data_words);
    unmmko1_command command_f2 = unmmko1_f2(UNMMKO1_BUS_B, RT_3, SA_2, 2);
    ViUInt32 messages_count = 0;
    unmmko1_message* messages = NULL;

    unmkocheck(search_unmmko1(resource_name, &position));

    unmbasecheck(unmbase_init(resource_name, VI_TRUE, VI_TRUE, &carrier_session));
    unmkocheck(unmmko1_init(resource_name, VI_TRUE, VI_TRUE, &session));
    unmkocheck(unmmko1_connect(session, carrier_session, position, VI_TRUE, VI_TRUE));

    unmkocheck(unmmko1_bc_configure(session, UNMMKO1_BC_DEFAULT));
    unmkocheck(unmmko1_bc_start(session));
    unmkocheck(unmmko1_mon_start(session));

    unmkocheck(unmmko1_bc_transmit_command(session, command_f1));
    Sleep(1);

    unmkocheck(unmmko1_bc_transmit_command(session, command_f2));
    Sleep(1);

    unmkocheck(unmmko1_mon_stop(session));
    unmkocheck(unmmko1_bc_stop(session));
    unmkocheck(unmmko1_mon_messages_count(session, &messages_count));

    messages = (unmmko1_message*)calloc(messages_count, sizeof(unmmko1_message));
    unmkocheck(unmmko1_mon_messages_read(session, messages_count, messages, &messages_count));
    print_messages(messages_count, messages);
    free(messages);

    unmkocheck(unmmko1_close(session));
    unmbasecheck(unmbase_close(carrier_session));

    return status;
}
