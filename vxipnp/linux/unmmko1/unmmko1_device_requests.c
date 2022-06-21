#include "unmmko1_device_requests.h"
#include "unmmko1_request.h"
#include "unmmko1_utilities.h"
#include "unmbase.h"
#include <string.h>

#define UNMMKO1_CMD_SELFTEST                        0x0001
#define UNMMKO1_CMD_RESET                           0x0002
#define UNMMKO1_CMD_VERSION                         0x0004
#define UNMMKO1_CMD_SET_FIFO_MODE                   0x5030
#define UNMMKO1_CMD_GET_FIFO_MODE                   0x5031
#define UNMMKO1_CMD_FIFO_TEST                       0x5032
#define UNMMKO1_CMD_SET_CONNECTION_TYPE             0x5060
#define UNMMKO1_CMD_GET_CONNECTION_TYPE             0x5061
#define UNMMKO1_CMD_SET_MODE                        0x5062
#define UNMMKO1_CMD_GET_MODE                        0x5063
#define UNMMKO1_CMD_RESET_MODE                      0x5064
#define UNMMKO1_CMD_GET_STATE                       0x0065
#define UNMMKO1_CMD_GET_CURRENT_TIMESTAMP           0x0066
#define UNMMKO1_CMD_RT_SET_DATA                     0x5040
#define UNMMKO1_CMD_RT_GET_N_DATA                   0x5041
#define UNMMKO1_CMD_RT_GET_DATA                     0x5042
#define UNMMKO1_CMD_RT_SET_CONFIG                   0x5043
#define UNMMKO1_CMD_RT_GET_CONFIG                   0x5044
#define UNMMKO1_CMD_RT_START                        0x5045
#define UNMMKO1_CMD_RT_STOP                         0x5046
#define UNMMKO1_CMD_RT_SET_STATUS_WORD              0x5047
#define UNMMKO1_CMD_RT_TURN                         0x5048
#define UNMMKO1_CMD_RT_BUILD                        0x504A
#define UNMMKO1_CMD_RT_UPDATE_DATA_HIGH             0x504B
#define UNMMKO1_CMD_RT_UPDATE_DATA_LOW              0x504C
#define UNMMKO1_CMD_BC_GET_N_MESSAGE                0x5050
#define UNMMKO1_CMD_BC_SET_MESSAGE                  0x5051
#define UNMMKO1_CMD_BC_GET_MESSAGE					0x5052
#define UNMMKO1_CMD_BC_GET_MESSAGE_SIZE             0x5053
#define UNMMKO1_CMD_BC_GET_SCHEDULE					0x5054
#define UNMMKO1_CMD_BC_START                        0x5055
#define UNMMKO1_CMD_BC_STOP							0x5056
#define UNMMKO1_CMD_BC_START_MON                    0x5057
#define UNMMKO1_CMD_BC_SEND_COMMAND                 0x5076
#define UNMMKO1_CMD_MON_START                       0x5080
#define UNMMKO1_CMD_MON_STOP                        0x5081

ViStatus set_current_mode(ViSession session, unmmko1_mode mode) {
    ViStatus status = VI_SUCCESS;
    unmmko1_request_data request;
    unmmko1_response_data response;
    unmmko1_device_data* device_data = get_device_data_or_error(session);

    if (is_not_valid_session(session))
        return UNMMKO1_ERROR_INTERNAL;

    clear_request(&request);
    clear_response(&response);

    request.command = UNMMKO1_CMD_SET_MODE;
    request.data[0] = (ViUInt16)mode;
    unerror(execute_request(session, &request, &response));

    device_data->current_mode = mode;

Error:
    return status;
}

