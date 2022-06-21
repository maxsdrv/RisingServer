#include "unmmko1.h"
#include "internal/unmmko1_internal.h"
#include <stdlib.h>
#include <string.h>

//! \brief Функция unmmko1_rt_configure осуществляет настройку мезонина в режиме оконечного устройства, определяет адреса имитируемых оконечных устройств.
//! Вызов функции также осуществляет сброс настроек контроллера.
//! Если мезонин был запущен в каком-либо режиме работы, то также будет произведена остановка мезонина.
//!
//! Флаги UNMMKO1_RT_BUS_A, UNMMKO1_RT_BUS_B и UNMMKO1_RT_BUS_A_AND_B (по умолчанию) определяют магистрали, по которым возможен обмен данными с оконечными устройствами.
//! Установка флага UNMMKO1_RT_CUSTOM_RESPONSES означает, что все команды приёма и передачи данных для всех подадресов оконечных устройств отмечаются как недопустимые.
//! На недопустимые команды приёма/передачи оконечное устройство не отвечает.
//! Для того, чтобы сделать команду допустимой (для определённых адреса и подадреса) нужно установить данные вызовом функции unmmko1_rt_set_subaddress_data.
//! Использовать флаг UNMMKO1_RT_CUSTOM_RESPONSES нужно в тех случаях, когда требуется часть команд приёма/передачи сделать недопустимыми.
//! Установка же флага UNMMKO1_RT_DEFAULT_RESPONSES (по умолчанию) означает, что все команды приёма и передачи данных для всех подадресов будут допустимыми.
//! Также по умолчанию все слова данных будут установлены в значение 0, вызовом функции unmmko1_rt_set_subaddress_data значения слов данных можно переписать.
//! Независимо от того, какой флаг (UNMMKO1_RT_CUSTOM_RESPONSES или UNMMKO1_RT_DEFAULT_RESPONSES) будет установлен, оконечное устройство будет отвечать на команды управления.
//!
//! В оконечных устройствах реализовано выполнение следующих команд управления: "Передать ОС" (КУ 2), "Блокировать передатчик" (КУ 4), "Разблокировать передатчик" (КУ 5),
//! "Установить ОУ в исходное состояние" (КУ 8), "Передать последнюю команду" (КУ 18).
//! \param session Номер сеанса связи с мезонином.
//! \param addresses Маска адресов оконечных устройств (младший значащий бит отвечает за адрес оконечного устройства 0, второй бит - за 1 и так далее).
//! \param rt_options Настройки оконечного устройства - объединение флагов UNMMKO1_RT_* из перечисления unmmko1_rt_options.
//! \return Код ошибки или код успешного выполнения функции.
ViStatus _VI_FUNC unmmko1_rt_configure(ViSession session, ViUInt32 addresses, int rt_options) {
    ViStatus status = VI_SUCCESS;
    ViUInt16 address = 0;
    unmmko1_device_data* device_data = get_device_data_or_error(session);

    if (UNMMKO1_MODE_BUS_CONTROLLER == device_data->current_mode && device_data->bus_controller.is_started)
        unerror(unmmko1_bc_stop(session));
    else if (UNMMKO1_MODE_REMOTE_TERMINAL == device_data->current_mode && device_data->remote_terminal.is_started)
        unerror(unmmko1_rt_stop(session));
    else if (UNMMKO1_MODE_BUS_MONITOR == device_data->current_mode && device_data->bus_monitor.is_started)
        unerror(unmmko1_mon_stop(session));

    unerror(unmmko1_rt_reset(session));
    unerror(set_current_mode(session, UNMMKO1_MODE_REMOTE_TERMINAL));
    unerror(set_connection_type(session, (rt_options & UNMMKO1_RT_DIRECT) ? UNMMKO1_DIRECT : UNMMKO1_TRANSFORM));
    unerror(turn_rt(session, addresses));
    unerror(build_rt(session, addresses, (rt_options & UNMMKO1_RT_CUSTOM_RESPONSES) ? VI_FALSE : VI_TRUE));
    device_data->remote_terminal.options = rt_options;

    // Отмечаем активные адреса оконечных устройств и задаём ответные слова по умолчанию
    for (address = 0; address < 31; ++address) {
        device_data->remote_terminal.addresses[address].active = (addresses & (1 << address)) ? true : false;
        device_data->remote_terminal.addresses[address].status_word = unmmko1_pack_sw(address, 0);
    }

    // Если выбрана опция отсутствия разметки ответов по умолчанию, то включаем активные адреса
    if (rt_options & UNMMKO1_RT_CUSTOM_RESPONSES) {
        for (address = 0; address < 31; ++address) {
            if (device_data->remote_terminal.addresses[address].active) {
                unerror(set_rt_configuration(session, address, VI_TRUE,
                                             device_data->remote_terminal.addresses[address].status_word,
                                             device_data->remote_terminal.addresses[address].vector_word,
                                             device_data->remote_terminal.addresses[address].selftest_word));
            }
        }
    }
    // Если выбрана опция разметки ответов по умолчанию, то отключаем неактивные адреса
    else {
        for (address = 0; address < 31; ++address) {
            if (!device_data->remote_terminal.addresses[address].active) {
                unerror(set_rt_configuration(session, address, VI_FALSE,
                                             device_data->remote_terminal.addresses[address].status_word,
                                             device_data->remote_terminal.addresses[address].vector_word,
                                             device_data->remote_terminal.addresses[address].selftest_word));
            }
        }
    }

Error:
    return status;
}

