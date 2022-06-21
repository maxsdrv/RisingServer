#include "unmmko1.h"

#include <stdlib.h>
#include <string.h>
#include <unmbase.h>
#include <stdio.h>
#include <time.h>
#include "internal/unmmko1_internal.h"

#define UNMMKO1_APP_VERSION "1.0.0"

//! \brief Функция unmmko1_init производит действия по инициализации мезонина.
//! \param resource_name Данная переменная указывает тип интерфейса и адрес устройства для инструмента, с которым открывается сеанс.
//! \param idn_query Данный параметр определяет необходимость запроса идентификатора мезонина в процедуре инициализации.
//! \param do_reset Данный параметр определяет необходимость сброса мезонина в процедуре инициализации.
//! \param session В данной переменной функция возвращает уникальный номер сеанса связи с мезонина, который необходимо сохранить для всех последующих вызовов функций драйвера мезонина.
//! \return Код ошибки или код успешного выполнения функции.
ViStatus _VI_FUNC unmmko1_init(ViRsrc resource_name, ViBoolean idn_query, ViBoolean do_reset, ViSession* session) {
    ViStatus status = VI_SUCCESS;
    unmmko1_device_data* device_data = NULL;
    ViSession temp_session = 0;
    ViSession defaultRM = 0;

    if (is_not_valid_boolean(idn_query))
        return VI_ERROR_PARAMETER2;
    if (is_not_valid_boolean(do_reset))
        return VI_ERROR_PARAMETER3;
    if (is_not_valid_pointer(session))
        return VI_ERROR_PARAMETER4;

    // Открываем сессию VISA
    unerror(viOpenDefaultRM(&defaultRM));

    // Открываем сессию мезонина
    unerror(viOpen(defaultRM, resource_name, VI_NULL, VI_NULL, &temp_session));

    // Создаём данные мезонина
    unerror(create_device_data(&device_data));

    // Сохраняем указатель на переменные сеанса
    unerror(viSetAttribute(temp_session, VI_ATTR_USER_DATA, (ViAttrState)device_data));

    // Запоминаем сессию
    device_data->session = 0;
    device_data->init_session = temp_session;
    *session = device_data->init_session;

    return status;

Error:
    if (is_valid_pointer(device_data))
        free(device_data);
    if (is_valid_session(temp_session))
        viClose(temp_session);
    if (is_valid_session(defaultRM))
        viClose(defaultRM);
    return status;
}

//! \brief Функция unmmko1_connect готовит к работе сеанс мезонина, открытый ранее с помощью функции инициализации.
//! Функцию необходимо вызывать один раз сразу после инициализации мезонина.
//! \param session Номер сеанса связи с мезонином.
//! \param carrier_session Номер сеанса связи с носителем мезонинов.
//! \param mezzanine_number Позиция мезонина на носителе мезонинов.
//! \param idn_query Данный параметр определяет необходимость запроса идентификатора мезонина.
//! \param do_reset Данный параметр определяет необходимость сброса мезонина.
//! \return Код ошибки или код успешного выполнения функции.
ViStatus _VI_FUNC unmmko1_connect(ViSession session, ViSession carrier_session, ViUInt16 mezzanine_number, ViBoolean idn_query, ViBoolean do_reset) {
    ViStatus status = VI_SUCCESS;
    ViSession temp_session = 0;
    unmmko1_device_data* device_data = get_device_data_from_visa(session);

    if (is_not_valid_device_data(device_data))
        return VI_ERROR_INV_SETUP;
    if (is_not_valid_session(carrier_session))
        return VI_ERROR_PARAMETER2;
    if (mezzanine_number < 1 || mezzanine_number > 8)
        return VI_ERROR_PARAMETER3;
    if (is_not_valid_boolean(idn_query))
        return VI_ERROR_PARAMETER4;
    if (is_not_valid_boolean(do_reset))
        return VI_ERROR_PARAMETER5;

    // Открытие сеанса связи с базой
    if ((status = unmbase_m_init(carrier_session, mezzanine_number, &temp_session)) < 0)
        goto Fail;

    device_data->carrier_session = carrier_session;
    device_data->session = temp_session;

    // Устанавливаем связь с носителем мезонинов
    unfail(unmbase_m_set_attribute(device_data->session, UNMBASE_MATTR_MEZ_EXTVI, (ViAttrState)session));

    // Устанавливаем асинхронный режим
    unfail(unmbase_m_set_attribute(session, UNMBASE_MATTR_ASYNC, (ViAttrState)1));

    // Сохраняем указатель на переменные сеанса
    unfail(unmbase_m_set_attribute(session, UNMBASE_MATTR_USER_DATA, (ViAttrState)device_data));

    // Запрос ID
    if (VI_TRUE == idn_query) {
        ViInt16 present = 0, idn_value = 0;
        unfail(unmbase_m_type_q(carrier_session, (ViInt16)mezzanine_number, &present, &idn_value));

        if ((idn_value & 0xFF) != UNMMKO1_MODEL_CODE)
            unfail(VI_ERROR_FAIL_ID_QUERY);
    }

    // Настраиваем ввод/вывод
    {
        // Настраиваем задержку первых данных
        unfail(unmbase_m_first_delay(session, UNMBASE_IOMODE_IN,  M_FIRST_DELAY));
        unfail(unmbase_m_first_delay(session, UNMBASE_IOMODE_OUT, M_FIRST_DELAY));
        // Настраиваем частоту временных отсчётов
        unfail(unmbase_m_clock(session, UNMBASE_IOMODE_IN,  M_CLOCK));
        unfail(unmbase_m_clock(session, UNMBASE_IOMODE_OUT, M_CLOCK));
        // Настраиваем ширину кадра
        unfail(unmbase_m_sample_width(session, UNMBASE_IOMODE_IN,  M_SAMPLE_WORDS));
        unfail(unmbase_m_sample_width(session, UNMBASE_IOMODE_OUT, M_SAMPLE_WORDS));

        // Триггер - уровень
        unfail(unmbase_m_trig_length(session, 1));

        // Настраиваем блочный обмен на ввод и вывод
        unfail(unmbase_m_mode(session, UNMBASE_IOMODE_IN,  UNMBASE_MODE_BLOCK));
        unfail(unmbase_m_mode(session, UNMBASE_IOMODE_OUT, UNMBASE_MODE_BLOCK));
    }

    // Выделяем память мезонину, разделяя память поровну между всеми мезонинами
    {
        ViInt32 mezzanine, mezzanine_count;
        ViUInt32 memory_size, memory_chunk;

        unfail(unmbase_mem_q(carrier_session, &memory_size));
        if (0 == memory_size)
            unfail(UNMMKO1_ERROR_NOT_ENOUGH_MEMORY);

        mezzanine_count = 0;
        for (mezzanine = 1; mezzanine <= 4; ++mezzanine) {
            ViInt16 present = 0, mtype = 0;
            unmbase_m_type_q(carrier_session, (ViInt16)mezzanine, &present, &mtype);
            if (present)
                mezzanine_count++;
        }

        // Начальный размер памяти
        memory_size /= (ViUInt32)mezzanine_count;

        // Дискрет уменьшения размера памяти
        memory_chunk = (ViUInt32)(~0xFF) & (memory_size / 16);

        // Сначала освободим память, если была занята
        unfail(unmbase_m_alloc(session, UNMBASE_IOMODE_IN,  0, VI_NULL));
        unfail(unmbase_m_alloc(session, UNMBASE_IOMODE_OUT, 0, VI_NULL));

        memory_size += memory_chunk;
        do {
            ViUInt32 addr;
            memory_size -= memory_chunk;
            if (memory_size <= 0)
                unfail(UNMMKO1_ERROR_NOT_ENOUGH_MEMORY);

            status = unmbase_m_alloc(session, UNMBASE_IOMODE_IN, memory_size / 2, &addr);
            if (status >= 0)
                status = unmbase_m_alloc(session, UNMBASE_IOMODE_OUT, memory_size / 2, &addr);
        } while (status && memory_chunk);

        unfail(status);
    }

    {
        // Сброс
        unmmko1_reset(session);

        // Производим тестовый запуск и останов мезонина
        unmbase_m_out16(session, REGISTER_FIFO, 0xFF);
        unmbase_m_start(session, UNMBASE_IOMODE_BOTH);
        unmbase_m_stop(session,  UNMBASE_IOMODE_BOTH);

        // Повторный сброс
        unmmko1_reset(session);
    }

    // Заполняем данные мезонина
    unfail(fill_device_data(device_data));

    // Устанавливаем обработчик событий от носителя мезонина
    unfail(unmbase_m_handler(session, (ViAddr)(&interrupt_request_handler)));

    // Разрешаем прерывания
    unfail(unmbase_m_config_event(session, VI_ON));

    return status;

Fail:
    if (is_valid_session(session))
        unmbase_m_close(session);
    return status;
}