ViStatus get_current_mode(ViSession session, unmmko1_mode* mode) {
    ViStatus status = VI_SUCCESS;
    unmmko1_request_data request;
    unmmko1_response_data response;

    if (is_not_valid_session(session))
        return UNMMKO1_ERROR_INTERNAL;
    if (is_not_valid_pointer(mode))
        return UNMMKO1_ERROR_INTERNAL;

    clear_request(&request);
    clear_response(&response);

    request.command = UNMMKO1_CMD_GET_MODE;
    request.counter = 10;
    unerror(execute_request(session, &request, &response));

    *mode = (unmmko1_mode)response[1];

Error:
    return status;
}

ViStatus set_connection_type(ViSession session, unmmko1_connection_type type) {
    ViStatus status = VI_SUCCESS;
    unmmko1_request_data request;
    unmmko1_response_data response;

    if (is_not_valid_session(session))
        return UNMMKO1_ERROR_INTERNAL;

    clear_request(&request);
    clear_response(&response);

    request.command = UNMMKO1_CMD_SET_CONNECTION_TYPE;
    request.data[0] = (ViUInt16)type;
    unerror(execute_request(session, &request, &response));

Error:
    return status;
}

ViStatus get_connection_type(ViSession session, unmmko1_connection_type* type) {
    ViStatus status = VI_SUCCESS;
    unmmko1_request_data request;
    unmmko1_response_data response;

    if (is_not_valid_session(session))
        return UNMMKO1_ERROR_INTERNAL;
    if (is_not_valid_pointer(type))
        return UNMMKO1_ERROR_INTERNAL;

    clear_request(&request);
    clear_response(&response);

    request.command = UNMMKO1_CMD_GET_CONNECTION_TYPE;
    request.counter = 10;
    unerror(execute_request(session, &request, &response));

    *type = (unmmko1_connection_type)response[1];

Error:
    return status;
}

ViStatus get_current_timestamp(ViSession session, ViUInt64* timestamp) {
    ViStatus status = VI_SUCCESS;
    unmmko1_request_data request;
    unmmko1_response_data response;

    if (is_not_valid_session(session))
        return UNMMKO1_ERROR_INTERNAL;
    if (is_not_valid_pointer(timestamp))
        return UNMMKO1_ERROR_INTERNAL;

    clear_request(&request);
    clear_response(&response);

    *timestamp = 0;

    request.command = UNMMKO1_CMD_GET_CURRENT_TIMESTAMP;
    request.counter = 10;
    unerror(execute_request(session, &request, &response));

    *timestamp = (ViUInt64)(response[1]) | ((ViUInt64)(response[2]) << 16) | ((ViUInt64)(response[3]) << 32) | ((ViUInt64)(response[4]) << 48);

Error:
    return status;
}

ViStatus start_bc(ViSession session, ViUInt16 messages_index) {
    ViStatus status = VI_SUCCESS;
    unmmko1_request_data request;
    unmmko1_response_data response;

    if (is_not_valid_session(session))
        return UNMMKO1_ERROR_INTERNAL;

    clear_request(&request);
    clear_response(&response);

    request.command = UNMMKO1_CMD_BC_START;
    request.data[0] = messages_index;
    unerror(execute_request(session, &request, &response));

Error:
    return status;
}

ViStatus stop_bc(ViSession session) {
    ViStatus status = VI_SUCCESS;
    unmmko1_request_data request;
    unmmko1_response_data response;

    if (is_not_valid_session(session))
        return UNMMKO1_ERROR_INTERNAL;

    clear_request(&request);
    clear_response(&response);

    request.command = UNMMKO1_CMD_BC_STOP;
    unerror(execute_request(session, &request, &response));

Error:
    return status;
}

typedef struct {
    ViUInt16 state;
    ViUInt16 delay;
    ViUInt16 next_command_index;
    ViUInt16 size;
    ViUInt16 data[33];
    ViUInt16 reserve[3];
} mmko1_internal_command;

