#include "unmmko1_request.h"
#include "unmmko1_utilities.h"
#include <unmbase.h>
#include <time.h>

#define REQUEST_TIMEOUT_IN_SECONDS 5

ViStatus execute_request(ViSession session, unmmko1_request_data* request, unmmko1_response_data* response) {
    ViStatus status = VI_SUCCESS;
    clock_t start_time, elapsed_time;
    unmmko1_device_data* device_data = get_device_data_or_error(session);

    ++device_data->command_counter;
    if (0 == device_data->command_counter)
        device_data->command_counter = 1;

    request->counter = device_data->command_counter;

    // Передаём запрос
    unerror(unmbase_m_moveout16(session, REQUEST_ADDRESS, (ViUInt16*)request, REQUEST_SIZE, REQUEST_INCREMENT));
    un_sleep(10);

    // Дожидаемся корректного ответа или статуса ошибки
    start_time = clock();
    do {
        unerror(unmbase_m_movein16(session, RESPONSE_ADDRESS, (ViUInt16*)(*response), RESPONSE_SIZE, REQUEST_INCREMENT));
        un_sleep(5);
        elapsed_time = clock() - start_time;
    } while ((0 == (*response)[0]) && (0 != (*response)[RESPONSE_SIZE - 1]) && (elapsed_time / CLOCKS_PER_SEC < REQUEST_TIMEOUT_IN_SECONDS));

    if (elapsed_time / CLOCKS_PER_SEC >= REQUEST_TIMEOUT_IN_SECONDS)
        status = VI_ERROR_TMO;

Error:
    return status;
}

void clear_request(unmmko1_request_data* request) {
    ViUInt32 index = 0;
    request->command = 0;
    request->counter = 1;
    request->new_data = 0;
    for (index = 0; index < REQUEST_DATA_SIZE; ++index)
        request->data[index] = 0;
    request->data[REQUEST_DATA_SIZE - 1] = 1;
}

void clear_response(unmmko1_response_data* response) {
    ViUInt32 index = 0;
    for (index = 0; index < RESPONSE_SIZE; ++index)
        (*response)[index] = 0;
    (*response)[RESPONSE_SIZE - 1] = 1;
}