//! \brief Функция unmmko1_self_test производит самоконтроль мезонина и возвращает его результат.
//! \param session Номер сеанса связи с мезонином.
//! \param result Код результата самоконтроля.
//! \param message Сообщение о результате самоконтроля.
//! \return Код ошибки или код успешного выполнения функции.
ViStatus _VI_FUNC unmmko1_self_test(ViSession session, ViInt16* result, ViChar message[]) {
    ViStatus status = VI_SUCCESS;
    unmmko1_device_data* device_data = get_device_data_or_error(session);

    if (is_not_valid_pointer(result))
        return VI_ERROR_PARAMETER2;
    if (is_not_valid_pointer(message))
        return VI_ERROR_PARAMETER3;

    // Останавливаем мезонин и сбрасываем все настройки
    unerror(unmmko1_reset(session));

    // Выполняем процедуру тестирования
    status = self_test(session);
    *result = (ViInt16)status;
    if (0 == status)
        strcpy(message, "Самоконтроль пройден успешно.");
    else if (-1 == status)
        strcpy(message, "Ошибка FIFO.");
    else if (-2 == status)
        strcpy(message, "Ошибка кода модели.");
    else if (-3 == status)
        strcpy(message, "Ошибка памяти.");
    else {
        unmmko1_error_message(session, status, message);
        *result = -1;
    }

    // Сбрасываем настройки мезонина
    unmmko1_reset(session);
    return (0 == *result ? VI_SUCCESS : UNMMKO1_ERROR_SELFTEST);

Error:
    *result = (ViInt16)status;
    unmmko1_error_message(session, status, message);
    unmmko1_reset(session);
    return status;
}

ViBoolean wait_for_monitoring_one_message(ViSession session, unmmko1_message* message) {
    ViUInt32 message_count = 0;
    clock_t start_time = 0, elapsed_time = 0;
    const clock_t timeout = 5 * CLOCKS_PER_SEC;

    start_time = clock();
    do {
        unmmko1_mon_messages_count(session, &message_count);
        if (message_count > 0)
            break;

        un_sleep(5);
        elapsed_time = clock() - start_time;
    } while (0 == message_count && elapsed_time < timeout);

    if (message_count > 0)
        unmmko1_mon_messages_read(session, 1, message, &message_count);

    return (message_count > 0);
}

ViBoolean compare_messages(unmmko1_message* message, ViUInt16 activities, ViUInt16 errors, unmmko1_command command,
                           ViUInt16 response_1_status_word, ViUInt16 response_1_data_words_count, ViUInt16 response_1_data_words[32],
ViUInt16 response_2_status_word, ViUInt16 response_2_data_words_count, ViUInt16 response_2_data_words[32]) {
    if (message->activity != activities)
        return VI_FALSE;
    if (message->error != errors)
        return VI_FALSE;
    if (message->command.command_word_1 != command.command_word_1)
        return VI_FALSE;
    if (message->command.command_word_2 != command.command_word_2)
        return VI_FALSE;
    if (message->command.data_words_count != command.data_words_count)
        return VI_FALSE;
    if (memcmp(message->command.data_words, command.data_words, sizeof(message->command.data_words)))
        return VI_FALSE;
    if (message->response_1.status_word != response_1_status_word)
        return VI_FALSE;
    if (message->response_1.data_words_count != response_1_data_words_count)
        return VI_FALSE;
    if (memcmp(message->response_1.data_words, response_1_data_words, sizeof(message->response_1.data_words)))
        return VI_FALSE;
    if (message->response_2.status_word != response_2_status_word)
        return VI_FALSE;
    if (message->response_2.data_words_count != response_2_data_words_count)
        return VI_FALSE;
    if (memcmp(message->response_2.data_words, response_2_data_words, sizeof(message->response_2.data_words)))
        return VI_FALSE;

    return VI_TRUE;
}