ViStatus set_bc_command(ViSession session, ViUInt16 command_index, unmmko1_command command, ViBoolean is_last, ViUInt16 next_command_index) {
    ViStatus status = VI_SUCCESS;
    ViInt16 state = 0;
    unmmko1_request_data request;
    unmmko1_response_data response;
    mmko1_internal_command internal_command;

    if (is_not_valid_session(session))
        return UNMMKO1_ERROR_INTERNAL;

    // Заполняем структуру команды
    internal_command.size = command.data_words_count + (command.activity & UNMMKO1_MSG_ACT_CWD_2 ? 2 : 1);
    internal_command.data[0] = command.command_word_1;
    if (command.activity & UNMMKO1_MSG_ACT_CWD_2) {
        internal_command.data[1] = command.command_word_2;
        memcpy(internal_command.data + 2, command.data_words, command.data_words_count * sizeof(ViUInt16));
    }
    else {
        memcpy(internal_command.data + 1, command.data_words, command.data_words_count * sizeof(ViUInt16));
    }

    internal_command.delay = 1000;
    internal_command.next_command_index = next_command_index;
    internal_command.state = 0x0008U;
    if (is_last)
        internal_command.state |= 0x0001U;
    if (command.activity & UNMMKO1_MSG_ACT_BUS_B)
        internal_command.state |= 0x0004U;
    if (command.activity & UNMMKO1_MSG_ACT_CWD_2)
        internal_command.state |= 0x0002U;

    // Передаём буфер с командой
    unerror(unmbase_m_stop(session, UNMBASE_IOMODE_OUT));
    unerror(unmbase_m_mode(session, UNMBASE_IOMODE_OUT, UNMBASE_MODE_BLOCK));

    unerror(unmbase_m_block_size(session, 1, sizeof(mmko1_internal_command) / sizeof(ViUInt32)));
    unerror(unmbase_m_write_block(session, 0, sizeof(mmko1_internal_command) / sizeof(ViUInt32), (ViUInt32*)(&internal_command)));
    unerror(unmbase_m_out16(session, 0, 1));
    unerror(unmbase_m_start(session, UNMBASE_IOMODE_OUT));

    clear_request(&request);
    clear_response(&response);

    request.command = UNMMKO1_CMD_BC_SET_MESSAGE;
    request.counter = 10;
    request.data[0] = command_index;
    unerror(execute_request(session, &request, &response));

    do {
        unerror(unmbase_m_state(session, UNMBASE_IOMODE_OUT, &state));
    } while (state > 0);

    unerror(unmbase_m_async_stop(session, UNMBASE_IOMODE_OUT));

Error:
    return status;
}

ViStatus start_bc_mon(ViSession session) {
    ViStatus status = VI_SUCCESS;
    unmmko1_request_data request;
    unmmko1_response_data response;

    if (is_not_valid_session(session))
        return UNMMKO1_ERROR_INTERNAL;

    clear_request(&request);
    clear_response(&response);

    request.command = UNMMKO1_CMD_BC_START_MON;
    unerror(execute_request(session, &request, &response));

Error:
    return status;
}

