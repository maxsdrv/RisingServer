#include "unmmko1.h"
#include "internal/unmmko1_internal.h"
#include "internal/unmmko1_mon_utilities.h"
#include "unmbase.h"
#include <stdlib.h>

//! \brief Функция unmmko1_mon_configure осуществляет настройку мезонина в режиме монитора шины.
//! Вызов функции также осуществляет сброс настроек монитора.
//! Если мезонин был запущен в каком-либо режиме работы, то также будет произведена остановка мезонина.
//! \param session Номер сеанса связи с мезонином.
//! \param mon_options Настройки монитора - объединение флагов UNMMKO1_MON_* из перечисления unmmko1_mon_options.
//! \return Код ошибки или код успешного выполнения функции.
ViStatus _VI_FUNC unmmko1_mon_configure(ViSession session, int mon_options) {
    ViStatus status = VI_SUCCESS;
    unmmko1_device_data* device_data = get_device_data_or_error(session);

    if (UNMMKO1_MODE_BUS_CONTROLLER == device_data->current_mode && device_data->bus_controller.is_started)
        unerror(unmmko1_bc_stop(session));
    else if (UNMMKO1_MODE_REMOTE_TERMINAL == device_data->current_mode && device_data->remote_terminal.is_started)
        unerror(unmmko1_rt_stop(session));
    else if (UNMMKO1_MODE_BUS_MONITOR == device_data->current_mode && device_data->bus_monitor.is_started)
        unerror(unmmko1_mon_stop(session));

    unerror(unmmko1_mon_reset(session));
    unerror(set_current_mode(session, UNMMKO1_MODE_BUS_MONITOR));
    unerror(set_connection_type(session, (mon_options & UNMMKO1_MON_DIRECT) ? UNMMKO1_DIRECT : UNMMKO1_TRANSFORM));
    device_data->bus_monitor.options = mon_options;

Error:
    return status;
}

//! \brief Функция unmmko1_mon_reset производит сброс настроек времени отсутствия ответа и фильтрации, удаление сообщений монитора.
//! Вызов функции не приводит к останову мезонина.
//! \param session Номер сеанса связи с мезонином.
//! \return Код ошибки или код успешного выполнения функции.
ViStatus _VI_FUNC unmmko1_mon_reset(ViSession session) {
    ViStatus status = VI_SUCCESS;
    unmmko1_device_data* device_data = get_device_data_or_error(session);
    reset_bus_monitor_settings(&device_data->bus_monitor);
    return status;
}

//! \brief Функция unmmko1_mon_set_timeout устанавливает значение времени отсутствия ответа, используемое монитором для разбора сообщений.
//! \param session Номер сеанса связи с мезонином.
//! \param timeout_in_us Значение времени отсутствия ответа в микросекундах.
//! \return Код ошибки или код успешного выполнения функции.
ViStatus _VI_FUNC unmmko1_mon_set_timeout(ViSession session, ViUInt16 timeout_in_us) {
    unmmko1_device_data* device_data = get_device_data_or_error(session);
    device_data->bus_monitor.accumulator.timeout_value_in_us = timeout_in_us;
    return VI_SUCCESS;
}

//! \brief Функция unmmko1_mon_filter_address позволяет установить фильтр по адресам оконечных устройств.
//! Фильтр определяется маской, заданный в аргументе addresses_mask.
//! Младший значащий бит аргумента отвечает за адрес оконечного устройства 0. Старший значащий бит - за адрес 31.
//! Если функция не используется, то мониторироваться будут все оконечные устройства.
//! \param session Номер сеанса связи с мезонином.
//! \param addresses_mask Маска адресов оконечных устройств.
//! \return Код ошибки или код успешного выполнения функции.
ViStatus _VI_FUNC unmmko1_mon_filter_address(ViSession session, ViUInt32 addresses_mask) {
    unmmko1_device_data* device_data = get_device_data_or_error(session);
    device_data->bus_monitor.filter_rules.addresses_mask = addresses_mask;
    return VI_SUCCESS;
}