//! \brief Функция unmmko1_test_exchange производит тестирование обмена в различных режимах работы мезонина.
//! Тестирование обмена - длительная операция.
//! \param session Номер сеанса связи с мезонином.
//! \param result Код результата тестирования.
//! \param message Сообщение о результате тестирования.
//! \return Код ошибки или код успешного выполнения функции.
ViStatus _VI_FUNC unmmko1_test_exchange(ViSession session, ViInt16* result, ViChar message[]) {
    ViStatus status = VI_SUCCESS;
    unmmko1_message m;
    ViUInt16 data_words[32] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32};
    ViUInt16 zero_data_words[32] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    ViUInt16 one_data_words[32] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    ViUInt16 data_words_queue[256];
    ViUInt16 index;
    ViBoolean message_received = VI_FALSE;

    unmmko1_device_data* device_data = get_device_data_or_error(session);

    if (is_not_valid_pointer(result))
        return VI_ERROR_PARAMETER2;
    if (is_not_valid_pointer(message))
        return VI_ERROR_PARAMETER3;

    // Останавливаем мезонин и сбрасываем все настройки
    unerror(unmmko1_reset(session));

    // Выполняем процедуру тестирования
    // Режим монитора
    {
        unmmko1_command command_f1 = unmmko1_f1(UNMMKO1_BUS_A, RT_1, SA_2, 32, data_words);

        // Мониторирование на магистрали A
        unerror(unmmko1_mon_configure(session, UNMMKO1_MON_DIRECT | UNMMKO1_MON_BUS_A));
        unerror(unmmko1_mon_start(session));
        command_f1.activity = UNMMKO1_MSG_ACT_BUS_B | UNMMKO1_MSG_ACT_CWD_1;
        unerror(unmmko1_bc_transmit_command(session, command_f1));
        message_received = wait_for_monitoring_one_message(session, &m);
        unerror(unmmko1_mon_stop(session));
        if (!message_received || !compare_messages(&m, UNMMKO1_MSG_ACT_BUS_A | UNMMKO1_MSG_ACT_CWD_1, UNMMKO1_MSG_ERR_NO_RESPONSE | UNMMKO1_MSG_ERR_PROTOCOL, command_f1,
                              0, 0, zero_data_words, 0, 0, zero_data_words))
            fail_test(0x0001, "Ошибка монитора (магистраль A)");

        // Мониторирование на магистрали B
        unerror(unmmko1_mon_configure(session, UNMMKO1_MON_DIRECT | UNMMKO1_MON_BUS_B));
        unerror(unmmko1_mon_start(session));
        command_f1.activity = UNMMKO1_MSG_ACT_BUS_A | UNMMKO1_MSG_ACT_CWD_1;
        unerror(unmmko1_bc_transmit_command(session, command_f1));
        message_received = wait_for_monitoring_one_message(session, &m);
        unerror(unmmko1_mon_stop(session));
        if (!message_received || !compare_messages(&m, UNMMKO1_MSG_ACT_BUS_B | UNMMKO1_MSG_ACT_CWD_1, UNMMKO1_MSG_ERR_NO_RESPONSE | UNMMKO1_MSG_ERR_PROTOCOL, command_f1,
                              0, 0, zero_data_words, 0, 0, zero_data_words))
            fail_test(0x0002, "Ошибка монитора (магистраль B)");
    }

    // Режим оконечного устройства
    {
        // Формат сообщения 1
        {
            unmmko1_command command_f1 = unmmko1_f1(UNMMKO1_BUS_A, RT_1, SA_2, 32, data_words);

            // Магистраль A
            unerror(unmmko1_rt_configure(session, 1 << RT_1, UNMMKO1_RT_DIRECT | UNMMKO1_RT_BUS_A | UNMMKO1_RT_DEFAULT_RESPONSES));
            unerror(unmmko1_rt_start(session));
            unerror(unmmko1_mon_start(session));
            command_f1.activity = UNMMKO1_MSG_ACT_BUS_B | UNMMKO1_MSG_ACT_CWD_1;
            unerror(unmmko1_bc_transmit_command(session, command_f1));
            message_received = wait_for_monitoring_one_message(session, &m);
            unerror(unmmko1_mon_stop(session));
            unerror(unmmko1_rt_stop(session));
            if (!message_received || !compare_messages(&m, UNMMKO1_MSG_ACT_BUS_A | UNMMKO1_MSG_ACT_CWD_1 | UNMMKO1_MSG_ACT_SWD_1, UNMMKO1_MSG_ERR_OK, command_f1,
                                  unmmko1_pack_sw(RT_1, 0), 0, zero_data_words, 0, 0, zero_data_words))
                fail_test(0x0003, "Ошибка оконечного устройства (магистраль A): формат сообщения 1");

            // Магистраль B
            unerror(unmmko1_rt_configure(session, 1 << RT_1, UNMMKO1_RT_DIRECT | UNMMKO1_RT_BUS_B | UNMMKO1_RT_DEFAULT_RESPONSES));
            unerror(unmmko1_rt_start(session));
            unerror(unmmko1_mon_start(session));
            command_f1.activity = UNMMKO1_MSG_ACT_BUS_A | UNMMKO1_MSG_ACT_CWD_1;
            unerror(unmmko1_bc_transmit_command(session, command_f1));
            message_received = wait_for_monitoring_one_message(session, &m);
            unerror(unmmko1_mon_stop(session));
            unerror(unmmko1_rt_stop(session));
            if (!message_received || !compare_messages(&m, UNMMKO1_MSG_ACT_BUS_B | UNMMKO1_MSG_ACT_CWD_1 | UNMMKO1_MSG_ACT_SWD_1, UNMMKO1_MSG_ERR_OK, command_f1,
                                  unmmko1_pack_sw(RT_1, 0), 0, zero_data_words, 0, 0, zero_data_words))
                fail_test(0x0004, "Ошибка оконечного устройства (магистраль B): формат сообщения 1");
        }

        // Формат сообщения 2
        {
            unmmko1_command command_f2 = unmmko1_f2(UNMMKO1_BUS_B, RT_1, SA_2, 32);

            // Магистраль A
            unerror(unmmko1_rt_configure(session, 1 << RT_1, UNMMKO1_RT_DIRECT | UNMMKO1_RT_BUS_A | UNMMKO1_RT_DEFAULT_RESPONSES));
            unerror(unmmko1_rt_set_subaddress_data(session, RT_1, SA_2, 32, data_words));
            unerror(unmmko1_rt_start(session));
            unerror(unmmko1_mon_start(session));
            command_f2.activity = UNMMKO1_MSG_ACT_BUS_B | UNMMKO1_MSG_ACT_CWD_1;
            unerror(unmmko1_bc_transmit_command(session, command_f2));
            message_received = wait_for_monitoring_one_message(session, &m);
            unerror(unmmko1_mon_stop(session));
            unerror(unmmko1_rt_stop(session));
            if (!message_received || !compare_messages(&m, UNMMKO1_MSG_ACT_BUS_A | UNMMKO1_MSG_ACT_CWD_1 | UNMMKO1_MSG_ACT_SWD_1, UNMMKO1_MSG_ERR_OK, command_f2,
                                  unmmko1_pack_sw(RT_1, 0), 32, data_words, 0, 0, zero_data_words))
                fail_test(0x0005, "Ошибка оконечного устройства (магистраль A): формат сообщения 2");

            // Магистраль B
            unerror(unmmko1_rt_configure(session, 1 << RT_1, UNMMKO1_RT_DIRECT | UNMMKO1_RT_BUS_B | UNMMKO1_RT_DEFAULT_RESPONSES));
            unerror(unmmko1_rt_set_subaddress_data(session, RT_1, SA_2, 32, data_words));
            unerror(unmmko1_rt_start(session));
            unerror(unmmko1_mon_start(session));
            command_f2.activity = UNMMKO1_MSG_ACT_BUS_A | UNMMKO1_MSG_ACT_CWD_1;
            unerror(unmmko1_bc_transmit_command(session, command_f2));
            message_received = wait_for_monitoring_one_message(session, &m);
            unerror(unmmko1_mon_stop(session));
            unerror(unmmko1_rt_stop(session));
            if (!message_received || !compare_messages(&m, UNMMKO1_MSG_ACT_BUS_B | UNMMKO1_MSG_ACT_CWD_1 | UNMMKO1_MSG_ACT_SWD_1, UNMMKO1_MSG_ERR_OK, command_f2,
                                  unmmko1_pack_sw(RT_1, 0), 32, data_words, 0, 0, zero_data_words))
                fail_test(0x0006, "Ошибка оконечного устройства (магистраль B): формат сообщения 2");
        }

        // Формат сообщения 2 в режиме очереди
        {
            unmmko1_command command_f2 = unmmko1_f2(UNMMKO1_BUS_B, RT_1, SA_2, 32);
            for (index = 0; index < 256; ++index)
                data_words_queue[index] = index;

            // Магистраль A
            unerror(unmmko1_rt_configure(session, 1 << RT_1, UNMMKO1_RT_DIRECT | UNMMKO1_RT_BUS_A | UNMMKO1_RT_DEFAULT_RESPONSES));
            unerror(unmmko1_rt_set_subaddress_options(session, RT_1, SA_2, UNMMKO1_RT_SUBADDRESS_QUEUE));
            unerror(unmmko1_rt_set_subaddress_data(session, RT_1, SA_2, 256, data_words_queue));

            unerror(unmmko1_rt_start(session));
            unerror(unmmko1_mon_start(session));
            command_f2.activity = UNMMKO1_MSG_ACT_BUS_B | UNMMKO1_MSG_ACT_CWD_1;
            for (index = 0; index < 256 / 32; ++index) {
                unerror(unmmko1_bc_transmit_command(session, command_f2));
                un_sleep(10);
            }
            unerror(unmmko1_mon_stop(session));
            unerror(unmmko1_rt_stop(session));

            for (index = 0; index < 256 / 32; ++index) {
                message_received = wait_for_monitoring_one_message(session, &m);
                if (!message_received || !compare_messages(&m, UNMMKO1_MSG_ACT_BUS_A | UNMMKO1_MSG_ACT_CWD_1 | UNMMKO1_MSG_ACT_SWD_1, UNMMKO1_MSG_ERR_OK, command_f2,
                                      unmmko1_pack_sw(RT_1, 0), 32, data_words_queue + index * 32, 0, 0, zero_data_words))
                    fail_test(0x0007, "Ошибка оконечного устройства (магистраль A): формат сообщения 2 в режиме очереди");
            }

            // Магистраль B
            unerror(unmmko1_rt_configure(session, 1 << RT_1, UNMMKO1_RT_DIRECT | UNMMKO1_RT_BUS_B | UNMMKO1_RT_DEFAULT_RESPONSES));
            unerror(unmmko1_rt_set_subaddress_options(session, RT_1, SA_2, UNMMKO1_RT_SUBADDRESS_QUEUE));
            unerror(unmmko1_rt_set_subaddress_data(session, RT_1, SA_2, 256, data_words_queue));

            unerror(unmmko1_rt_start(session));
            unerror(unmmko1_mon_start(session));
            command_f2.activity = UNMMKO1_MSG_ACT_BUS_A | UNMMKO1_MSG_ACT_CWD_1;
            for (index = 0; index < 256 / 32; ++index) {
                unerror(unmmko1_bc_transmit_command(session, command_f2));
                un_sleep(10);
            }
            unerror(unmmko1_mon_stop(session));
            unerror(unmmko1_rt_stop(session));

            for (index = 0; index < 256 / 32; ++index) {
                message_received = wait_for_monitoring_one_message(session, &m);
                if (!message_received || !compare_messages(&m, UNMMKO1_MSG_ACT_BUS_B | UNMMKO1_MSG_ACT_CWD_1 | UNMMKO1_MSG_ACT_SWD_1, UNMMKO1_MSG_ERR_OK, command_f2,
                                      unmmko1_pack_sw(RT_1, 0), 32, data_words_queue + index * 32, 0, 0, zero_data_words))
                    fail_test(0x0008, "Ошибка оконечного устройства (магистраль B): формат сообщения 2 в режиме очереди");
            }
        }

        // Формат сообщения 4
        {
            unmmko1_command command_f4 = unmmko1_f4(UNMMKO1_BUS_B, RT_1, SA_MC0, 1);

            // Магистраль A
            unerror(unmmko1_rt_configure(session, 1 << RT_1, UNMMKO1_RT_DIRECT | UNMMKO1_RT_BUS_A | UNMMKO1_RT_DEFAULT_RESPONSES));
            unerror(unmmko1_rt_start(session));
            unerror(unmmko1_mon_start(session));
            command_f4.activity = UNMMKO1_MSG_ACT_BUS_B | UNMMKO1_MSG_ACT_CWD_1;
            unerror(unmmko1_bc_transmit_command(session, command_f4));
            message_received = wait_for_monitoring_one_message(session, &m);
            unerror(unmmko1_mon_stop(session));
            unerror(unmmko1_rt_stop(session));
            if (!message_received || !compare_messages(&m, UNMMKO1_MSG_ACT_BUS_A | UNMMKO1_MSG_ACT_CWD_1 | UNMMKO1_MSG_ACT_SWD_1, UNMMKO1_MSG_ERR_OK, command_f4,
                                  unmmko1_pack_sw(RT_1, 0), 0, zero_data_words, 0, 0, zero_data_words))
                fail_test(0x0009, "Ошибка оконечного устройства (магистраль A): формат сообщения 4");

            // Магистраль B
            unerror(unmmko1_rt_configure(session, 1 << RT_1, UNMMKO1_RT_DIRECT | UNMMKO1_RT_BUS_B | UNMMKO1_RT_DEFAULT_RESPONSES));
            unerror(unmmko1_rt_start(session));
            unerror(unmmko1_mon_start(session));
            command_f4.activity = UNMMKO1_MSG_ACT_BUS_A | UNMMKO1_MSG_ACT_CWD_1;
            unerror(unmmko1_bc_transmit_command(session, command_f4));
            message_received = wait_for_monitoring_one_message(session, &m);
            unerror(unmmko1_mon_stop(session));
            unerror(unmmko1_rt_stop(session));
            if (!message_received || !compare_messages(&m, UNMMKO1_MSG_ACT_BUS_B | UNMMKO1_MSG_ACT_CWD_1 | UNMMKO1_MSG_ACT_SWD_1, UNMMKO1_MSG_ERR_OK, command_f4,
                                  unmmko1_pack_sw(RT_1, 0), 0, zero_data_words, 0, 0, zero_data_words))
                fail_test(0x000a, "Ошибка оконечного устройства (магистраль B): формат сообщения 4");
        }

        // Формат сообщения 5
        {
            ViUInt16 data_word = 0x5432u;
            unmmko1_command command_f5 = unmmko1_f5(UNMMKO1_BUS_B, RT_1, SA_MC0, 16);

            // Магистраль A
            unerror(unmmko1_rt_configure(session, 1 << RT_1, UNMMKO1_RT_DIRECT | UNMMKO1_RT_BUS_A | UNMMKO1_RT_DEFAULT_RESPONSES));
            unerror(unmmko1_rt_set_command_data(session, RT_1, 16, data_word));
            unerror(unmmko1_rt_start(session));
            unerror(unmmko1_mon_start(session));
            command_f5.activity = UNMMKO1_MSG_ACT_BUS_B | UNMMKO1_MSG_ACT_CWD_1;
            unerror(unmmko1_bc_transmit_command(session, command_f5));
            message_received = wait_for_monitoring_one_message(session, &m);
            unerror(unmmko1_mon_stop(session));
            unerror(unmmko1_rt_stop(session));
            one_data_words[0] = data_word;
            if (!message_received || !compare_messages(&m, UNMMKO1_MSG_ACT_BUS_A | UNMMKO1_MSG_ACT_CWD_1 | UNMMKO1_MSG_ACT_SWD_1, UNMMKO1_MSG_ERR_OK, command_f5,
                                  unmmko1_pack_sw(RT_1, 0), 1, one_data_words, 0, 0, zero_data_words))
                fail_test(0x000b, "Ошибка оконечного устройства (магистраль A): формат сообщения 5");

            // Магистраль B
            unerror(unmmko1_rt_configure(session, 1 << RT_1, UNMMKO1_RT_DIRECT | UNMMKO1_RT_BUS_B | UNMMKO1_RT_DEFAULT_RESPONSES));
            unerror(unmmko1_rt_set_command_data(session, RT_1, 16, data_word));
            unerror(unmmko1_rt_start(session));
            unerror(unmmko1_mon_start(session));
            command_f5.activity = UNMMKO1_MSG_ACT_BUS_A | UNMMKO1_MSG_ACT_CWD_1;
            unerror(unmmko1_bc_transmit_command(session, command_f5));
            message_received = wait_for_monitoring_one_message(session, &m);
            unerror(unmmko1_mon_stop(session));
            unerror(unmmko1_rt_stop(session));
            if (!message_received || !compare_messages(&m, UNMMKO1_MSG_ACT_BUS_B | UNMMKO1_MSG_ACT_CWD_1 | UNMMKO1_MSG_ACT_SWD_1, UNMMKO1_MSG_ERR_OK, command_f5,
                                  unmmko1_pack_sw(RT_1, 0), 1, one_data_words, 0, 0, zero_data_words))
                fail_test(0x000c, "Ошибка оконечного устройства (магистраль B): формат сообщения 5");
        }

        // Формат сообщения 6
        {
            unmmko1_command command_f6 = unmmko1_f6(UNMMKO1_BUS_B, RT_1, SA_MC0, 17, 0);

            // Магистраль A
            unerror(unmmko1_rt_configure(session, 1 << RT_1, UNMMKO1_RT_DIRECT | UNMMKO1_RT_BUS_A | UNMMKO1_RT_DEFAULT_RESPONSES));
            unerror(unmmko1_rt_start(session));
            unerror(unmmko1_mon_start(session));
            command_f6.activity = UNMMKO1_MSG_ACT_BUS_B | UNMMKO1_MSG_ACT_CWD_1;
            unerror(unmmko1_bc_transmit_command(session, command_f6));
            message_received = wait_for_monitoring_one_message(session, &m);
            unerror(unmmko1_mon_stop(session));
            unerror(unmmko1_rt_stop(session));
            if (!message_received || !compare_messages(&m, UNMMKO1_MSG_ACT_BUS_A | UNMMKO1_MSG_ACT_CWD_1 | UNMMKO1_MSG_ACT_SWD_1, UNMMKO1_MSG_ERR_OK, command_f6,
                                  unmmko1_pack_sw(RT_1, 0), 0, zero_data_words, 0, 0, zero_data_words))
                fail_test(0x000d, "Ошибка оконечного устройства (магистраль A): формат сообщения 6");

            // Магистраль B
            unerror(unmmko1_rt_configure(session, 1 << RT_1, UNMMKO1_RT_DIRECT | UNMMKO1_RT_BUS_B | UNMMKO1_RT_DEFAULT_RESPONSES));
            unerror(unmmko1_rt_start(session));
            unerror(unmmko1_mon_start(session));
            command_f6.activity = UNMMKO1_MSG_ACT_BUS_A | UNMMKO1_MSG_ACT_CWD_1;
            unerror(unmmko1_bc_transmit_command(session, command_f6));
            message_received = wait_for_monitoring_one_message(session, &m);
            unerror(unmmko1_mon_stop(session));
            unerror(unmmko1_rt_stop(session));
            if (!message_received || !compare_messages(&m, UNMMKO1_MSG_ACT_BUS_B | UNMMKO1_MSG_ACT_CWD_1 | UNMMKO1_MSG_ACT_SWD_1, UNMMKO1_MSG_ERR_OK, command_f6,
                                  unmmko1_pack_sw(RT_1, 0), 0, zero_data_words, 0, 0, zero_data_words))
                fail_test(0x000e, "Ошибка оконечного устройства (магистраль B): формат сообщения 6");
        }
    }

    *result = 0;
    strcpy(message, "Тест обмена пройден без ошибок");