ViStatus transmit_bc_command(ViSession session, unmmko1_command command) {
    ViStatus status = VI_SUCCESS;
    ViUInt16 buffer[34];
    ViUInt16 size = (command.data_words_count + (command.activity & UNMMKO1_MSG_ACT_CWD_2 ? 2 : 1) + 1) / 2;
    ViInt16 state = 0;
    unmmko1_request_data request;
    unmmko1_response_data response;

    if (is_not_valid_session(session))
        return UNMMKO1_ERROR_INTERNAL;

    // Заполняем слова во временный буфер
    memset(buffer, 0, sizeof(buffer));
    buffer[0] = command.command_word_1;
    if (command.activity & UNMMKO1_MSG_ACT_CWD_2) {
        buffer[1] = command.command_word_2;
        memcpy(buffer + 2, command.data_words, command.data_words_count * sizeof(ViUInt16));
    }
    else {
        memcpy(buffer + 1, command.data_words, command.data_words_count * sizeof(ViUInt16));
    }

    // Передаём буфер с командой
    unerror(unmbase_m_stop(session, UNMBASE_IOMODE_OUT));
    unerror(unmbase_m_mode(session, UNMBASE_IOMODE_OUT, UNMBASE_MODE_BLOCK));

    unerror(unmbase_m_block_size(session, 1, size));
    unerror(unmbase_m_write_block(session, 0, size, (ViUInt32*)buffer));
    unerror(unmbase_m_out16(session, 0, 1));
    unerror(unmbase_m_start(session, UNMBASE_IOMODE_OUT));

    clear_request(&request);
    clear_response(&response);

    request.command = UNMMKO1_CMD_BC_SEND_COMMAND;
    request.counter = 10;
    request.data[0] = (command.activity & UNMMKO1_MSG_ACT_BUS_B) ? 2 : 1;
    request.data[1] = (command.activity & UNMMKO1_MSG_ACT_CWD_2) ? 1 : 0;
    request.data[2] = command.data_words_count + (command.activity & UNMMKO1_MSG_ACT_CWD_2 ? 2 : 1);
    unerror(execute_request(session, &request, &response));

    do {
        unerror(unmbase_m_state(session, UNMBASE_IOMODE_OUT, &state));
    } while (state > 0);

    unerror(unmbase_m_async_stop(session, UNMBASE_IOMODE_OUT));

Error:
    return status;
}

ViStatus start_rt(ViSession session, unmmko1_bus_usage bus_usage) {
    ViStatus status = VI_SUCCESS;
    unmmko1_request_data request;
    unmmko1_response_data response;
    ViUInt16 bus_usage_internal = 0;

    if (is_not_valid_session(session))
        return UNMMKO1_ERROR_INTERNAL;

    clear_request(&request);
    clear_response(&response);

    if (bus_usage == UNMMKO1_USE_BUS_A_AND_B)
        bus_usage_internal = 3;
    else if (bus_usage == UNMMKO1_USE_ONLY_BUS_A)
        bus_usage_internal = 1;
    else if (bus_usage == UNMMKO1_USE_ONLY_BUS_B)
        bus_usage_internal = 2;

    request.command = UNMMKO1_CMD_RT_START;
    request.data[0] = bus_usage_internal;
    unerror(execute_request(session, &request, &response));

Error:
    return status;
}

ViStatus stop_rt(ViSession session) {
    ViStatus status = VI_SUCCESS;
    unmmko1_request_data request;
    unmmko1_response_data response;

    if (is_not_valid_session(session))
        return UNMMKO1_ERROR_INTERNAL;

    clear_request(&request);
    clear_response(&response);

    request.command = UNMMKO1_CMD_RT_STOP;
    request.counter = 10;
    unerror(execute_request(session, &request, &response));

Error:
    return status;
}

ViStatus turn_rt(ViSession session, ViUInt32 addresses_mask) {
    ViStatus status = VI_SUCCESS;
    unmmko1_request_data request;
    unmmko1_response_data response;

    if (is_not_valid_session(session))
        return UNMMKO1_ERROR_INTERNAL;

    clear_request(&request);
    clear_response(&response);

    request.command = UNMMKO1_CMD_RT_TURN;
    request.counter = 10;
    request.data[0] = (ViUInt16)(addresses_mask >> 16);
    request.data[1] = (ViUInt16)(addresses_mask & 0xffff);
    unerror(execute_request(session, &request, &response));

Error:
    return status;
}

ViStatus build_rt(ViSession session, ViUInt32 addresses_mask, ViBoolean build_default_responses) {
    ViStatus status = VI_SUCCESS;
    unmmko1_request_data request;
    unmmko1_response_data response;

    if (is_not_valid_session(session))
        return UNMMKO1_ERROR_INTERNAL;

    clear_request(&request);
    clear_response(&response);

    request.command = UNMMKO1_CMD_RT_BUILD;
    request.counter = 10;
    request.data[0] = build_default_responses ? 1 : 0;
    request.data[1] = (ViUInt16)(addresses_mask >> 16);
    request.data[2] = (ViUInt16)(addresses_mask & 0xffff);
    unerror(execute_request(session, &request, &response));

Error:
    return status;
}

