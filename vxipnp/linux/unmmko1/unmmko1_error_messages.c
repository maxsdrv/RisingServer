#include "unmmko1_error_messages.h"
#include <string.h>
#include <locale.h>

typedef struct {
    ViStatus status;
    const char* message;
} UNMMKO1_ERROR_MESSAGES_TABLE;

//! Таблица сообщений об ошибках мезонина на английском языке
static const UNMMKO1_ERROR_MESSAGES_TABLE ErrorMessagesInEnglish[] = {
    { UNMMKO1_WARNING_BAD_INITILIZATION,                    "Bad initialization" },
    { UNMMKO1_WARNING_ALREADY_STARTED,                      "Bus monitor is already started" },
    { UNMMKO1_WARNING_ALREADY_STOPPED,                      "Bus monitor is already stopped" },
    { UNMMKO1_ERROR_UNKNOWN,                                "Unknown error" },
    { UNMMKO1_ERROR_NULL_POINTER,                           "Null pointer used as parameter" },
    { UNMMKO1_ERROR_NOT_ENOUGH_MEMORY,                      "Not enough memory" },
    { UNMMKO1_ERROR_INTERNAL,                               "Internal error" },
    { UNMMKO1_ERROR_SELFTEST,                               "Selftest error" },
    { UNMMKO1_ERROR_WAS_CONFIGURED_IN_A_DIFFERENT_MODE,     "Device was configured in a different mode" },
    { UNMMKO1_ERROR_ILLEGAL_OPERATION_WHILE_RUNNING,        "Illegal operation while running" },
    { UNMMKO1_ERROR_ILLEGAL_OPERATION_WHILE_STOPPED,        "Illegal operation while stopped"},
    { UNMMKO1_ERROR_RT_ADDRESS_WAS_NOT_CONFIGURED,          "Remote terminal was not configured"},
    { UNMMKO1_ERROR_CANNOT_UPDATE_DATA_WITH_QUEUE_MODE,     "Cannot update data with queue mode"},
    { UNMMKO1_ERROR_ILLEGAL_OPERATION_IN_SCHEDULE_MODE,     "Illegal operation in schedule mode"},
    { UNMMKO1_ERROR_EXCEEDED_SCHEDULE_SIZE_LIMIT,           "Exceeded schedule size limit"}
};

//! Таблица сообщений об ошибках мезонина на русском языке
static const UNMMKO1_ERROR_MESSAGES_TABLE ErrorMessagesInRussian[] = {
    { UNMMKO1_WARNING_BAD_INITILIZATION,                    "Ошибка во время инициализации" },
    { UNMMKO1_WARNING_ALREADY_STARTED,                      "Устройство уже запущено" },
    { UNMMKO1_WARNING_ALREADY_STOPPED,                      "Устройство уже остановлено" },
    { UNMMKO1_ERROR_UNKNOWN,                                "Неизвестная ошибка" },
    { UNMMKO1_ERROR_NULL_POINTER,                           "Указатель NULL передан в качестве параметра" },
    { UNMMKO1_ERROR_NOT_ENOUGH_MEMORY,                      "Недостаточно памяти" },
    { UNMMKO1_ERROR_INTERNAL,                               "Внутренняя ошибка" },
    { UNMMKO1_ERROR_SELFTEST,                               "Ошибка самоконтроля" },
    { UNMMKO1_ERROR_WAS_CONFIGURED_IN_A_DIFFERENT_MODE,     "Устройство было сконфигурировано в другом режиме" },
    { UNMMKO1_ERROR_ILLEGAL_OPERATION_WHILE_RUNNING,        "Недопустимая операция при запущенном устройстве" },
    { UNMMKO1_ERROR_ILLEGAL_OPERATION_WHILE_STOPPED,        "Недопустимая операция при остановленном устройстве"},
    { UNMMKO1_ERROR_RT_ADDRESS_WAS_NOT_CONFIGURED,          "Оконечное устройство не настроено"},
    { UNMMKO1_ERROR_CANNOT_UPDATE_DATA_WITH_QUEUE_MODE,     "Недопустимо обновление данных в режиме очереди данных"},
    { UNMMKO1_ERROR_ILLEGAL_OPERATION_IN_SCHEDULE_MODE,     "Недопустимая операция в режиме работы по расписанию"},
    { UNMMKO1_ERROR_EXCEEDED_SCHEDULE_SIZE_LIMIT,           "Превышен предел размера расписания"}
};

void get_localized_error_message(ViStatus status, ViChar message[]) {
    ViUInt32 index = 0;
    char* current_locale = setlocale(LC_CTYPE, NULL);

    if (0 == strncmp(current_locale, "ru_RU", sizeof("ru_RU")) || 0 == strncmp(current_locale, "Russian_Russia", sizeof("Russian_Russia"))) {
        for (index = 0; index < sizeof(ErrorMessagesInRussian) / sizeof(UNMMKO1_ERROR_MESSAGES_TABLE); ++index)
            if (ErrorMessagesInRussian[index].status == status)
                strcpy(message, ErrorMessagesInRussian[index].message);
    }
    else {
        for (index = 0; index < sizeof(ErrorMessagesInEnglish) / sizeof(UNMMKO1_ERROR_MESSAGES_TABLE); ++index)
            if (ErrorMessagesInEnglish[index].status == status)
                strcpy(message, ErrorMessagesInEnglish[index].message);
    }
}
