#include "common.h"

int main() {
    ViStatus status = VI_SUCCESS;
    ViUInt32 messages_count = 0;
    unmmko1_message* messages = NULL;

    unmkocheck(search_unmmko1(resource_name, &position));

    unmbasecheck(unmbase_init(resource_name, VI_TRUE, VI_TRUE, &carrier_session));
    unmkocheck(unmmko1_init(resource_name, VI_TRUE, VI_TRUE, &session));
    unmkocheck(unmmko1_connect(session, carrier_session, position, VI_TRUE, VI_TRUE));

    unmkocheck(unmmko1_mon_configure(session, UNMMKO1_MON_TRANSFORM | UNMMKO1_MON_BUS_A_AND_B));
    unmkocheck(unmmko1_mon_start(session));

    printf("Press a key to continue\n");
    while (!key_pressed())
        Sleep(1);

    unmkocheck(unmmko1_mon_stop(session));
    unmkocheck(unmmko1_mon_messages_count(session, &messages_count));

    messages = (unmmko1_message*)calloc(messages_count, sizeof(unmmko1_message));
    unmkocheck(unmmko1_mon_messages_read(session, messages_count, messages, &messages_count));
    print_messages(messages_count, messages);
    free(messages);

    unmkocheck(unmmko1_close(session));
    unmbasecheck(unmbase_close(carrier_session));

    return status;
}