//! \brief Функция unmmko1_mon_filter_subaddress позволяет установить фильтр по подадресам для конкретного оконечного устройства.
//! Фильтр определяется масками подадресов приёма и передачи данных, масками кодов команд приёма и передачи.
//! В каждой маске младший значащий бит отвечает за подадрес 0 или код команды 0. Старший значащий бит - за подадрес 31 или код команды 31.
//! Если функция не используется, то мониторироваться будут все сообщения оконечного устройства.
//! \param session Номер сеанса связи с мезонином.
//! \param address Адрес оконечного устройства.
//! \param receive_subaddresses Битовая маска подадресов приёма.
//! \param transmit_subaddresses Битовая маска подадресов передачи.
//! \param receive_modecodes Битовая маска команд управления приёма.
//! \param transmit_modecodes Битовая маска команд управления передачи.
//! \return Код ошибки или код успешного выполнения функции.
ViStatus _VI_FUNC unmmko1_mon_filter_subaddress(ViSession session, ViUInt16 address, ViUInt32 receive_subaddresses, ViUInt32 transmit_subaddresses, ViUInt32 receive_modecodes, ViUInt32 transmit_modecodes) {
    unmmko1_device_data* device_data = get_device_data_or_error(session);

    if (is_not_valid_uint16(address, 0, 31))
        return VI_ERROR_PARAMETER2;

    device_data->bus_monitor.filter_rules.receive_subaddresses[address] = receive_subaddresses;
    device_data->bus_monitor.filter_rules.transmit_subaddresses[address] = transmit_subaddresses;
    device_data->bus_monitor.filter_rules.receive_modecodes[address] = receive_modecodes;
    device_data->bus_monitor.filter_rules.transmit_modecodes[address] = transmit_modecodes;

    return VI_SUCCESS;
}

//! \brief Функция unmmko1_mon_start запускает мезонин в режиме монитора шины.
//! Настройки монитора шины предварительно устанавливаются функцией unmmko1_mon_configure.
//! Монитор шины допускается использовать совместно с режимами контроллера шины или оконечного устройства, и в этом случае вызывать unmmko1_mon_configure не надо.
//! \remark При запуске монитора шины удаляются ранее записанные сообщения.
//! \param session Номер сеанса связи с мезонином.
//! \return Код ошибки или код успешного выполнения функции.
ViStatus _VI_FUNC unmmko1_mon_start(ViSession session) {
    ViStatus status = VI_SUCCESS;
    ViUInt64 timeout_value_in_us = default_timeout_value_in_us;
    unmmko1_device_data* device_data = get_device_data_or_error(session);

    if (UNMMKO1_MODE_UNDEFINED == device_data->current_mode)
        unerror(unmmko1_mon_configure(session, UNMMKO1_MON_DEFAULT));

    if (device_data->bus_monitor.is_started)
        return UNMMKO1_WARNING_ALREADY_STARTED;

    // Настраиваем режима обмена
    unerror(unmbase_m_mode(session, UNMBASE_IOMODE_IN, UNMBASE_MODE_LOOP));

    // Запускаем чтение данных
    unerror(unmbase_m_out16(session, REGISTER_FIFO, 0xFF));
    unerror(unmbase_m_start(session, UNMBASE_IOMODE_IN));

    // Очищаем старые данные
    un_queue_clear(device_data->bus_monitor.messages);

    // Сбрасываем аккумулятор, сохраняя при этом настройки времени таймаута
    timeout_value_in_us = device_data->bus_monitor.accumulator.timeout_value_in_us;
    reset_accumulator(&device_data->bus_monitor.accumulator);
    device_data->bus_monitor.accumulator.timeout_value_in_us = timeout_value_in_us;

    // Запускаем монитор как самостоятельный режим, если это не контроллер и не оконечное устройство
    if (UNMMKO1_MODE_BUS_MONITOR == device_data->current_mode)
        unerror(start_mon(session, device_data->bus_monitor.options & UNMMKO1_USE_MASK));

    device_data->bus_monitor.is_started = VI_TRUE;

Error:
    return status;
}