Fail:
    unmmko1_reset(session);
    return status;

Error:
    *result = (ViInt16)status;
    unmmko1_error_message(session, status, message);
    unmmko1_reset(session);
    return status;
}

//! \brief Функция unmmko1_test_memory производит тестирование памяти мезонина.
//! Тестирование памяти - длительная операция.
//! \param session Номер сеанса связи с мезонином.
//! \param result Код результата тестирования.
//! \param message Сообщение о результате тестирования.
//! \return Код ошибки или код успешного выполнения функции.
ViStatus _VI_FUNC unmmko1_test_memory(ViSession session, ViInt16* result, ViChar message[]) {
    ViStatus status = VI_SUCCESS;
    unmmko1_device_data* device_data = get_device_data_or_error(session);

    if (is_not_valid_pointer(result))
        return VI_ERROR_PARAMETER2;
    if (is_not_valid_pointer(message))
        return VI_ERROR_PARAMETER3;

    // Останавливаем мезонин и сбрасываем все настройки
    unerror(unmmko1_reset(session));

    // Конфигурируем все оконечные устройства, записываем и читаем основные настройки
    {
        ViUInt16 address = 0;
        unerror(unmmko1_rt_configure(session, 0xffffffff, UNMMKO1_RT_DEFAULT));
        for (address = 0; address < 31; ++address)
            unerror(set_rt_configuration(session, address, VI_TRUE, address, address + 1, address + 2));
        for (address = 0; address < 31; ++address) {
            ViBoolean on = VI_FALSE;
            ViUInt16 status_word = 0, vector_word = 0, selftest_word = 0;
            unerror(get_rt_configuration(session, address, &on, &status_word, &vector_word, &selftest_word));
            if (!on || status_word != address || vector_word != address + 1 || selftest_word != address + 2)
                fail_test(0x0001, "Ошибка чтения конфигурации оконечного устройства");
        }
    }

    // Записываем данные в режиме UNMMKO1_RT_SUBADDRESS_DEFAULT и читаем их
    {
#define DATA_WORDS_COUNT 32
        ViUInt16 data_words[DATA_WORDS_COUNT];
        ViUInt16 address = 0, subaddress = 0, data_index = 0;
        for (address = 0; address < 31; ++address) {
            for (subaddress = 1; subaddress < 31; ++subaddress) {
                for (data_index = 0; data_index < DATA_WORDS_COUNT; ++data_index)
                    data_words[data_index] = (address * 32 + subaddress) * 32 + data_index;
                unerror(unmmko1_rt_set_subaddress_data(session, address, subaddress, DATA_WORDS_COUNT, data_words));
            }
        }

        for (address = 0; address < 31; ++address) {
            for (subaddress = 1; subaddress < 31; ++subaddress) {
                unmmko1_rt_subaddress_options options;
                ViUInt16 data_words_count;
                ViUInt32 packed_data_word[DATA_WORDS_COUNT / 2];
                for (data_index = 0; data_index < DATA_WORDS_COUNT; ++data_index)
                    data_words[data_index] = (address * 32 + subaddress) * 32 + data_index;
                unerror(get_rt_data(session, address, subaddress, &options, &data_words_count, packed_data_word));
                if (options != UNMMKO1_RT_SUBADDRESS_DEFAULT || DATA_WORDS_COUNT != data_words_count || memcmp(data_words, packed_data_word, sizeof(packed_data_word)))
                    fail_test(0x0002, "Ошибка чтения данных оконечного устройства");
            }
        }
    }

    // Записываем данные в режиме UNMMKO1_RT_SUBADDRESS_QUEUE и читаем их
    {
#undef DATA_WORDS_COUNT
#define DATA_WORDS_COUNT 256
        ViUInt16 data_words[DATA_WORDS_COUNT];
        ViUInt16 address = 0, subaddress = 0, data_index = 0;
        for (address = 0; address < 31; ++address) {
            for (subaddress = 1; subaddress < 31; ++subaddress) {
                for (data_index = 0; data_index < DATA_WORDS_COUNT; ++data_index)
                    data_words[data_index] = (address * 32 + subaddress) * 32 + data_index;
                unerror(unmmko1_rt_set_subaddress_options(session, address, subaddress, UNMMKO1_RT_SUBADDRESS_QUEUE));
                unerror(unmmko1_rt_set_subaddress_data(session, address, subaddress, DATA_WORDS_COUNT, data_words));
            }
        }

        for (address = 0; address < 31; ++address) {
            for (subaddress = 1; subaddress < 31; ++subaddress) {
                unmmko1_rt_subaddress_options options;
                ViUInt16 data_words_count;
                ViUInt32 packed_data_word[DATA_WORDS_COUNT / 2];
                for (data_index = 0; data_index < DATA_WORDS_COUNT; ++data_index)
                    data_words[data_index] = (address * 32 + subaddress) * 32 + data_index;
                unerror(get_rt_data(session, address, subaddress, &options, &data_words_count, packed_data_word));
                if (options != UNMMKO1_RT_SUBADDRESS_QUEUE || DATA_WORDS_COUNT != data_words_count || memcmp(data_words, packed_data_word, sizeof(packed_data_word)))
                    fail_test(0x0003, "Ошибка чтения расширенных данных оконечного устройства");
            }
        }
#undef DATA_WORDS_COUNT
    }

    *result = 0;
    strcpy(message, "Тест памяти пройден без ошибок");

Fail:
    unmmko1_reset(session);
    return status;

Error:
    *result = (ViInt16)status;
    unmmko1_error_message(session, status, message);
    unmmko1_reset(session);
    return status;
}

