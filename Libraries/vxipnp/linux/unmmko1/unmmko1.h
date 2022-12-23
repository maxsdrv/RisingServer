#ifndef UNMMKO1_H
#define UNMMKO1_H

#ifdef __cplusplus
extern "C" {
#endif

#include <vpptype.h>

//! Код модели мезонина
#define UNMMKO1_MODEL_CODE                                                                (0x50)

// Коды ошибок и предупреждений
#define UNMMKO1_ERROR_OFFSET                                           (_VI_ERROR + 0x3FFC0E00L)
#define UNMMKO1_WARNING_OFFSET                                                     (0x3FFC0E00L)

#define UNMMKO1_WARNING_BAD_INITILIZATION                           (UNMMKO1_WARNING_OFFSET + 0)
#define UNMMKO1_WARNING_ALREADY_STARTED                             (UNMMKO1_WARNING_OFFSET + 1)
#define UNMMKO1_WARNING_ALREADY_STOPPED                             (UNMMKO1_WARNING_OFFSET + 2)
#define UNMMKO1_ERROR_UNKNOWN                                         (UNMMKO1_ERROR_OFFSET + 0)
#define UNMMKO1_ERROR_NULL_POINTER                                    (UNMMKO1_ERROR_OFFSET + 1)
#define UNMMKO1_ERROR_NOT_ENOUGH_MEMORY                               (UNMMKO1_ERROR_OFFSET + 2)
#define UNMMKO1_ERROR_INTERNAL                                        (UNMMKO1_ERROR_OFFSET + 3)
#define UNMMKO1_ERROR_SELFTEST                                        (UNMMKO1_ERROR_OFFSET + 4)
#define UNMMKO1_ERROR_WAS_CONFIGURED_IN_A_DIFFERENT_MODE              (UNMMKO1_ERROR_OFFSET + 5)
#define UNMMKO1_ERROR_ILLEGAL_OPERATION_WHILE_RUNNING                 (UNMMKO1_ERROR_OFFSET + 6)
#define UNMMKO1_ERROR_ILLEGAL_OPERATION_WHILE_STOPPED                 (UNMMKO1_ERROR_OFFSET + 7)
#define UNMMKO1_ERROR_RT_ADDRESS_WAS_NOT_CONFIGURED                   (UNMMKO1_ERROR_OFFSET + 8)
#define UNMMKO1_ERROR_CANNOT_UPDATE_DATA_WITH_QUEUE_MODE              (UNMMKO1_ERROR_OFFSET + 9)
#define UNMMKO1_ERROR_ILLEGAL_OPERATION_IN_SCHEDULE_MODE             (UNMMKO1_ERROR_OFFSET + 10)
#define UNMMKO1_ERROR_EXCEEDED_SCHEDULE_SIZE_LIMIT                   (UNMMKO1_ERROR_OFFSET + 11)

#define UNMMKO1_ERROR_FIRST_CODE                                         (UNMMKO1_ERROR_UNKNOWN)
#define UNMMKO1_ERROR_LAST_CODE                     (UNMMKO1_ERROR_EXCEEDED_SCHEDULE_SIZE_LIMIT)
#define UNMMKO1_WARNING_FIRST_CODE                           (UNMMKO1_WARNING_BAD_INITILIZATION)
#define UNMMKO1_WARNING_LAST_CODE                              (UNMMKO1_WARNING_ALREADY_STOPPED)

// Основные функции управления мезонином
//! Прототип функции пользовательского обработчика прерываний
typedef ViBoolean (_VI_FUNCH* UNMMKO1_EVENT_HANDLER) (ViSession session, ViInt32 reason, ViAddr user_data);

ViStatus _VI_FUNC unmmko1_init(ViRsrc resource_name, ViBoolean idn_query, ViBoolean do_reset, ViSession* session,
		unsigned int* p_int);
ViStatus _VI_FUNC unmmko1_connect(ViSession session, ViSession carrier_session, ViUInt16 mezzanine_number, ViBoolean idn_query, ViBoolean do_reset);
ViStatus _VI_FUNC unmmko1_self_test(ViSession session, ViInt16* result, ViChar message[]);
ViStatus _VI_FUNC unmmko1_test_exchange(ViSession session, ViInt16* result, ViChar message[]);
ViStatus _VI_FUNC unmmko1_test_memory(ViSession session, ViInt16* result, ViChar message[]);
ViStatus _VI_FUNC unmmko1_reset(ViSession session);
ViStatus _VI_FUNC unmmko1_install_interrupt_handler(ViSession session, UNMMKO1_EVENT_HANDLER handler, ViAddr data);
ViStatus _VI_FUNC unmmko1_error_query(ViSession session, ViPInt32 error, ViChar message[]);
ViStatus _VI_FUNC unmmko1_revision_query(ViSession session, ViChar software_version[], ViChar hardware_version[]);
ViStatus _VI_FUNC unmmko1_error_message(ViSession session, ViStatus status, ViChar error_message[]);
ViStatus _VI_FUNC unmmko1_close(ViSession session);

// Структуры и типы данных
//! Магистраль передачи/приёма информации
typedef enum {
    UNMMKO1_BUS_A                   = 0x0001,           //!< Основная магистраль
    UNMMKO1_BUS_B                   = 0x0002            //!< Резервная магистраль
} unmmko1_bus;

//! Флаги действий
//! Перечисленные действия используются в поле activity структур unmmko1_command и unmmko1_message
typedef enum {
    UNMMKO1_MSG_ACT_BUS_A           = UNMMKO1_BUS_A,    //!< Передача/приём по основной магистрали А (устанавливается в командном сегменте по умолчанию)
    UNMMKO1_MSG_ACT_BUS_B           = UNMMKO1_BUS_B,    //!< Передача/приём по резервной магистрали B
    UNMMKO1_MSG_ACT_CWD_1           = 0x0004,           //!< В сообщении или командном сегменте присутствует командное слово 1 (устанавливается в командном сегменте по умолчанию)
    UNMMKO1_MSG_ACT_CWD_2           = 0x0008,           //!< В сообщении или командном сегменте присутствует командное слово 2
    UNMMKO1_MSG_ACT_SWD_1           = 0x0010,           //!< В сообщении присутствует ответное слово 1
    UNMMKO1_MSG_ACT_SWD_2           = 0x0020            //!< В сообщении присутствует ответное слово 2
} unmmko1_message_activities;

//! Флаги ошибок, зафиксированных в сообщении
//! Перечисленные ошибки можно проверить в unmmko1_message.error, используя побитовое И
typedef enum {
    UNMMKO1_MSG_ERR_OK              = 0x0000,           //!< Ошибки не зафиксированы
    UNMMKO1_MSG_ERR_NO_RESPONSE     = 0x0001,           //!< Состояние отсутствие ответа (таймаут ожидания ответа)
    UNMMKO1_MSG_ERR_ANY_ERROR_BIT   = 0x0002,           //!< Установлен хотя бы один из признаков ошибки в ответном слове
    UNMMKO1_MSG_ERR_PROTOCOL        = 0x0004,           //!< Протокольная ошибка
    UNMMKO1_MSG_ERR_DATA_COUNT      = 0x0008,           //!< Некорректное количество слов данных
    UNMMKO1_MSG_ERR_MANCHECTER      = 0x0010,           //!< Ошибка манчестера
    UNMMKO1_MSG_ERR_SYSTEM          = 0x0040            //!< Внутренняя ошибка
} unmmko1_message_errors;

//! Биты ошибок
typedef enum {
    UNMMKO1_ERRBIT_MESSAGE_ERROR                    = 0x0400,   //!< [ОшС]  Ошибка в сообщении (9 бит)
    UNMMKO1_ERRBIT_INSTRUMENTATION                  = 0x0200,   //!< [ПОС]  Передача ответного слова (10 бит)
    UNMMKO1_ERRBIT_SERVICE_REQUEST                  = 0x0100,   //!< [ЗО]   Запрос на обслуживание (11 бит)
    UNMMKO1_ERRBIT_RESERVED_12                      = 0x0080,   //!< [12]   Резерв (12 бит)
    UNMMKO1_ERRBIT_RESERVED_13                      = 0x0040,   //!< [13]   Резерв (13 бит)
    UNMMKO1_ERRBIT_RESERVED_14                      = 0x0020,   //!< [14]   Резерв (14 бит)
    UNMMKO1_ERRBIT_BROADCAST_COMMAND_RECEIVED       = 0x0010,   //!< [ПГК]  Принята групповая команда (15 бит)
    UNMMKO1_ERRBIT_BUSY                             = 0x0008,   //!< [АЗ]   Абонент занят (16 бит)
    UNMMKO1_ERRBIT_SYSTEM_FLAG                      = 0x0004,   //!< [НА]   Неисправность абонента (17 бит)
    UNMMKO1_ERRBIT_DYNAMIC_BUS_CONTROL_ACCEPTANCE   = 0x0002,   //!< [ПУИ]  Принято управление интерфейсом (18 бит)
    UNMMKO1_ERRBIT_TERMINAL_FLAG                    = 0x0001    //!< [НОУ]  Неисправность ОУ (19 бит)
} unmmko1_error_bits;

//! Командный сегмент сообщения
typedef struct {
    ViUInt16 activity;              //!< Флаги действий из перечисления unmmko1_message_activities
    ViUInt16 command_word_1;        //!< Первое командное слово
    ViUInt16 command_word_2;        //!< Второе командное слово
    ViUInt16 data_words_count;      //!< Количество слов данных
    ViUInt16 data_words[32];        //!< Слова данных
} unmmko1_command;

//! Ответный сегмент сообщения
typedef struct {
    ViUInt16 status_word;           //!< Ответное слово
    ViUInt16 data_words_count;      //!< Количество слов данных
    ViUInt16 data_words[32];        //!< Слова данных
} unmmko1_response;

//! Структура сообщения
typedef struct {
    ViUInt32 timestamp_low;         //!< Метка времени (младшие 32 бита)
    ViUInt32 timestamp_high;        //!< Метка времени (старшие 32 бита)
    ViUInt16 activity;              //!< Флаги зафиксированных действий из перечисления unmmko1_message_activities
    ViUInt16 error;                 //!< Флаги зафиксированных ошибок из перечисления unmmko1_message_errors

    unmmko1_command  command;       //!< Командный сегмент сообщения
    unmmko1_response response_1;    //!< Первый ответный сегмент сообщения
    unmmko1_response response_2;    //!< Второй ответный сегмент сообщения
} unmmko1_message;

#ifndef UNMMKO1_DISABLE_CONSTANTS

//! Перечисление адресов оконечных устройств
typedef enum {
    RT_0,  RT_1,  RT_2,  RT_3,
    RT_4,  RT_5,  RT_6,  RT_7,
    RT_8,  RT_9,  RT_10, RT_11,
    RT_12, RT_13, RT_14, RT_15,
    RT_16, RT_17, RT_18, RT_19,
    RT_20, RT_21, RT_22, RT_23,
    RT_24, RT_25, RT_26, RT_27,
    RT_28, RT_29, RT_30, RT_31,

    RT_BCAST = RT_31
} unmmko1_address;

//! Перечисление подадресов оконечных устройств
typedef enum {
    SA_0,  SA_1,  SA_2,  SA_3,
    SA_4,  SA_5,  SA_6,  SA_7,
    SA_8,  SA_9,  SA_10, SA_11,
    SA_12, SA_13, SA_14, SA_15,
    SA_16, SA_17, SA_18, SA_19,
    SA_20, SA_21, SA_22, SA_23,
    SA_24, SA_25, SA_26, SA_27,
    SA_28, SA_29, SA_30, SA_31,

    SA_MC0  = SA_0,
    SA_MC31 = SA_31
} unmmko1_subaddress;

#endif

// Создание командных сегментов
unmmko1_command _VI_FUNC unmmko1_bc_rt(unmmko1_bus bus, ViUInt16 command_word, ViUInt16* data_words);
unmmko1_command _VI_FUNC unmmko1_rt_rt(unmmko1_bus bus, ViUInt16 command_word_1, ViUInt16 command_word_2);
unmmko1_command _VI_FUNC unmmko1_f1(unmmko1_bus bus, ViUInt16 address, ViUInt16 subaddress, ViUInt16 word_count, ViUInt16* data_words);
unmmko1_command _VI_FUNC unmmko1_f2(unmmko1_bus bus, ViUInt16 address, ViUInt16 subaddress, ViUInt16 word_count);
unmmko1_command _VI_FUNC unmmko1_f3(unmmko1_bus bus, ViUInt16 receive_address, ViUInt16 receive_subaddress, ViUInt16 transmit_address, ViUInt16 transmit_subaddress, ViUInt16 word_count);
unmmko1_command _VI_FUNC unmmko1_f4(unmmko1_bus bus, ViUInt16 address, ViUInt16 subaddress, ViUInt16 mode_code);
unmmko1_command _VI_FUNC unmmko1_f5(unmmko1_bus bus, ViUInt16 address, ViUInt16 subaddress, ViUInt16 mode_code);
unmmko1_command _VI_FUNC unmmko1_f6(unmmko1_bus bus, ViUInt16 address, ViUInt16 subaddress, ViUInt16 mode_code, ViUInt16 data_word);
unmmko1_command _VI_FUNC unmmko1_f7(unmmko1_bus bus, ViUInt16 subaddress, ViUInt16 word_count, ViUInt16* data_words);
unmmko1_command _VI_FUNC unmmko1_f8(unmmko1_bus bus, ViUInt16 receive_subaddress, ViUInt16 transmit_address, ViUInt16 transmit_subaddress, ViUInt16 word_count);
unmmko1_command _VI_FUNC unmmko1_f9(unmmko1_bus bus, ViUInt16 subaddress, ViUInt16 mode_code);
unmmko1_command _VI_FUNC unmmko1_f10(unmmko1_bus bus, ViUInt16 subaddress, ViUInt16 mode_code, ViUInt16 data_word);

// Создание и разбор командного слова
ViUInt16 _VI_FUNC unmmko1_pack_cw(ViUInt16 address, ViUInt16 rx_tx, ViUInt16 subaddress, ViUInt16 word_count);
void _VI_FUNC unmmko1_unpack_cw(ViUInt16 command_word, ViUInt16* address, ViUInt16* rx_tx, ViUInt16* subaddress, ViUInt16* word_count);

// Создание и разбор ответного слова
ViUInt16 _VI_FUNC unmmko1_pack_sw(ViUInt16 address, ViUInt16 error_bits);
void _VI_FUNC unmmko1_unpack_sw(ViUInt16 status_word, ViUInt16* address, ViUInt16* error_bits);

// Управление контроллером шины
//! Флаги настроек контроллера шины
//! Для включения нескольких опций используйте побитовое ИЛИ
//! Используются в качестве аргумента bc_options в функции unmmko1_bc_configure
typedef enum {
    UNMMKO1_BC_DEFAULT                      = 0x0000,   //!< Настройки по умолчанию

    UNMMKO1_BC_TRANSFORM                    = 0x0000,   //!< Трансформаторное подключение (по умолчанию)
    UNMMKO1_BC_DIRECT                       = 0x0001    //!< Непосредственное подключение
} unmmko1_bc_options;

//! Максимальное количество командных сегментов в расписании с учётом количества повторений
#define UNMMKO1_BC_SCHEDULE_SIZE_LIMIT      6500

ViStatus _VI_FUNC unmmko1_bc_configure(ViSession session, int bc_options);
ViStatus _VI_FUNC unmmko1_bc_reset(ViSession session);

ViStatus _VI_FUNC unmmko1_bc_schedule_command(ViSession session, unmmko1_command command);
ViStatus _VI_FUNC unmmko1_bc_set_schedule_repeat_count(ViSession session, ViUInt16 repeat_count);

ViStatus _VI_FUNC unmmko1_bc_start(ViSession session);
ViStatus _VI_FUNC unmmko1_bc_status(ViSession session, ViBoolean* status);
ViStatus _VI_FUNC unmmko1_bc_stop(ViSession session);

ViStatus _VI_FUNC unmmko1_bc_transmit_command(ViSession session, unmmko1_command command);

// Управление оконечным устройством
//! Флаги настроек оконечного устройства
//! Для включения нескольких опций используйте побитовое ИЛИ
//! Используются в качестве аргумента rt_options в функции unmmko1_rt_configure
typedef enum {
    UNMMKO1_RT_DEFAULT                      = 0x0000,   //!< Настройки по умолчанию

    UNMMKO1_RT_TRANSFORM                    = 0x0000,   //!< Трансформаторное подключение (по умолчанию)
    UNMMKO1_RT_DIRECT                       = 0x0001,   //!< Непосредственное подключение

    UNMMKO1_RT_BUS_A_AND_B                  = 0x0000,   //!< Оконечное устройство отвечает на сообщения, присланные по магистрали A и B (по умолчанию)
    UNMMKO1_RT_BUS_A                        = 0x0002,   //!< Оконечное устройство отвечает только на сообщения, присланные по магистрали A
    UNMMKO1_RT_BUS_B                        = 0x0004,   //!< Оконечное устройство отвечает только на сообщения, присланные по магистрали B

    UNMMKO1_RT_DEFAULT_RESPONSES            = 0x0000,   //!< Оконечное устройство создаёт ответы по умолчанию на все типы сообщений (по умолчанию)
    UNMMKO1_RT_CUSTOM_RESPONSES             = 0x0008    //!< Ответные сегменты оконечного устройства настраиваются отдельно для каждого сообщения
} unmmko1_rt_options;

//! Флаги настроек подадресов оконечного устройства
//! Используются в качестве аргумента options в функции unmmko1_rt_set_subaddress_options
typedef enum {
    UNMMKO1_RT_SUBADDRESS_DEFAULT           = 0x0000,   //!< Настройки по умолчанию
    UNMMKO1_RT_SUBADDRESS_WRAP              = 0x0001,   //!< Для указанных адреса и подадреса используется циклический возврат данных (принятые оконечным устройством данные перезаписывают данные на передачу)
    UNMMKO1_RT_SUBADDRESS_QUEUE             = 0x0002    //!< Для указанных адреса и подадреса используется режим очереди данных (число слов данных больше 32, при запросе данных ОУ возвращает следующие слова данные)
} unmmko1_rt_subaddress_options;

//! Максимальный размер очереди слов данных для всех подадресов в режиме UNMMKO1_RT_SUBADDRESS_QUEUE
#define UNMMKO1_RT_QUEUE_SIZE_LIMIT         262000

ViStatus _VI_FUNC unmmko1_rt_configure(ViSession session, ViUInt32 addresses, int rt_options);
ViStatus _VI_FUNC unmmko1_rt_reset(ViSession session);

ViStatus _VI_FUNC unmmko1_rt_set_status_word(ViSession session, ViUInt16 address, ViUInt16 status_word);
ViStatus _VI_FUNC unmmko1_rt_set_subaddress_options(ViSession session, ViUInt16 address, ViUInt16 subaddress, unmmko1_rt_subaddress_options subaddress_options);
ViStatus _VI_FUNC unmmko1_rt_set_subaddress_data(ViSession session, ViUInt16 address, ViUInt16 subaddress, int data_words_count, ViUInt16* data_words);
ViStatus _VI_FUNC unmmko1_rt_set_command_data(ViSession session, ViUInt16 address, ViUInt16 command_code, ViUInt16 data_word);

ViStatus _VI_FUNC unmmko1_rt_start(ViSession session);
ViStatus _VI_FUNC unmmko1_rt_status(ViSession session, ViBoolean* status);
ViStatus _VI_FUNC unmmko1_rt_stop(ViSession session);

// Управление монитором шины
//! Флаги настроек монитора
//! Для включения нескольких опций используйте побитовое ИЛИ
//! Используются в качестве аргумента mon_options в функции unmmko1_mon_configure
typedef enum {
    UNMMKO1_MON_DEFAULT                     = 0x0000,   //!< Настройки по умолчанию

    UNMMKO1_MON_TRANSFORM                   = 0x0000,   //!< Трансформаторное подключение (по умолчанию)
    UNMMKO1_MON_DIRECT                      = 0x0001,   //!< Непосредственное подключение

    UNMMKO1_MON_BUS_A_AND_B                 = 0x0000,   //!< Монитор шины мониторирует сообщения по магистралям A и B (по умолчанию)
    UNMMKO1_MON_BUS_A                       = 0x0002,   //!< Монитор шины мониторирует сообщения только по магистрали A
    UNMMKO1_MON_BUS_B                       = 0x0004    //!< Монитор шины мониторирует сообщения только по магистрали B
} unmmko1_mon_options;

ViStatus _VI_FUNC unmmko1_mon_configure(ViSession session, int mon_options);
ViStatus _VI_FUNC unmmko1_mon_reset(ViSession session);

ViStatus _VI_FUNC unmmko1_mon_set_timeout(ViSession session, ViUInt16 timeout_in_us);
ViStatus _VI_FUNC unmmko1_mon_filter_address(ViSession session, ViUInt32 addresses_mask);
ViStatus _VI_FUNC unmmko1_mon_filter_subaddress(ViSession session, ViUInt16 address, ViUInt32 receive_subaddresses, ViUInt32 transmit_subaddresses, ViUInt32 receive_modecodes, ViUInt32 transmit_modecodes);

ViStatus _VI_FUNC unmmko1_mon_start(ViSession session);
ViStatus _VI_FUNC unmmko1_mon_status(ViSession session, ViBoolean* status);
ViStatus _VI_FUNC unmmko1_mon_stop(ViSession session);

ViStatus _VI_FUNC unmmko1_mon_messages_count(ViSession session, ViUInt32* messages_count);
ViStatus _VI_FUNC unmmko1_mon_messages_read(ViSession session, ViUInt32 messages_count, unmmko1_message* messages, ViUInt32* read_messages_count);

#ifdef __cplusplus
}
#endif

#endif // UNMMKO1_H