ViStatus set_status_word(ViSession session, ViUInt16 address, ViUInt16 status_word) {
    ViStatus status = VI_SUCCESS;
    unmmko1_request_data request;
    unmmko1_response_data response;

    if (is_not_valid_session(session))
        return UNMMKO1_ERROR_INTERNAL;

    clear_request(&request);
    clear_response(&response);

    request.command = UNMMKO1_CMD_RT_SET_STATUS_WORD;
    request.counter = 10;
    request.data[0] = address;
    request.data[1] = status_word;
    unerror(execute_request(session, &request, &response));

Error:
    return status;
}

ViStatus set_rt_configuration(ViSession session, ViUInt16 address, ViBoolean on, ViUInt16 status_word, ViUInt16 vector_word, ViUInt16 selftest_word) {
    ViStatus status = VI_SUCCESS;
    unmmko1_request_data request;
    unmmko1_response_data response;

    if (is_not_valid_session(session))
        return UNMMKO1_ERROR_INTERNAL;

    clear_request(&request);
    clear_response(&response);

    request.command = UNMMKO1_CMD_RT_SET_CONFIG;
    request.counter = 10;
    request.data[0] = address;
    request.data[1] = status_word;
    request.data[2] = vector_word;
    request.data[3] = selftest_word;
    request.data[4] = on ? 1 : 0;

    unerror(execute_request(session, &request, &response));

Error:
    return status;
}

ViStatus get_rt_configuration(ViSession session, ViUInt16 address, ViBoolean* on, ViUInt16* status_word, ViUInt16* vector_word, ViUInt16* selftest_word) {
    ViStatus status = VI_SUCCESS;
    unmmko1_request_data request;
    unmmko1_response_data response;

    if (is_not_valid_session(session))
        return UNMMKO1_ERROR_INTERNAL;

    clear_request(&request);
    clear_response(&response);

    request.command = UNMMKO1_CMD_RT_GET_CONFIG;
    request.counter = 10;
    request.data[0] = address;
    unerror(execute_request(session, &request, &response));

    if (is_valid_pointer(status_word))
        *status_word = response[2];
    if (is_valid_pointer(vector_word))
        *vector_word = response[3];
    if (is_valid_pointer(selftest_word))
        *selftest_word = response[4];
    if (is_valid_pointer(on))
        *on = response[5] ? VI_TRUE : VI_FALSE;

Error:
    return status;
}

ViStatus set_rt_data(ViSession session, ViUInt16 address, ViUInt16 subaddress, unmmko1_rt_subaddress_options options, ViUInt16 data_words_count, ViUInt32* packed_data_words) {
    ViStatus status = VI_SUCCESS;
    ViUInt16 size = (data_words_count + 1) / 2;
    ViInt16 state = 0;
    unmmko1_request_data request;
    unmmko1_response_data response;

    if (is_not_valid_session(session))
        return UNMMKO1_ERROR_INTERNAL;

    // Передаём буфер с командой
    unerror(unmbase_m_stop(session, UNMBASE_IOMODE_OUT));
    unerror(unmbase_m_mode(session, UNMBASE_IOMODE_OUT, UNMBASE_MODE_BLOCK));

    unerror(unmbase_m_block_size(session, 1, size));
    unerror(unmbase_m_write_block(session, 0, size, packed_data_words));
    unerror(unmbase_m_out16(session, 0, 1));
    unerror(unmbase_m_start(session, UNMBASE_IOMODE_OUT));

    clear_request(&request);
    clear_response(&response);

    request.command = UNMMKO1_CMD_RT_SET_DATA;
    request.counter = 10;
    request.data[0] = (ViUInt16)(address << 5) | subaddress;
    request.data[1] = (ViUInt16)options + 1;
    request.data[2] = data_words_count;
    unerror(execute_request(session, &request, &response));

    do {
        unerror(unmbase_m_state(session, UNMBASE_IOMODE_OUT, &state));
    } while (state > 0);

    unerror(unmbase_m_async_stop(session, UNMBASE_IOMODE_OUT));

Error:
    return status;
}