//! \brief Функция unmmko1_reset функция производит сброс мезонина в состояние по умолчанию.
//! Если мезонин был запущен в каком-либо режиме работы, то также будет произведена остановка мезонина.
//! \param session Номер сеанса связи с мезонином.
//! \return Код ошибки или код успешного выполнения функции.
ViStatus _VI_FUNC unmmko1_reset(ViSession session) {
    ViStatus status = VI_SUCCESS;
    unmmko1_device_data* device_data = get_device_data_or_error(session);

    // Останавливаем мезонин, если он запущен
    if (UNMMKO1_MODE_BUS_CONTROLLER == device_data->current_mode && device_data->bus_controller.is_started)
        unerror(unmmko1_bc_stop(session));
    else if (UNMMKO1_MODE_REMOTE_TERMINAL == device_data->current_mode && device_data->remote_terminal.is_started)
        unerror(unmmko1_rt_stop(session));
    else if (UNMMKO1_MODE_BUS_MONITOR == device_data->current_mode && device_data->bus_monitor.is_started)
        unerror(unmmko1_mon_stop(session));

    // Запрещаем прерывания
    unerror(unmbase_m_config_event(session, VI_OFF));

    // Останавливаем и сбрасываем мезонин
    unmbase_m_stop(session,  UNMBASE_IOMODE_BOTH);
    unmbase_m_reset(session, UNMBASE_IOMODE_BOTH);

    // Сбрасываем данные мезонина
    unerror(reset_device_data(device_data));

    // Настраиваем задержку первых данных
    unerror(unmbase_m_first_delay(session, UNMBASE_IOMODE_IN,  M_FIRST_DELAY));
    unerror(unmbase_m_first_delay(session, UNMBASE_IOMODE_OUT, M_FIRST_DELAY));
    // Настраиваем частоту временных отсчётов
    unerror(unmbase_m_clock(session, UNMBASE_IOMODE_IN,  M_CLOCK));
    unerror(unmbase_m_clock(session, UNMBASE_IOMODE_OUT, M_CLOCK));
    // Настраиваем ширину кадра
    unerror(unmbase_m_sample_width(session, UNMBASE_IOMODE_IN,  M_SAMPLE_WORDS));
    unerror(unmbase_m_sample_width(session, UNMBASE_IOMODE_OUT, M_SAMPLE_WORDS));
    // Настраиваем длину блока
    unerror(unmbase_m_block_size(session, UNMBASE_IOMODE_IN,  512 / M_SAMPLE_BYTES));
    unerror(unmbase_m_block_size(session, UNMBASE_IOMODE_OUT, 512 / M_SAMPLE_BYTES));

    // Триггер - уровень
    unerror(unmbase_m_trig_length(session, 1));

    // Настраиваем блочный обмен на ввод и вывод
    unerror(unmbase_m_mode(session, UNMBASE_IOMODE_IN,  UNMBASE_MODE_BLOCK));
    unerror(unmbase_m_mode(session, UNMBASE_IOMODE_OUT, UNMBASE_MODE_BLOCK));

    // Размер пакета
    unerror(unmbase_m_packet_size(session, UNMBASE_IOMODE_IN, 0));

    // Разрешаем прерывания
    unerror(unmbase_m_config_event(session, VI_ON));

Error:
    return status;
}