//! \brief Функция unmmko1_rt_reset производит сброс значений и настроек ответных сегментов.
//! Настройка подадресов сбрасывается на значение по умолчанию - UNMMKO1_RT_SUBADDRESS_DEFAULT.
//! Значения слов данных, слова данных на команды управления обнуляются.
//! Настройка ответного сегмента по умолчанию - UNMMKO1_RT_RESPONSE_DEFAULT.
//! Если мезонин был запущен в каком-либо режиме работы, то также будет произведена остановка мезонина.
//! \param session Номер сеанса связи с мезонином.
//! \return Код ошибки или код успешного выполнения функции.
ViStatus _VI_FUNC unmmko1_rt_reset(ViSession session) {
    ViStatus status = VI_SUCCESS;
    unmmko1_device_data* device_data = get_device_data_or_error(session);

    if (UNMMKO1_MODE_BUS_CONTROLLER == device_data->current_mode && device_data->bus_controller.is_started)
        unerror(unmmko1_bc_stop(session));
    else if (UNMMKO1_MODE_REMOTE_TERMINAL == device_data->current_mode && device_data->remote_terminal.is_started)
        unerror(unmmko1_rt_stop(session));
    else if (UNMMKO1_MODE_BUS_MONITOR == device_data->current_mode && device_data->bus_monitor.is_started)
        unerror(unmmko1_mon_stop(session));

    reset_remote_terminal_settings(&device_data->remote_terminal);

Error:
    return status;
}

//! \brief Функция unmmko1_rt_set_status_word предназначена для установки значения ответного слова для конкретного адреса оконечного устройства.
//! Указываемый адрес оконечного устройства должен быть заранее настроен функцией unmmko1_rt_configure.
//! Вызов функции возможен также в процессе работы мезонина в режиме оконечного устройства (после unmmko1_rt_start).
//! \param session Номер сеанса связи с мезонином.
//! \param address Адрес оконечного устройства.
//! \param status_word Ответное слово (можно создать с помощью вызова функции unmmko1_pack_sw).
//! \return Код ошибки или код успешного выполнения функции.
ViStatus _VI_FUNC unmmko1_rt_set_status_word(ViSession session, ViUInt16 address, ViUInt16 status_word) {
    ViStatus status = VI_SUCCESS;
    unmmko1_device_data* device_data = get_device_data_or_error(session);

    if (UNMMKO1_MODE_REMOTE_TERMINAL != device_data->current_mode)
        return UNMMKO1_ERROR_WAS_CONFIGURED_IN_A_DIFFERENT_MODE;

    if (is_not_valid_uint16(address, 0, 30))
        return VI_ERROR_PARAMETER2;

    if (!device_data->remote_terminal.addresses[address].active)
        return UNMMKO1_ERROR_RT_ADDRESS_WAS_NOT_CONFIGURED;

    unerror(set_status_word(session, address, status_word));

Error:
    return status;
}

