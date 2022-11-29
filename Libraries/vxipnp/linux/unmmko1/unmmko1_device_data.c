#include "unmmko1_device_data.h"

#include <stdlib.h>
#include <stddef.h>
#include <visa.h>
#include <unmbase.h>
#include "unmmko1_utilities.h"

unmmko1_device_data* get_device_data_from_visa(ViSession session) {
    unmmko1_device_data* data = NULL;
    if (viGetAttribute(session, VI_ATTR_USER_DATA, (ViPAttrState)&data) >= 0)
        return data;
    return NULL;
}

unmmko1_device_data* get_device_data_from_carrier(ViSession session) {
    unmmko1_device_data* data = NULL;
    if (unmbase_m_get_attribute(session, UNMBASE_MATTR_USER_DATA, (void*)&data) >= 0)
        return data;
    return NULL;
}

ViBoolean is_not_valid_device_data(unmmko1_device_data* data) {
    return (NULL == data || data->model_code != UNMMKO1_MODEL_CODE);
}

ViStatus create_device_data(unmmko1_device_data** device_data) {
    ViStatus status = VI_SUCCESS;
    unmmko1_device_data* new_device_data;

    *device_data = new_device_data = (unmmko1_device_data*)calloc(1, sizeof(unmmko1_device_data));
    if (is_not_valid_pointer(new_device_data))
        return VI_ERROR_ALLOC;

    // Задаём значения по умолчанию
    new_device_data->model_code = UNMMKO1_MODEL_CODE;
    new_device_data->session = 0;
    new_device_data->carrier_session = 0;
    new_device_data->interrupt_request_handler = NULL;
    new_device_data->interrupt_request_data = NULL;
    new_device_data->command_counter = 0;

    new_device_data->current_mode = UNMMKO1_MODE_UNDEFINED;

    create_bus_monitor_settings(&new_device_data->bus_monitor);
    create_bus_controller_settings(&new_device_data->bus_controller);
    create_remote_terminal_settings(&new_device_data->remote_terminal);

    return status;
}

ViStatus fill_device_data(unmmko1_device_data* device_data) {
    ViStatus status = VI_SUCCESS;

    if (is_not_valid_device_data(device_data))
        return VI_ERROR_INV_SETUP;
    if (is_not_valid_session(device_data->session))
        return VI_ERROR_INV_SETUP;

    reset_bus_monitor_settings(&device_data->bus_monitor);
    reset_bus_controller_settings(&device_data->bus_controller);
    reset_remote_terminal_settings(&device_data->remote_terminal);

    return status;
}

ViStatus destroy_device_data(unmmko1_device_data* device_data) {
    ViStatus status = VI_SUCCESS;

    destroy_bus_monitor_settings(&device_data->bus_monitor);
    destroy_bus_controller_settings(&device_data->bus_controller);
    destroy_remote_terminal_settings(&device_data->remote_terminal);

    free(device_data);
    device_data = NULL;

    return status;
}

ViStatus reset_device_data(unmmko1_device_data* device_data) {
    ViStatus status = VI_SUCCESS;

    device_data->interrupt_request_handler = NULL;
    device_data->interrupt_request_data = NULL;
    device_data->current_mode = UNMMKO1_MODE_UNDEFINED;

    reset_bus_monitor_settings(&device_data->bus_monitor);
    reset_bus_controller_settings(&device_data->bus_controller);
    reset_remote_terminal_settings(&device_data->remote_terminal);

    return status;
}

ViBoolean _VI_FUNCH interrupt_request_handler(ViSession session, ViInt32 reason) {
    unmmko1_device_data* device_data = get_device_data_from_carrier(session);
    if (is_not_valid_device_data(device_data))
        return 0;

    // Осуществляем сброс мезонина при запросе от носителя мезонинов
    if (UNMBASE_EVENT_RESET == reason)
        unmmko1_reset(session);

    // Вызываем пользовательский обработчик
    if (device_data->interrupt_request_handler)
        return device_data->interrupt_request_handler(session, reason, device_data->interrupt_request_data);

    return 1;
}

void reset_sequence_data(sequence_s* s) {
    size_t i = 0;
    s->timestamp = 0;
    s->count = 0;
    s->types = 0;
    for (; i < 40; ++i)
        s->values[i] = 0;
    s->errors = 0;
    s->gap = 0;
}

void reset_accumulator(accumulator_t* accumulator) {
    reset_sequence_data(&accumulator->sequence_a[0]);
    reset_sequence_data(&accumulator->sequence_a[1]);
    reset_sequence_data(&accumulator->sequence_a[2]);
    reset_sequence_data(&accumulator->sequence_b[0]);
    reset_sequence_data(&accumulator->sequence_b[1]);
    reset_sequence_data(&accumulator->sequence_b[2]);

    accumulator->last_a_timestamp = 0;
    accumulator->last_b_timestamp = 0;
    accumulator->current_timestamp = 0;
    accumulator->timeout_value_in_us = default_timeout_value_in_us;
}