//! \brief Функция unmmko1_install_interrupt_handler устанавливаем пользовательскую функцию для приёма прерываний от мезонина.
//! \param session Номер сеанса связи с мезонином.
//! \param handler Пользовательский обработчик прерываний - указатель на функцию с семантикой, заданной в UNMMKO1_EVENT_HANDLER.
//! \param data Указатель на данные, передаваемые в пользовательский обработчик прерываний.
//! \return Код ошибки или код успешного выполнения функции.
ViStatus _VI_FUNC unmmko1_install_interrupt_handler(ViSession session, UNMMKO1_EVENT_HANDLER handler, ViAddr data) {
    unmmko1_device_data* device_data = get_device_data_or_error(session);

    device_data->interrupt_request_handler = handler;
    device_data->interrupt_request_data = data;

    return VI_SUCCESS;
}

//! \brief Функция unmmko1_error_query возвращает текущие код и сообщение об ошибке при работе с мезонином.
//! Для данного мезонина функция не поддерживается и возвращает статус VI_WARN_NSUP_ERROR_QUERY.
//! \param session Номер сеанса связи с мезонином.
//! \param error Код ошибки.
//! \param message Сообщение об ошибке.
//! \return Код ошибки или код успешного выполнения функции.
ViStatus _VI_FUNC unmmko1_error_query(ViSession session, ViPInt32 error, ViChar message[]) {
    (void)session;
    (void)error;
    (void)message;
    return VI_WARN_NSUP_ERROR_QUERY;
}

//! \brief Функция unmmko1_revision_query возвращает версию драйвера инструмента.
//! Для данного мезонина функция не поддерживает возврат версии аппаратного обеспечения и возвращает статус VI_WARN_NSUP_REV_QUERY.
//! \param session Номер сеанса связи с мезонином.
//! \param software_version Версия программного обеспечения мезонина.
//! \param hardware_version Версия аппаратного обеспечения мезонина (не поддерживается).
//! \return Код ошибки или код успешного выполнения функции.
ViStatus _VI_FUNC unmmko1_revision_query(ViSession session, ViChar software_version[], ViChar hardware_version[]) {
    (void)session;
    strcpy(software_version, UNMMKO1_APP_VERSION);
    strcpy(hardware_version, "<not available>");
    return VI_WARN_NSUP_REV_QUERY;
}

//! \brief Функция unmmko1_error_message получает и интерпретирует код состояния, возвращенный какой-либо функцией драйвера и возвращает строку сообщения об ошибке.
//! Поддерживается возврат сообщений на английском и русском языках, язык зависит от текущих региональных параметров (локали LC_CTYPE).
//! \param session Номер сеанса связи с мезонином.
//! \param status Код ошибки.
//! \param error_message Сообщение об ошибке.
//! \return Код ошибки или код успешного выполнения функции.
ViStatus _VI_FUNC unmmko1_error_message(ViSession session, ViStatus status, ViChar error_message[]) {
    (void)session;

    if ((status >= UNMMKO1_WARNING_FIRST_CODE && status <= UNMMKO1_WARNING_LAST_CODE) ||
        (status >= UNMMKO1_ERROR_FIRST_CODE && status <= UNMMKO1_ERROR_LAST_CODE)) {
        get_localized_error_message(status, error_message);
    }
    else if (unmbase_error_message(VI_NULL, status, error_message) < 0) {
        strcpy(error_message, "Unknown status");
        return VI_WARN_UNKNOWN_STATUS;
    }

    return VI_SUCCESS;
}

//! \brief Функция unmmko1_close закрывает сеанс связи с мезонином.
//! \param session Номер сеанса связи с мезонином.
//! \return Код ошибки или код успешного выполнения функции.
ViStatus _VI_FUNC unmmko1_close(ViSession session) {
    ViStatus status = VI_SUCCESS;
    ViSession init_session = 0;
    unmmko1_device_data* device_data = get_device_data_or_error(session);

    unerror(unmmko1_reset(session));

    init_session = device_data->init_session;
    destroy_device_data(device_data);

    // Закрываем сессию мезонина
    if (is_valid_session(session)) {
        unerror(unmbase_m_set_attribute(session, UNMBASE_MATTR_USER_DATA, VI_NULL));
        unerror(unmbase_m_close(session));
    }

    // Закрываем сессию инициализации мезонина
    if (is_valid_session(init_session))
        unerror(viClose(session));

Error:
    return status;
}

static unmmko1_command empty_command() {
    unmmko1_command command;
    command.activity = 0;
    command.command_word_1 = 0;
    command.command_word_2 = 0;
    command.data_words_count = 0;
    memset(command.data_words, 0, sizeof(command.data_words));
    return command;
}

message_format_enum detect_bc_rt_format(ViUInt16 command_word) {
    ViUInt16 address, rx_tx, subaddress, word_count;
    unmmko1_unpack_cw(command_word, &address, &rx_tx, &subaddress, &word_count);

    // Если адрес ОУ групповой, то это возможно форматы 7-10
    if (31 == address) {
        // Если подадрес 0b00000 или 0b11111, то это возможно форматы 9-10
        if (0 == subaddress || 31 == subaddress) {
            // Если команда приёма, то это возможно формат 10
            if (0 == rx_tx) {
                // Если код команды управления совпадает с разрешёнными к использованию, то точно формат 10
                if (17 == word_count || 20 == word_count || 21 == word_count)
                    return f10;
            }
            // Если команда передачи, то это возможно формат 9
            else if (1 == rx_tx) {
                // Если код команды управления совпадает с разрешёнными к использованию, то точно формат 9
                if (1 == word_count || (3 <= word_count && 8 >= word_count))
                    return f9;
            }
        }
        // Иначе, если это не команда управления, то возможно форматы 7-8
        else {
            // Если команда приёма и второго командного слова нет, то это формат 7
            if (0 == rx_tx)
                return f7;
        }
    }
    // Иначе - адрес негрупповой команды, то есть возможно форматы 1-6
    else {
        // Если подадрес 0b00000 или 0b11111, то это возможно форматы 4-6
        if (0 == subaddress || 31 == subaddress) {
            // Если команда приёма, то это возможно формат 6
            if (0 == rx_tx) {
                // Если код команды управления совпадает с разрешёнными к использованию, то точно формат 6
                if (17 == word_count || 20 == word_count || 21 == word_count)
                    return f6;
            }
            // Если команда передачи, то это возможно форматы 4-5
            else if (1 == rx_tx) {
                // Если код команды управления от 0 до 8, то точно формат 4
                if (word_count <= 8)
                    return f4;
                // Если код команды управления 16, 18 или 19, то точно формат 5
                else if (16 == word_count || 18 == word_count || 19 == word_count)
                    return f5;
            }
        }
        // Иначе, если это не команда управления, то возможно форматы 1-3
        else {
            // Если команда передачи, то это формат 2
            if (1 == rx_tx)
                return f2;
            // Если команда приёма и второго командного слова нет, то это формат 1
            else
                return f1;
        }
    }

    return f_unknown;
}