//! \brief Функция unmmko1_rt_set_subaddress_options предназначена для установки настроек подадреса оконечного устройства.
//! Указываемый адрес оконечного устройства должен быть заранее настроен функцией unmmko1_rt_configure.
//!
//! Флаг UNMMKO1_RT_SUBADDRESS_DEFAULT определяет поведение по умолчанию - оконечное устройство поддерживает хранение 32 слов данных для подадреса.
//! Установленные в этом режиме слова данных (функцией unmmko1_rt_set_subaddress_data) возвращаются контроллеру шины в ответ на команду передачи данных (формат 2).
//! Если в команде передачи запрашивается меньше, чем 32 слова данных, то оконечное устройство возвращает слова данных, начиная с самого первого.
//! Флаг UNMMKO1_RT_SUBADDRESS_WRAP определяет, что указанный подадрес оконечного устройства должен работать в режиме циклического возврата данных, то есть
//! слова, принятые оконечным устройством в этот подадрес, перезаписывают слова данных на передачу.
//! В этом режиме обеспечивается хранение 32 слов данных, устройство возвращает слова данных, начиная с самого первого.
//! Флаг UNMMKO1_RT_SUBADDRESS_QUEUE включает режим очереди данных для указанного подадреса.
//! В этом режиме обеспечивается хранение произвольного количества слов данных (слова данных и их количество устанавливаются функцией unmmko1_rt_set_subaddress_data до старта мезонина).
//! Особенность режима очереди данных в том, что оконечное устройство передаёт слова данных по очереди.
//! Первый запрос данных проводит к отправке слов, начиная с первого слова. Последующие запросы - начиная со следующего за последним переданным словом.
//!
//! Вызов функции недоступен в процессе работы мезонина в режиме оконечного устройства (после unmmko1_rt_start).
//! \param session Номер сеанса связи с мезонином.
//! \param address Адрес оконечного устройства.
//! \param subaddress Подадрес оконечного устройства.
//! \param subaddress_options Флаг настройки подадреса.
//! \return Код ошибки или код успешного выполнения функции.
ViStatus _VI_FUNC unmmko1_rt_set_subaddress_options(ViSession session, ViUInt16 address, ViUInt16 subaddress, unmmko1_rt_subaddress_options subaddress_options) {
    ViStatus status = VI_SUCCESS;
    unmmko1_device_data* device_data = get_device_data_or_error(session);

    if (UNMMKO1_MODE_REMOTE_TERMINAL != device_data->current_mode)
        return UNMMKO1_ERROR_WAS_CONFIGURED_IN_A_DIFFERENT_MODE;

    if (is_not_valid_uint16(address, 0, 30))
        return VI_ERROR_PARAMETER2;

    if (is_not_valid_uint16(subaddress, 1, 30))
        return VI_ERROR_PARAMETER3;

    if (subaddress_options != UNMMKO1_RT_SUBADDRESS_DEFAULT &&
        subaddress_options != UNMMKO1_RT_SUBADDRESS_WRAP &&
        subaddress_options != UNMMKO1_RT_SUBADDRESS_QUEUE)
        return VI_ERROR_PARAMETER4;

    if (!device_data->remote_terminal.addresses[address].active)
        return UNMMKO1_ERROR_RT_ADDRESS_WAS_NOT_CONFIGURED;

    if (device_data->remote_terminal.is_started)
        return UNMMKO1_ERROR_ILLEGAL_OPERATION_WHILE_RUNNING;

    if (device_data->remote_terminal.addresses[address].subaddresses[subaddress].options != subaddress_options) {
        unmmko1_rt_subaddress_options temp = device_data->remote_terminal.addresses[address].subaddresses[subaddress].options;
        device_data->remote_terminal.addresses[address].subaddresses[subaddress].options = subaddress_options;
        status = unmmko1_rt_set_subaddress_data(session, address, subaddress,
                                                device_data->remote_terminal.addresses[address].subaddresses[subaddress].data_words_count,
                                                device_data->remote_terminal.addresses[address].subaddresses[subaddress].data_words);
        if (0 != status)
            device_data->remote_terminal.addresses[address].subaddresses[subaddress].options = temp;
    }

    return status;
}

