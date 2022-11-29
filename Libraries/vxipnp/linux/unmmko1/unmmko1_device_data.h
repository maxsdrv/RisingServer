#ifndef UNMMKO1_DEVICE_DATA_H
#define UNMMKO1_DEVICE_DATA_H

#include <visa.h>

#include "un_threads.h"
#include "unmmko1.h"
#include <stddef.h>
#include "internal/un_threads.h"
#include "internal/un_queue.h"
#include "internal/unmmko1_constants.h"

#ifndef ViUInt64
#include <stdint.h>
#define ViUInt64 uint64_t
#endif

typedef enum {
    UNMMKO1_MODE_UNDEFINED          = 0x00,
    UNMMKO1_MODE_BUS_CONTROLLER     = 0x01,
    UNMMKO1_MODE_REMOTE_TERMINAL    = 0x02,
    UNMMKO1_MODE_BUS_MONITOR        = 0x03
} unmmko1_mode;

//! Тип подключения.
typedef enum {
    UNMMKO1_DIRECT                  = 0x0000,   //!< Непосредственное подключение.
    UNMMKO1_TRANSFORM               = 0x0001    //!< Трансформаторное подключение (по умолчанию).
} unmmko1_connection_type;

//! Обрабатываемые магистрали
typedef enum {
    UNMMKO1_USE_BUS_A_AND_B         = 0x0000,   //!< Обработка магистралей A и B (по умолчанию)
    UNMMKO1_USE_ONLY_BUS_A          = 0x0002,   //!< Обработка только по магистрали A
    UNMMKO1_USE_ONLY_BUS_B          = 0x0004,   //!< Обработка только по магистрали B
    UNMMKO1_USE_MASK                = 0x0006    //!< Маска выбора магистралей
} unmmko1_bus_usage;

typedef struct {
    ViUInt64 timestamp;
    ViUInt16 state;
    ViUInt16 value;
} milstd1553_word_s;

typedef enum {
    f_rubbish,                                  //!< Остатки от старых сообщений
    f_unknown                       = 0x0001,   //!< Формат данных не определён
    // Форматы основных сообщений (1 - 6)
    f1                              = 0x0002,   //!< КС-СД-СД-...-СД  <->  ОС                     Передача данных от КШ к ОУ
    f2                              = 0x0004,   //!< КС  <->  ОС-СД-СД-...-СД                     Передача данных от ОУ к КШ
    f3                              = 0x0008,   //!< КС-КС  <->  ОС-СД-СД-...-СД  <->  ОС         Передача данных от ОУ к ОУ
    f4                              = 0x0010,   //!< КС  <->  ОС                                  Передача команды управления
    f5                              = 0x0020,   //!< КС  <->  ОС-СД                               Передача команды управления и приём слова данных
    f6                              = 0x0040,   //!< КС-СД  <->  ОС                               Передача команды управления со словом данных
    // Форматы групповых сообщений (7 - 10)
    f7                              = 0x0080,   //!< КС-СД-СД-...-СД                              Групповая передача данных от КШ ко всем ОУ
    f8                              = 0x0100,   //!< КС-КС  <->  ОС-СД-СД-...-СД                  Групповая передача от определённого ОУ ко всем остальным ОУ
    f9                              = 0x0200,   //!< КС                                           Групповая передача команды управления
    f10                             = 0x0400    //!< КС-СД                                        Групповая передача команды управления со словом данных
} message_format_enum;

#pragma pack(push)
#pragma pack(1)

//! Непрерывная последовательность слов
typedef struct {
    ViUInt64        timestamp;
    size_t          count;
    ViUInt64        types;
    ViUInt16        values[40];
    ViUInt16        errors;
    ViUInt64        gap;
} sequence_s;

#pragma pack(pop)

//! Время отсутствия ответа по умолчанию
#define default_timeout_value_in_us     14

//! Аккумулятор разбора слов
typedef struct {
    sequence_s sequence_a[3];                               //!< Последовательности разбора сообщений магистрали A
    sequence_s sequence_b[3];                               //!< Последовательности разбора сообщений магистрали B
    ViUInt64 last_a_timestamp;                              //!< Время последнего сообщения магистрали A
    ViUInt64 last_b_timestamp;                              //!< Время последнего сообщения магистрали B
    ViUInt64 current_timestamp;                             //!< Текущая метка времени (используется для определения паузы после последнего слова)
    ViUInt64 timeout_value_in_us;                           //!< Время отсутствия ответа
} accumulator_t;

//! Сброс аккумулятора разбора слов
void reset_accumulator(accumulator_t* accumulator);

//! Правила фильтрации сообщений
typedef struct {
    ViUInt32 addresses_mask;                                //!< Маска адресов оконечных устройств, которые подлежат мониторированию
    ViUInt32 receive_subaddresses[32];                      //!< Битовая маска подадресов приёма для каждого оконечного устройства
    ViUInt32 transmit_subaddresses[32];                     //!< Битовая маска подадресов передачи для каждого оконечного устройства
    ViUInt32 receive_modecodes[32];                         //!< Битовая маска команд управления приёма для каждого оконечного устройства
    ViUInt32 transmit_modecodes[32];                        //!< Битовая маска команд управления передачи для каждого оконечного устройства
} filter_rules_t;

//! Сброс правил фильтрации сообщений
void reset_filter_rules(filter_rules_t* filter_rules);

//! Настройки монитора шины
typedef struct {
    ViBoolean is_started;                                   //!< Флаг состояния запуска
    int options;                                            //!< Флаги настроек монитора
    accumulator_t accumulator;                              //!< Аккумулятор разбора слов монитора
    un_queue* messages;                                     //!< Очередь сообщений монитора
    filter_rules_t filter_rules;                            //!< Правила фильтрации сообщений монитора
} bus_monitor_settings_t;