//! \brief Функция unmmko1_bc_rt создаёт командный сегмент для сообщений обмена данными между контроллером шины и оконечным устройством.
//! Функция предназначена для формирования сообщений с одним командным словом - форматы 1, 2, 4, 5, 6, 7, 9, 10.
//! Требуемое количество слов данных определяется командным словом.
//! \param bus Выбранная магистраль для передачи командного сегмента.
//! \param command_word Командное слово (можно создать с помощью вызова функции unmmko1_pack_cw).
//! \param data_words Указатель на массив слов данных (может быть NULL для соответствующих форматов).
//! \return Командный сегмент.
unmmko1_command _VI_FUNC unmmko1_bc_rt(unmmko1_bus bus, ViUInt16 command_word, ViUInt16* data_words) {
    unmmko1_command command = empty_command();
    message_format_enum format = detect_bc_rt_format(command_word);

    // Недостоверный командный сегмент
    if (f_rubbish == format || f_unknown == format || f3 == format || f8 == format)
        return command;

    // Форматы (1 и 7) с количеством данных, указанным в командном слове
    else if (f1 == format || f7 == format) {
        ViUInt16 word_count;
        unmmko1_unpack_cw(command_word, NULL, NULL, NULL, &word_count);

        command.activity = (ViUInt16)(bus | UNMMKO1_MSG_ACT_CWD_1);
        command.command_word_1 = command_word;
        memcpy(command.data_words, data_words, (0 != word_count ? word_count : 32) * sizeof(ViUInt16));
        command.data_words_count = (0 != word_count ? word_count : 32);
        return command;
    }

    // Форматы (6 и 10) с одним словом данных
    else if (f6 == format || f10 == format) {
        command.activity = (ViUInt16)(bus | UNMMKO1_MSG_ACT_CWD_1);
        command.command_word_1 = command_word;
        memcpy(command.data_words, data_words, sizeof(ViUInt16));
        command.data_words_count = 1;
        return command;
    }

    // Форматы без слов данных
    else {
        command.activity = (ViUInt16)(bus | UNMMKO1_MSG_ACT_CWD_1);
        command.command_word_1 = command_word;
        return command;
    }
}

//! \brief Функция unmmko1_rt_rt создаёт командный сегмент для сообщений обмена данными между оконечными устройствами.
//! Функция предназначена для формирования сообщений с двумя командными словами - форматы 3 и 8.
//! \param bus Выбранная магистраль для передачи командного сегмента.
//! \param command_word_1 Первое командное слово (можно создать с помощью вызова функции unmmko1_pack_cw).
//! \param command_word_2 Первое командное слово (можно создать с помощью вызова функции unmmko1_pack_cw).
//! \return Командный сегмент.
unmmko1_command _VI_FUNC unmmko1_rt_rt(unmmko1_bus bus, ViUInt16 command_word_1, ViUInt16 command_word_2) {
    // Разбираем командные слова, чтобы потом выбрать между 3 и 8 форматами
    ViUInt16 address_1, rx_tx_1, subaddress_1, word_count_1;
    ViUInt16 address_2, rx_tx_2, subaddress_2, word_count_2;
    unmmko1_unpack_cw(command_word_1, &address_1, &rx_tx_1, &subaddress_1, &word_count_1);
    unmmko1_unpack_cw(command_word_2, &address_2, &rx_tx_2, &subaddress_2, &word_count_2);

    // Формат 8 - без слов данных
    if (31 == address_1 && 0 == rx_tx_1 && 0 != subaddress_1 && 31 != subaddress_1 &&
        31 != address_2 && 1 == rx_tx_2 && 0 != subaddress_2 && 31 != subaddress_2 && word_count_1 == word_count_2) {
        unmmko1_command command = empty_command();
        command.activity = (ViUInt16)(bus | UNMMKO1_MSG_ACT_CWD_1 | UNMMKO1_MSG_ACT_CWD_2);
        command.command_word_1 = command_word_1;
        command.command_word_2 = command_word_2;
        return command;
    }

    // Формат 3 - с количеством данных, указанным в командном слове
    else if (31 != address_1 && 0 == rx_tx_1 && 0 != subaddress_1 && 31 != subaddress_1 &&
             31 != address_2 && 1 == rx_tx_2 && 0 != subaddress_2 && 31 != subaddress_2 && word_count_1 == word_count_2) {
        unmmko1_command command = empty_command();
        command.activity = (ViUInt16)(bus | UNMMKO1_MSG_ACT_CWD_1 | UNMMKO1_MSG_ACT_CWD_2);
        command.command_word_1 = command_word_1;
        command.command_word_2 = command_word_2;
        return command;
    }

    // Недостоверный командный сегмент
    else
        return empty_command();
}

//! \brief Функция unmmko1_f1 создаёт командный сегмент сообщения в формате 1.
//! Формат 1 - передача слов данных от контроллера к оконечному устройству.
//! \param bus Выбранная магистраль для передачи командного сегмента.
//! \param address Адрес оконечного устройства.
//! \param subaddress Подадрес (1 .. 30).
//! \param word_count Количество слов данных.
//! \param data_words Указатель на массив слов данных (массив должен содержать как минимум word_count слов данных).
//! \return Командный сегмент.
unmmko1_command _VI_FUNC unmmko1_f1(unmmko1_bus bus, ViUInt16 address, ViUInt16 subaddress, ViUInt16 word_count, ViUInt16* data_words) {
    return unmmko1_bc_rt(bus, unmmko1_pack_cw(address, 0, subaddress, word_count), data_words);
}

//! \brief Функция unmmko1_f2 создаёт командный сегмент сообщения в формате 2.
//! Формат 2 - передача слов данных от оконечного устройства к контроллеру.
//! \param bus Выбранная магистраль для передачи командного сегмента.
//! \param address Адрес оконечного устройства.
//! \param subaddress Подадрес (1 .. 30).
//! \param word_count Количество слов данных.
//! \return Командный сегмент.
unmmko1_command _VI_FUNC unmmko1_f2(unmmko1_bus bus, ViUInt16 address, ViUInt16 subaddress, ViUInt16 word_count) {
    return unmmko1_bc_rt(bus, unmmko1_pack_cw(address, 1, subaddress, word_count), NULL);
}

//! \brief Функция unmmko1_f3 создаёт командный сегмент сообщения в формате 3.
//! Формат 3 - передача слов данных от оконечного устройства к оконечному устройству.
//! \param bus Выбранная магистраль для передачи командного сегмента.
//! \param receive_address Адрес оконечного устройства, которое принимает слова данных.
//! \param receive_subaddress Подадрес приёма слов данных (1 .. 30).
//! \param transmit_address Адрес оконечного устройства, которое передаёт слова данных.
//! \param transmit_subaddress Подадрес передачи слов данных (1 .. 30).
//! \param word_count Количество слов данных.
//! \return Командный сегмент.
unmmko1_command _VI_FUNC unmmko1_f3(unmmko1_bus bus, ViUInt16 receive_address, ViUInt16 receive_subaddress, ViUInt16 transmit_address, ViUInt16 transmit_subaddress, ViUInt16 word_count) {
    return unmmko1_rt_rt(bus, unmmko1_pack_cw(receive_address, 0, receive_subaddress, word_count), unmmko1_pack_cw(transmit_address, 1, transmit_subaddress, word_count));
}

//! \brief Функция unmmko1_f4 создаёт командный сегмент сообщения в формате 4.
//! Формат 4 - передача команды управления без слов данных.
//! \param bus Выбранная магистраль для передачи командного сегмента.
//! \param address Адрес оконечного устройства.
//! \param subaddress Подадрес/режим управления (SA_MC0 (0) или SA_MC31 (31)).
//! \param mode_code Код команды управления (0 .. 8).
//! \return Командный сегмент.
unmmko1_command _VI_FUNC unmmko1_f4(unmmko1_bus bus, ViUInt16 address, ViUInt16 subaddress, ViUInt16 mode_code) {
    return unmmko1_bc_rt(bus, unmmko1_pack_cw(address, 1, subaddress, mode_code), NULL);
}

//! \brief Функция unmmko1_f5 создаёт командный сегмент сообщения в формате 5.
//! Формат 5 - передача команды управления и приём слова данных от оконечного устройства.
//! \param bus Выбранная магистраль для передачи командного сегмента.
//! \param address Адрес оконечного устройства.
//! \param subaddress Подадрес/режим управления (SA_MC0 (0) или SA_MC31 (31)).
//! \param mode_code Код команды управления (16, 18, 19).
//! \return Командный сегмент.
unmmko1_command _VI_FUNC unmmko1_f5(unmmko1_bus bus, ViUInt16 address, ViUInt16 subaddress, ViUInt16 mode_code) {
    return unmmko1_bc_rt(bus, unmmko1_pack_cw(address, 1, subaddress, mode_code), NULL);
}