//! \brief Функция unmmko1_rt_set_subaddress_data предназначена для установки слов данных подадреса оконечного устройства.
//! Вызов функции для подадреса в режиме по умолчанию (UNMMKO1_RT_SUBADDRESS_DEFAULT) и в режиме циклического возврата данных (UNMMKO1_RT_SUBADDRESS_WRAP)
//! приводит к перезаписи указанного количества слов данных. В этих режимах вызов функции возможен также в процессе работы мезонина (после unmmko1_rt_start).
//! В режиме очереди данных (UNMMKO1_RT_SUBADDRESS_QUEUE) функция формирует очередь из data_words_count слов данных и записывает в неё слова.
//! Длина очереди слов данных ограничена размером расширенной области памяти, которая составляет UNMMKO1_RT_QUEUE_SIZE_LIMIT слов данных на все очереди оконечных устройств.
//! Вызов функции в режиме очереди данных недоступен в процессе работы мезонина (после unmmko1_rt_start).
//!
//! Если оконечное устройство было настроено с флагом UNMMKO1_RT_CUSTOM_RESPONSES, то unmmko1_rt_set_subaddress_data делает команды приёма/передачи к этому подадресу допустимыми.
//! \param session Номер сеанса связи с мезонином.
//! \param address Адрес оконечного устройства.
//! \param subaddress Подадрес оконечного устройства.
//! \param data_words_count Количество слов данных.
//! \param data_words Массив слов данных.
//! \return Код ошибки или код успешного выполнения функции.
ViStatus _VI_FUNC unmmko1_rt_set_subaddress_data(ViSession session, ViUInt16 address, ViUInt16 subaddress, int data_words_count, ViUInt16* data_words) {
    ViStatus status = VI_SUCCESS;
    unmmko1_device_data* device_data = get_device_data_or_error(session);

    if (UNMMKO1_MODE_REMOTE_TERMINAL != device_data->current_mode)
        return UNMMKO1_ERROR_WAS_CONFIGURED_IN_A_DIFFERENT_MODE;

    if (is_not_valid_uint16(address, 0, 30))
        return VI_ERROR_PARAMETER2;

    if (is_not_valid_uint16(subaddress, 1, 30))
        return VI_ERROR_PARAMETER3;

    if (0 == data_words_count)
        return VI_ERROR_PARAMETER4;

    if (NULL == data_words)
        return VI_ERROR_PARAMETER5;

    if (!device_data->remote_terminal.addresses[address].active)
        return UNMMKO1_ERROR_RT_ADDRESS_WAS_NOT_CONFIGURED;

    if (device_data->remote_terminal.is_started) {
        unmmko1_rt_subaddress_options subaddress_options = device_data->remote_terminal.addresses[address].subaddresses[subaddress].options;
        if (subaddress_options == UNMMKO1_RT_SUBADDRESS_QUEUE)
            return UNMMKO1_ERROR_CANNOT_UPDATE_DATA_WITH_QUEUE_MODE;

        // Обновляем значения в оконечном устройстве
        unerror(update_rt_data(session, address, subaddress, (ViUInt16)data_words_count, data_words));
        // Обновляем значения в структуре оконечного устройства
        memcpy(device_data->remote_terminal.addresses[address].subaddresses[subaddress].data_words, data_words, MIN((ViUInt16)data_words_count, 32) * sizeof(ViUInt16));
    }
    else {
        // Обновляем значения в оконечном устройстве
        unmmko1_rt_subaddress_options subaddress_options = device_data->remote_terminal.addresses[address].subaddresses[subaddress].options;
        size_t packed_data_words_size = (size_t)(data_words_count + 1) / 2;
        ViUInt32* packed_data_words = (ViUInt32*)calloc(packed_data_words_size, sizeof(ViUInt32));
        memcpy(packed_data_words, data_words, (size_t)data_words_count * sizeof(ViUInt16));
        // Нечётное количество слов данных требуется дополнить из словом из структуры оконечного устройства
        if (0 != data_words_count % 2 && data_words_count < device_data->remote_terminal.addresses[address].subaddresses[subaddress].data_words_count) {
            ViUInt32 align_word = (ViUInt32)device_data->remote_terminal.addresses[address].subaddresses[subaddress].data_words[data_words_count];
            packed_data_words[packed_data_words_size - 1] |= (align_word << 16);
        }

        // Для режимов кроме режима очереди можно установить только 32 слова данных
        if (subaddress_options != UNMMKO1_RT_SUBADDRESS_QUEUE)
            data_words_count = MIN(data_words_count, 32);

        unerror(set_rt_data(session, address, subaddress, subaddress_options, (ViUInt16)data_words_count, packed_data_words));

        // Обновляем значения в структуре оконечного устройства
        if (subaddress_options == UNMMKO1_RT_SUBADDRESS_QUEUE) {
            free(device_data->remote_terminal.addresses[address].subaddresses[subaddress].data_words);
            device_data->remote_terminal.addresses[address].subaddresses[subaddress].data_words_count = (ViUInt16)data_words_count;
            device_data->remote_terminal.addresses[address].subaddresses[subaddress].data_words = (ViUInt16*)calloc((size_t)data_words_count, sizeof(ViUInt16));
            memcpy(device_data->remote_terminal.addresses[address].subaddresses[subaddress].data_words, data_words, (size_t)data_words_count * sizeof(ViUInt16));
        }
        else {
            memcpy(device_data->remote_terminal.addresses[address].subaddresses[subaddress].data_words, data_words, MIN((ViUInt16)data_words_count, 32) * sizeof(ViUInt16));
        }
    }

Error:
    return status;
}