void create_bus_monitor_settings(bus_monitor_settings_t* bus_monitor_settings);
void reset_bus_monitor_settings(bus_monitor_settings_t* bus_monitor_settings);
void destroy_bus_monitor_settings(bus_monitor_settings_t* bus_monitor_settings);

#define invalid_status_word 0xffffu

#pragma pack(push)
#pragma pack(1)

//! Настройки оконечного устройства
typedef struct {
    ViBoolean is_started;                                   //!< Флаг состояния запуска
    int options;                                            //!< Флаги настроек оконечного устройства

    struct {
        bool active;                                        //!< Активность оконечного устройства
        ViUInt16 vector_word;                               //!< Слово данных на КУ 16 "Передать векторное слово"
        ViUInt16 selftest_word;                             //!< Слово данных на КУ 19 "Передать слово ВСК ОУ"
        ViUInt16 status_word;                               //!< Ответное слово
        struct {
            unmmko1_rt_subaddress_options options;          //!< Настройки ответного сегмента
            ViUInt16 data_words_count;                      //!< Количество слов данных
            ViUInt16* data_words;                           //!< Слова данных
        } subaddresses[31];
    } addresses[31];
} remote_terminal_settings_t;

#pragma pack(pop)

void create_remote_terminal_settings(remote_terminal_settings_t* remote_terminal_settings);
void reset_remote_terminal_settings(remote_terminal_settings_t* remote_terminal_settings);
void destroy_remote_terminal_settings(remote_terminal_settings_t* remote_terminal_settings);

//! Настройки контроллера шины
typedef struct {
    ViBoolean is_started;                                   //!< Флаг состояния запуска
    int options;                                            //!< Флаги настроек контроллера шины

    un_queue* schedule;                                     //!< Расписание из командных сегментов
    ViUInt16 repeat_count;                                  //!< Количество повторений расписания
} bus_controller_settings_t;

void create_bus_controller_settings(bus_controller_settings_t* bus_controller_settings);
void reset_bus_controller_settings(bus_controller_settings_t* bus_controller_settings);
void destroy_bus_controller_settings(bus_controller_settings_t* bus_controller_settings);

//! Структура данных мезонина
typedef struct {
    ViUInt16 model_code;                                    //!< Код модели мезонина
    ViSession init_session;                                 //!< Сессия, полученная при инициализации мезонина
    ViSession session;                                      //!< Сессия мезонина
    ViSession carrier_session;                              //!< Сессия носителя мезонинов
    UNMMKO1_EVENT_HANDLER interrupt_request_handler;        //!< Пользовательский обработчик прерываний
    ViAddr interrupt_request_data;                          //!< Указатель на данные, передаваемые в пользовательский обработчик прерываний
    ViUInt16 command_counter;                               //!< Счётчик команд

    unmmko1_mode current_mode;                              //!< Текущий режим работы мезонина
    bus_monitor_settings_t bus_monitor;                     //!< Настройки монитора шины
    remote_terminal_settings_t remote_terminal;             //!< Настройки оконечного устройства
    bus_controller_settings_t bus_controller;               //!< Настройки контроллера шины
} unmmko1_device_data;

//! \brief Функция запроса указателя на данные мезонина по аттрибуту в VISA
unmmko1_device_data* get_device_data_from_visa(ViSession session);

//! \brief Функция запроса указателя на данные мезонина по аттрибуту в носителе мезонинов
unmmko1_device_data* get_device_data_from_carrier(ViSession session);

//! \brief Макрос объявления и запроса указателя на данные мезонина по аттрибуту в носителе мезонинов
//! Создаёт device_data равный NULL, если данные мезонина с указанной сессией не найдены или некорректны
#define get_device_data(session) \
    get_device_data_from_carrier(session); \
    if (is_not_valid_device_data(device_data)) device_data = NULL;

//! \brief Макрос объявления и запроса указателя на данные мезонина по аттрибуту в носителе мезонинов
//! \returns Возвращает ошибку VI_ERROR_INV_SETUP, если данные мезонина с указанной сессией не найдены или некорректны
#define get_device_data_or_error(session) \
    get_device_data_from_carrier(session); \
    if (is_not_valid_device_data(device_data)) return VI_ERROR_INV_SETUP

//! \brief Функция проверки некорректности указателя на данные мезонина
ViBoolean is_not_valid_device_data(unmmko1_device_data* data);

//! \brief Создание структуры данных мезонина
//! \param[out] device_data Указатель на указатель на структуру данных мезонина
ViStatus create_device_data(unmmko1_device_data** device_data);

//! \brief Заполнение структуры данных мезонина с использованием функций, обращающихся к мезонину для считывания параметров
//! \param[in] device_data Указатель на структуру данных мезонина с валидной сессией мезонина
ViStatus fill_device_data(unmmko1_device_data* device_data);

//! Уничтожение структуры данных мезонина
//! \param[in] device_data Указатель на структуру данных мезонина
ViStatus destroy_device_data(unmmko1_device_data* device_data);

//! Сброс структуры данных мезонина в исходный вид
//! \param[in] device_data Указатель на структуру данных мезонина
ViStatus reset_device_data(unmmko1_device_data* device_data);

//! Обработчик прерываний от носителя мезонинов
ViBoolean _VI_FUNCH interrupt_request_handler(ViSession session, ViInt32 reason);

#endif // UNMMKO1_DEVICE_DATA_H