//! \brief Функция unmmko1_f6 создаёт командный сегмент сообщения в формате 6.
//! Формат 6 - передача команды управления со словом данных.
//! \param bus Выбранная магистраль для передачи командного сегмента.
//! \param address Адрес оконечного устройства.
//! \param subaddress Подадрес/режим управления (SA_MC0 (0) или SA_MC31 (31)).
//! \param mode_code Код команды управления (17, 20, 21).
//! \param data_word Слово данных.
//! \return Командный сегмент.
unmmko1_command _VI_FUNC unmmko1_f6(unmmko1_bus bus, ViUInt16 address, ViUInt16 subaddress, ViUInt16 mode_code, ViUInt16 data_word) {
    return unmmko1_bc_rt(bus, unmmko1_pack_cw(address, 0, subaddress, mode_code), &data_word);
}

//! \brief Функция unmmko1_f7 создаёт командный сегмент сообщения в формате 7.
//! Формат 7 - передача слов данных (в групповом сообщении) от контроллера шины к оконечным устройствам.
//! \param bus Выбранная магистраль для передачи командного сегмента.
//! \param subaddress Подадрес (1 .. 30).
//! \param word_count Количество слов данных.
//! \param data_words Указатель на массив слов данных (массив должен содержать как минимум word_count слов данных).
//! \return Командный сегмент.
unmmko1_command _VI_FUNC unmmko1_f7(unmmko1_bus bus, ViUInt16 subaddress, ViUInt16 word_count, ViUInt16* data_words) {
    return unmmko1_bc_rt(bus, unmmko1_pack_cw(31, 0, subaddress, word_count), data_words);
}

//! \brief Функция unmmko1_f8 создаёт командный сегмент сообщения в формате 8.
//! Формат 8 - передача слов данных (в групповом сообщении) от оконечного устройства к оконечным устройствам.
//! \param bus Выбранная магистраль для передачи командного сегмента.
//! \param receive_subaddress Подадрес приёма слов данных.
//! \param transmit_address Адрес оконечного устройства, которое передаёт слова данных.
//! \param transmit_subaddress Подадрес передачи слов данных.
//! \param word_count Количество слов данных.
//! \return Командный сегмент.
unmmko1_command _VI_FUNC unmmko1_f8(unmmko1_bus bus, ViUInt16 receive_subaddress, ViUInt16 transmit_address, ViUInt16 transmit_subaddress, ViUInt16 word_count) {
    return unmmko1_rt_rt(bus, unmmko1_pack_cw(31, 0, receive_subaddress, word_count), unmmko1_pack_cw(transmit_address, 1, transmit_subaddress, word_count));
}

//! \brief Функция unmmko1_f9 создаёт командный сегмент сообщения в формате 9.
//! Формат 9 - передача групповой команды управления без слов данных.
//! \param bus Выбранная магистраль для передачи командного сегмента.
//! \param subaddress Подадрес/режим управления (SA_MC0 (0) или SA_MC31 (31)).
//! \param mode_code Код команды управления (1, 3, 4, 5, 6, 7, 8).
//! \return Командный сегмент.
unmmko1_command _VI_FUNC unmmko1_f9(unmmko1_bus bus, ViUInt16 subaddress, ViUInt16 mode_code) {
    return unmmko1_bc_rt(bus, unmmko1_pack_cw(31, 1, subaddress, mode_code), NULL);
}

//! \brief Функция unmmko1_f10 создаёт командный сегмент сообщения в формате 10.
//! Формат 10 - передача групповой команды управления со словом данных.
//! \param bus Выбранная магистраль для передачи командного сегмента.
//! \param subaddress Подадрес/режим управления (SA_MC0 (0) или SA_MC31 (31)).
//! \param mode_code Код команды управления (17, 20, 21).
//! \param data_word Слово данных.
//! \return Командный сегмент.
unmmko1_command _VI_FUNC unmmko1_f10(unmmko1_bus bus, ViUInt16 subaddress, ViUInt16 mode_code, ViUInt16 data_word) {
    return unmmko1_bc_rt(bus, unmmko1_pack_cw(31, 0, subaddress, mode_code), &data_word);
}

static const ViUInt16 terminal_address_mask         = 0xf800;
static const ViUInt16 transmit_receive_field_mask   = 0x0400;
static const ViUInt16 terminal_subaddress_mask      = 0x03e0;
static const ViUInt16 data_count_mask               = 0x001f;
static const ViUInt16 terminal_address_position     = 11;
static const ViUInt16 transmit_receive_position     = 10;
static const ViUInt16 terminal_subaddress_position  = 5;
static const ViUInt16 five_bits_mask                = 0x001f;
static const ViUInt16 error_bits_mask               = 0x07ff;

//! \brief Функция unmmko1_pack_cw создаёт 16-битное командное слово из составляющих его полей.
//! \param address Адрес оконечного устройства.
//! \param rx_tx Разряд приёма/передачи (приём - 0, передача - 1).
//! \param subaddress Подадрес/режим управления.
//! \param word_count Количество слов данных/код команды управления.
//! \return Командное слово.
ViUInt16 _VI_FUNC unmmko1_pack_cw(ViUInt16 address, ViUInt16 rx_tx, ViUInt16 subaddress, ViUInt16 word_count) {
    ViUInt16 command_word = (word_count & five_bits_mask);
    command_word |= ((subaddress & five_bits_mask) << terminal_subaddress_position);
    command_word |= ((rx_tx ? 1 : 0) << transmit_receive_position);
    command_word |= ((address & five_bits_mask) << terminal_address_position);
    return command_word;
}

//! \brief Функция unmmko1_unpack_cw извлекает поля из 16-битного командного слова.
//! Для игнорирования любого из возвращаемых аргументов передайте значение NULL вместо указателя на аргумент.
//! \param[in] command_word Командное слово.
//! \param[out] address Адрес оконечного устройства.
//! \param[out] rx_tx Разряд приёма/передачи (приём - 0, передача - 1).
//! \param[out] subaddress Подадрес/режим управления.
//! \param[out] word_count Количество слов данных/код команды управления.
void _VI_FUNC unmmko1_unpack_cw(ViUInt16 command_word, ViUInt16* address, ViUInt16* rx_tx, ViUInt16* subaddress, ViUInt16* word_count) {
    if (NULL != address)
        *address = ((command_word & terminal_address_mask) >> terminal_address_position);
    if (NULL != rx_tx)
        *rx_tx = (0 != (command_word & transmit_receive_field_mask));
    if (NULL != subaddress)
        *subaddress = ((command_word & terminal_subaddress_mask) >> terminal_subaddress_position);
    if (NULL != word_count)
        *word_count = (command_word & data_count_mask);
}

//! \brief Функция unmmko1_pack_sw создаёт 16-битное ответное слово из составляющих его полей.
//! \param address Адрес оконечного устройства.
//! \param error_bits Признаки ответного слова (объединение констант из перечисления unmmko1_error_bits).
//! \return Ответное слово.
ViUInt16 _VI_FUNC unmmko1_pack_sw(ViUInt16 address, ViUInt16 error_bits) {
    return (ViUInt16)(((address & five_bits_mask) << 11) | (error_bits & error_bits_mask));
}

//! \brief Функция unmmko1_pack_sw извлекает поля из ответного слова.
//! Для игнорирования любого из возвращаемых аргументов передайте значение NULL вместо указателя на аргумент.
//! \param[in] status_word Ответное слово.
//! \param[out] address Адрес оконечного устройства.
//! \param[out] error_bits Признаки ответного слова (объединение констант из перечисления unmmko1_error_bits).
void _VI_FUNC unmmko1_unpack_sw(ViUInt16 status_word, ViUInt16* address, ViUInt16* error_bits) {
    if (NULL != address)
        *address = ((status_word & terminal_address_mask) >> terminal_address_position);
    if (NULL != error_bits)
        *error_bits = (status_word & error_bits_mask);
}