ViStatus get_rt_data(ViSession session, ViUInt16 address, ViUInt16 subaddress, unmmko1_rt_subaddress_options* options, ViUInt16* data_words_count, ViUInt32* packed_data_words) {
    ViStatus status = VI_SUCCESS;
    ViUInt32 buffer_size = 0;
    unmmko1_request_data request;
    unmmko1_response_data response;

    if (is_not_valid_session(session))
        return UNMMKO1_ERROR_INTERNAL;
    if (is_not_valid_pointer(data_words_count))
        return UNMMKO1_ERROR_INTERNAL;

    // Запускаем чтение данных
    unerror(unmbase_m_mode(session, UNMBASE_IOMODE_IN, UNMBASE_MODE_LOOP));
    unerror(unmbase_m_out16(session, REGISTER_FIFO, 0xFF));
    unerror(unmbase_m_start(session, UNMBASE_IOMODE_IN));

    clear_request(&request);
    clear_response(&response);

    request.command = UNMMKO1_CMD_RT_GET_DATA;
    request.counter = 10;
    request.data[0] = (ViUInt16)(address << 5) | subaddress;
    unerror(execute_request(session, &request, &response));

    if (is_valid_pointer(options))
        *options = (unmmko1_rt_subaddress_options)(response[1] - 1);
    *data_words_count = response[2];

    un_sleep(10);

    // Читаем слова данных и останавливаем чтение данных
    unerror(unmbase_m_read_packet(session, *data_words_count, packed_data_words, &buffer_size));
    unerror(unmbase_m_async_stop(session, UNMBASE_IOMODE_IN));

Error:
    return status;
}

ViStatus update_rt_data(ViSession session, ViUInt16 address, ViUInt16 subaddress, ViUInt16 data_words_count, ViUInt16* data_words) {
    ViStatus status = VI_SUCCESS;
    ViUInt16 data_word_index = 0;
    const ViUInt16 half_data_words_count = 16;
    unmmko1_request_data request;
    unmmko1_response_data response;

    if (is_not_valid_session(session))
        return UNMMKO1_ERROR_INTERNAL;

    clear_request(&request);
    clear_response(&response);

    request.command = UNMMKO1_CMD_RT_UPDATE_DATA_LOW;
    request.counter = 10;
    request.data[0] = (ViUInt16)(address << 5) | subaddress;
    request.data[1] = MIN(half_data_words_count, data_words_count);
    for (data_word_index = 0; data_word_index < request.data[1]; ++data_word_index)
        request.data[2 + data_word_index] = data_words[data_word_index];
    unerror(execute_request(session, &request, &response));

    if (data_words_count > half_data_words_count) {
        clear_request(&request);
        clear_response(&response);

        request.command = UNMMKO1_CMD_RT_UPDATE_DATA_HIGH;
        request.counter = 10;
        request.data[0] = (ViUInt16)(address << 5) | subaddress;
        request.data[1] = MIN(half_data_words_count, data_words_count - half_data_words_count);
        for (data_word_index = 0; data_word_index < request.data[1]; ++data_word_index)
            request.data[2 + data_word_index] = data_words[half_data_words_count + data_word_index];
        unerror(execute_request(session, &request, &response));
    }
Error:
    return status;
}