//! \brief Функция unmmko1_mon_status возвращает состояние запуска мезонина в режиме монитора шины.
//! \param session Номер сеанса связи с мезонином.
//! \param status Состояние запуска монитора шины (VI_TRUE - монитора шины запущен, VI_FALSE - остановлен).
//! \return Код ошибки или код успешного выполнения функции.
ViStatus _VI_FUNC unmmko1_mon_status(ViSession session, ViBoolean* status) {
    unmmko1_device_data* device_data = get_device_data_or_error(session);

    if (is_not_valid_pointer(status))
        return VI_ERROR_PARAMETER2;

    *status = device_data->bus_monitor.is_started;
    return VI_SUCCESS;
}

//! \brief Функция unmmko1_mon_stop останавливает мезонин, запущенный ранее в режиме монитора шины.
//! Если монитор шины используется совместно с режимами контроллера шины или оконечного устройства, то вызов функции приведёт к остановке только монитора шины.
//! Считанные монитором шины сообщения можно запросить с помощью функций unmmko1_mon_messages_count и unmmko1_mon_messages_read.
//! \param session Номер сеанса связи с мезонином.
//! \return Код ошибки или код успешного выполнения функции.
ViStatus _VI_FUNC unmmko1_mon_stop(ViSession session) {
    ViStatus status = VI_SUCCESS;
    unmmko1_device_data* device_data = get_device_data_or_error(session);

    if (UNMMKO1_MODE_UNDEFINED == device_data->current_mode)
        return UNMMKO1_ERROR_WAS_CONFIGURED_IN_A_DIFFERENT_MODE;

    if (!device_data->bus_monitor.is_started)
        return UNMMKO1_WARNING_ALREADY_STOPPED;

    // Останавливаем чтение данных
    unerror(unmbase_m_async_stop(session, UNMBASE_IOMODE_IN));

    // Останавливаем монитор как самостоятельный режим, если это не контроллер и не оконечное устройство
    if (UNMMKO1_MODE_BUS_MONITOR == device_data->current_mode)
        unerror(stop_mon(session));
    device_data->bus_monitor.is_started = VI_FALSE;

Error:
    return status;
}

//! \brief Функция unmmko1_read_milstd1553_words используется для чтения данных из FIFO и преобразования их в слова МКО.
//! \return Код ошибки или код успешного выполнения функции.
ViStatus unmmko1_read_milstd1553_words(ViSession session, un_queue* words) {
    ViStatus status = VI_SUCCESS;
    ViUInt32 data_count = 0;
    size_t word_count = 0;
    unmmko1_device_data* device_data = get_device_data_or_error(session);

    // Запрашиваем количество готовых данных
    unerror(unmbase_m_howmuch_data_q(session, UNMBASE_IOMODE_IN, &data_count));

    // Каждое слово монитора закодировано 64-битными словами, поэтому выравниваем количество данных по 2 32-битных слова
    word_count = data_count / 2;
    data_count = word_count * 2;

    // Если данные есть, то сохраняем их и отправляем на обработку
    if (data_count > 0) {
        // Выделяем память под данные
        ViUInt32* data = calloc(data_count, sizeof(ViUInt32));
        if (NULL == data)
            return 1;

        // Считываем данные
        unerror(unmbase_m_read_packet(session, data_count, data, &data_count));

        // Разбираем считанные данные по словам
        {
            size_t word_index = 0;
            milstd1553_word_s word;

            for (word_index = 0; word_index < word_count; ++word_index) {
                ViUInt32 w1 = data[2 * word_index];
                ViUInt32 w2 = data[2 * word_index + 1];

                word.value = (ViUInt16)(w1 & 0xffff);
                word.state = (ViUInt8)((w1 >> 16) & 0xff);
                word.timestamp = (((ViUInt64)w2) << 8) | (w1 >>24);

                un_queue_push_back(words, &word);
            }
        }

        // Освобождаем память
        free(data);
    }

Error:
    return status;
}