//! \brief Функция unmmko1_rt_set_command_data предназначена для установки слов данных в ответ на команду управления в формате сообщения 5.
//! Возвращаемые слова данных возможно установить в ответ на команды управления "Передать векторное слово" (КУ 16) и "Передать слово ВСК ОУ" (КУ 19).
//! Слово данных в ответе оконечного устройства на команду управления "Передать последнюю команду" (КУ 18) определяется только последней командой.
//! Допустимо использовать функцию в процессе работы мезонина в режиме оконечного устройства (после unmmko1_rt_start).
//! \param session Номер сеанса связи с мезонином.
//! \param address Адрес оконечного устройства.
//! \param command_code Код команды управления.
//! \param data_word Слово данных.
//! \return Код ошибки или код успешного выполнения функции.
ViStatus _VI_FUNC unmmko1_rt_set_command_data(ViSession session, ViUInt16 address, ViUInt16 command_code, ViUInt16 data_word) {
    ViStatus status = VI_SUCCESS;
    unmmko1_device_data* device_data = get_device_data_or_error(session);

    if (UNMMKO1_MODE_REMOTE_TERMINAL != device_data->current_mode)
        return UNMMKO1_ERROR_WAS_CONFIGURED_IN_A_DIFFERENT_MODE;

    if (is_not_valid_uint16(address, 0, 30))
        return VI_ERROR_PARAMETER2;

    if (command_code != 16 && command_code != 19)
        return VI_ERROR_PARAMETER3;

    if (!device_data->remote_terminal.addresses[address].active)
        return UNMMKO1_ERROR_RT_ADDRESS_WAS_NOT_CONFIGURED;

    if (16 == command_code)
        device_data->remote_terminal.addresses[address].vector_word = data_word;
    else if (19 == command_code)
        device_data->remote_terminal.addresses[address].selftest_word = data_word;

    unerror(set_rt_configuration(session, address, VI_TRUE,
                                 device_data->remote_terminal.addresses[address].status_word,
                                 device_data->remote_terminal.addresses[address].vector_word,
                                 device_data->remote_terminal.addresses[address].selftest_word));

Error:
    return status;
}

//! \brief Функция unmmko1_rt_start запускает мезонин в режиме оконечного устройства.
//! Настройки режима предварительно устанавливаются функцией unmmko1_rt_configure.
//! \param session Номер сеанса связи с мезонином.
//! \return Код ошибки или код успешного выполнения функции.
ViStatus _VI_FUNC unmmko1_rt_start(ViSession session) {
    ViStatus status = VI_SUCCESS;
    unmmko1_device_data* device_data = get_device_data_or_error(session);

    if (UNMMKO1_MODE_UNDEFINED == device_data->current_mode)
        unerror(unmmko1_rt_configure(session, 0x0000, UNMMKO1_RT_DEFAULT));

    if (UNMMKO1_MODE_REMOTE_TERMINAL != device_data->current_mode)
        return UNMMKO1_ERROR_WAS_CONFIGURED_IN_A_DIFFERENT_MODE;

    if (device_data->remote_terminal.is_started)
        return UNMMKO1_WARNING_ALREADY_STARTED;

    unerror(start_rt(session, device_data->remote_terminal.options & UNMMKO1_USE_MASK));
    device_data->remote_terminal.is_started = VI_TRUE;

Error:
    return status;
}

//! \brief Функция unmmko1_rt_status возвращает состояние запуска мезонина в режиме оконечного устройства.
//! \param session Номер сеанса связи с мезонином.
//! \param status Состояние запуска оконечного устройства (VI_TRUE - режим оконечного устройства запущен, VI_FALSE - остановлен).
//! \return Код ошибки или код успешного выполнения функции.
ViStatus _VI_FUNC unmmko1_rt_status(ViSession session, ViBoolean* status) {
    unmmko1_device_data* device_data = get_device_data_or_error(session);

    if (is_not_valid_pointer(status))
        return VI_ERROR_PARAMETER2;

    *status = device_data->remote_terminal.is_started;
    return VI_SUCCESS;
}

//! \brief Функция unmmko1_rt_stop останавливает мезонин, запущенный ранее в режиме оконечного устройства.
//! \param session Номер сеанса связи с мезонином.
//! \return Код ошибки или код успешного выполнения функции.
ViStatus _VI_FUNC unmmko1_rt_stop(ViSession session) {
    ViStatus status = VI_SUCCESS;
    unmmko1_device_data* device_data = get_device_data_or_error(session);

    if (UNMMKO1_MODE_REMOTE_TERMINAL != device_data->current_mode)
        return UNMMKO1_ERROR_WAS_CONFIGURED_IN_A_DIFFERENT_MODE;

    if (!device_data->remote_terminal.is_started)
        return UNMMKO1_WARNING_ALREADY_STOPPED;

    unerror(stop_rt(session));
    device_data->remote_terminal.is_started = VI_FALSE;

Error:
    return status;
}