ViStatus start_mon(ViSession session, unmmko1_bus_usage bus_usage) {
    ViStatus status = VI_SUCCESS;
    unmmko1_request_data request;
    unmmko1_response_data response;
    ViUInt16 bus_usage_internal = 0;

    if (is_not_valid_session(session))
        return UNMMKO1_ERROR_INTERNAL;

    clear_request(&request);
    clear_response(&response);

    if (bus_usage == UNMMKO1_USE_BUS_A_AND_B)
        bus_usage_internal = 3;
    else if (bus_usage == UNMMKO1_USE_ONLY_BUS_A)
        bus_usage_internal = 1;
    else if (bus_usage == UNMMKO1_USE_ONLY_BUS_B)
        bus_usage_internal = 2;

    request.command = UNMMKO1_CMD_MON_START;
    request.data[0] = bus_usage_internal;
    unerror(execute_request(session, &request, &response));

Error:
    return status;
}

ViStatus stop_mon(ViSession session) {
    ViStatus status = VI_SUCCESS;
    unmmko1_request_data request;
    unmmko1_response_data response;

    if (is_not_valid_session(session))
        return UNMMKO1_ERROR_INTERNAL;

    clear_request(&request);
    clear_response(&response);

    request.command = UNMMKO1_CMD_MON_STOP;
    request.counter = 10;
    unerror(execute_request(session, &request, &response));

Error:
    return status;
}

ViStatus self_test(ViSession session) {
    ViStatus status = VI_SUCCESS;
    ViUInt32 buffer[4] = {0x0123, 0x4567, 0x89AB, 0xCDEF};
    ViUInt32 buffer_size = sizeof(buffer) / sizeof(ViUInt32);
    ViUInt32 in_buffer[64];
    ViUInt32 in_buffer_size = sizeof(in_buffer) / sizeof(ViUInt32);
    ViInt16 state = 0;
    unmmko1_request_data request;
    unmmko1_response_data response;

    if (is_not_valid_session(session))
        return UNMMKO1_ERROR_INTERNAL;

    // Запускаем чтение данных
    unerror(unmbase_m_mode(session, UNMBASE_IOMODE_IN, UNMBASE_MODE_LOOP));
    unerror(unmbase_m_out16(session, REGISTER_FIFO, 0xFF));
    unerror(unmbase_m_start(session, UNMBASE_IOMODE_IN));

    // Запускаем запись данных
    unerror(unmbase_m_stop(session, UNMBASE_IOMODE_OUT));
    unerror(unmbase_m_mode(session, UNMBASE_IOMODE_OUT, UNMBASE_MODE_BLOCK));

    unerror(unmbase_m_block_size(session, 1, buffer_size));
    unerror(unmbase_m_write_block(session, 0, buffer_size, buffer));
    unerror(unmbase_m_out16(session, 0, 1));
    unerror(unmbase_m_start(session, UNMBASE_IOMODE_OUT));

    clear_request(&request);
    clear_response(&response);

    request.command = UNMMKO1_CMD_FIFO_TEST;
    request.data[0] = (ViUInt16)(buffer_size & 0xffff);
    request.data[1] = (ViUInt16)(buffer_size >> 16);
    unerror(execute_request(session, &request, &response));

    // Дожидаемся записи данных
    do {
        unerror(unmbase_m_state(session, UNMBASE_IOMODE_OUT, &state));
    } while (state > 0);

    unerror(unmbase_m_async_stop(session, UNMBASE_IOMODE_OUT));

    // Читаем эхо-данные и останавливаем чтение данных
    unerror(unmbase_m_read_packet(session, in_buffer_size, in_buffer, &in_buffer_size));
    unerror(unmbase_m_async_stop(session, UNMBASE_IOMODE_IN));

    // Сравниваем данные
    if (memcmp(buffer, in_buffer, sizeof(buffer)))
        return -1;

    // Выполняем функцию самоконтроля
    clear_request(&request);
    clear_response(&response);

    request.command = UNMMKO1_CMD_SELFTEST;
    request.counter = 22;
    request.data[0] = UNMMKO1_MODEL_CODE;
    unerror(execute_request(session, &request, &response));

    // Прокидываем коды ошибок самоконтроля
    if (response[1] == 1)
        status = -2;
    if (response[1] == 2)
        status = -3;

Error:
    return status;
}