//! \brief Функция unmmko1_mon_messages_count служит для запроса количества сообщений, считанными монитором шины.
//! Допустимо использовать функцию как в процессе работы мезонина в режиме монитора шины (после unmmko1_mon_start),
//! так и после останова монитора (функцией unmmko1_mon_stop).
//! \param session Номер сеанса связи с мезонином.
//! \param[out] messages_count Количество считанных сообщений.
//! \return Код ошибки или код успешного выполнения функции.
ViStatus _VI_FUNC unmmko1_mon_messages_count(ViSession session, ViUInt32* messages_count) {
    ViStatus status = VI_SUCCESS;
    un_queue* words = NULL;
    un_queue* messages = NULL;
    unmmko1_device_data* device_data = get_device_data_or_error(session);

    if (is_not_valid_pointer(messages_count))
        return UNMMKO1_ERROR_INTERNAL;

    unerror(get_current_timestamp(session, &device_data->bus_monitor.accumulator.current_timestamp));

    words = un_queue_create(sizeof(milstd1553_word_s));
    unerror(unmmko1_read_milstd1553_words(session, words));

    messages = un_queue_create(sizeof(unmmko1_message));
    unmmko1_parse_words(words, &device_data->bus_monitor.accumulator, messages);
    unmmko1_filter_messages(messages, &device_data->bus_monitor.filter_rules, device_data->bus_monitor.messages);
    *messages_count = (ViUInt32)un_queue_size(device_data->bus_monitor.messages);

Error:
    un_queue_clear(words);
    un_queue_destroy(words);
    un_queue_clear(messages);
    un_queue_destroy(messages);
    return status;
}

//! \brief Функция unmmko1_mon_messages_read обеспечивает чтение сообщений в память компьютера.
//! Допустимо использовать функцию как в процессе работы мезонина в режиме монитора шины (после unmmko1_mon_start),
//! так и после останова монитора (функцией unmmko1_mon_stop).
//! \param session Номер сеанса связи с мезонином.
//! \param[in] messages_count Количество сообщений, которое необходимо считать.
//! \param[in,out] messages Массив, в который считываются готовые сообщения. Массив должен состоять как минимум из messages_count элементов типа unmmko1_message.
//! \param[out] read_messages_count Количество считанных сообщений в messages.
//! \return Код ошибки или код успешного выполнения функции.
ViStatus _VI_FUNC unmmko1_mon_messages_read(ViSession session, ViUInt32 messages_count, unmmko1_message* messages, ViUInt32* read_messages_count) {
    ViStatus status = VI_SUCCESS;
    unmmko1_message message;
    un_queue* words = NULL;
    un_queue* new_messages = NULL;
    ViUInt32 messages_index = 0;
    unmmko1_device_data* device_data = get_device_data_or_error(session);

    if (is_not_valid_pointer(messages) || is_not_valid_pointer(read_messages_count))
        return UNMMKO1_ERROR_INTERNAL;

    unerror(get_current_timestamp(session, &device_data->bus_monitor.accumulator.current_timestamp));

    words = un_queue_create(sizeof(milstd1553_word_s));
    unerror(unmmko1_read_milstd1553_words(session, words));

    new_messages = un_queue_create(sizeof(unmmko1_message));
    unmmko1_parse_words(words, &device_data->bus_monitor.accumulator, new_messages);
    unmmko1_filter_messages(new_messages, &device_data->bus_monitor.filter_rules, device_data->bus_monitor.messages);

    *read_messages_count = MIN((ViUInt32)un_queue_size(device_data->bus_monitor.messages), messages_count);
    for (messages_index = 0; messages_index < *read_messages_count; ++messages_index) {
        un_queue_pop_first(device_data->bus_monitor.messages, &message);
        messages[messages_index] = message;
    }

Error:
    un_queue_clear(words);
    un_queue_destroy(words);
    un_queue_clear(new_messages);
    un_queue_destroy(new_messages);
    return status;
}