void reset_filter_rules(filter_rules_t* filter_rules) {
    size_t address = 0;
    filter_rules->addresses_mask = 0xffffffff;
    for (address = 0; address < 32; ++address) {
        filter_rules->receive_subaddresses[address] = 0xffffffff;
        filter_rules->transmit_subaddresses[address] = 0xffffffff;
        filter_rules->receive_modecodes[address] = 0xffffffff;
        filter_rules->transmit_modecodes[address] = 0xffffffff;
    }
}

void create_bus_monitor_settings(bus_monitor_settings_t* bus_monitor_settings) {
    bus_monitor_settings->is_started = VI_FALSE;
    bus_monitor_settings->options = UNMMKO1_MON_DEFAULT;
    bus_monitor_settings->messages = un_queue_create(sizeof(unmmko1_message));
    reset_filter_rules(&bus_monitor_settings->filter_rules);
    reset_accumulator(&bus_monitor_settings->accumulator);
}

void reset_bus_monitor_settings(bus_monitor_settings_t* bus_monitor_settings) {
    bus_monitor_settings->is_started = VI_FALSE;
    bus_monitor_settings->options = UNMMKO1_MON_DEFAULT;
    un_queue_clear(bus_monitor_settings->messages);
    reset_filter_rules(&bus_monitor_settings->filter_rules);
    reset_accumulator(&bus_monitor_settings->accumulator);
}

void destroy_bus_monitor_settings(bus_monitor_settings_t* bus_monitor_settings) {
    un_queue_destroy(bus_monitor_settings->messages);
    reset_accumulator(&bus_monitor_settings->accumulator);
}

void create_remote_terminal_settings(remote_terminal_settings_t* remote_terminal_settings) {
    ViUInt16 address = 0, subaddress = 0;

    remote_terminal_settings->is_started = VI_FALSE;
    remote_terminal_settings->options = UNMMKO1_RT_DEFAULT;

    for (address = 0; address < 31; ++address) {
        remote_terminal_settings->addresses[address].active = false;
        remote_terminal_settings->addresses[address].vector_word = 0x0000U;
        remote_terminal_settings->addresses[address].selftest_word = 0x0000U;
        remote_terminal_settings->addresses[address].status_word = invalid_status_word;
        for (subaddress = 0; subaddress < 31; ++subaddress) {
            remote_terminal_settings->addresses[address].subaddresses[subaddress].options = UNMMKO1_RT_SUBADDRESS_DEFAULT;
            remote_terminal_settings->addresses[address].subaddresses[subaddress].data_words_count = 32;
            remote_terminal_settings->addresses[address].subaddresses[subaddress].data_words = (ViUInt16*)calloc(32, sizeof(ViUInt16));
        }
    }
}

void reset_remote_terminal_settings(remote_terminal_settings_t* remote_terminal_settings) {
    ViUInt16 address = 0, subaddress = 0, data_word_index = 0;

    remote_terminal_settings->is_started = VI_FALSE;
    remote_terminal_settings->options = UNMMKO1_RT_DEFAULT;

    for (address = 0; address < 31; ++address) {
        remote_terminal_settings->addresses[address].active = false;
        remote_terminal_settings->addresses[address].vector_word = 0x0000U;
        remote_terminal_settings->addresses[address].selftest_word = 0x0000U;
        remote_terminal_settings->addresses[address].status_word = invalid_status_word;
        for (subaddress = 0; subaddress < 31; ++subaddress) {
            remote_terminal_settings->addresses[address].subaddresses[subaddress].options = UNMMKO1_RT_SUBADDRESS_DEFAULT;
            if (32 == remote_terminal_settings->addresses[address].subaddresses[subaddress].data_words_count) {
                for (data_word_index = 0; data_word_index < 32; ++data_word_index)
                    remote_terminal_settings->addresses[address].subaddresses[subaddress].data_words[data_word_index] = 0;
            }
            else {
                remote_terminal_settings->addresses[address].subaddresses[subaddress].data_words_count = 32;
                free(remote_terminal_settings->addresses[address].subaddresses[subaddress].data_words);
                remote_terminal_settings->addresses[address].subaddresses[subaddress].data_words = (ViUInt16*)calloc(32, sizeof(ViUInt16));
            }
        }
    }
}

void destroy_remote_terminal_settings(remote_terminal_settings_t* remote_terminal_settings) {
    ViUInt16 address = 0, subaddress = 0;
    for (address = 0; address < 31; ++address)
        for (subaddress = 0; subaddress < 31; ++subaddress)
            free(remote_terminal_settings->addresses[address].subaddresses[subaddress].data_words);
}

void create_bus_controller_settings(bus_controller_settings_t* bus_controller_settings) {
    bus_controller_settings->is_started = VI_FALSE;
    bus_controller_settings->options = UNMMKO1_BC_DEFAULT;

    bus_controller_settings->schedule = un_queue_create(sizeof(unmmko1_command));
    bus_controller_settings->repeat_count = 1;
}

void reset_bus_controller_settings(bus_controller_settings_t* bus_controller_settings) {
    bus_controller_settings->is_started = VI_FALSE;
    bus_controller_settings->options = UNMMKO1_BC_DEFAULT;

    un_queue_clear(bus_controller_settings->schedule);
    bus_controller_settings->repeat_count = 1;
}

void destroy_bus_controller_settings(bus_controller_settings_t* bus_controller_settings) {
    un_queue_destroy(bus_controller_settings->schedule);
}
