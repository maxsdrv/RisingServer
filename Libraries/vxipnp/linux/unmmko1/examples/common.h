#ifndef UNMMKO1_EXAMPLES_COMMON_H
#define UNMMKO1_EXAMPLES_COMMON_H

#include <visa.h>
#include <vpptype.h>
#include <unmbase.h>
#include <unmmko1.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

static ViChar resource_name[256];
static ViUInt16 position = 0;
static ViSession carrier_session = 0, session = 0;

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
int key_pressed() {
    return _kbhit();
}
#else
#include <unistd.h>
int key_pressed() {
    return 0;
}
void Sleep(int msec) {
    int sec;
    int usec;

    sec = msec / 1000;
    usec = (msec % 1000) * 1000;
    if (sec > 0)
        sleep(sec);
    if (usec > 0)
        usleep(usec);
}
#endif

//! Проверка ошибок, используется при вызове функций драйвера мезонина MKO
void process_unmmko1_error(ViSession session, ViStatus status) {
    ViChar str[256];
    unmmko1_error_message(session, status, str);
    printf("Returnes status code %ld with message: %s\n", status, str);
}

//! Проверка ошибок, используется при вызове функций драйвера Носителя Мезонинов
void process_unmbase_error(ViSession session, ViStatus status) {
    ViChar str[256];
    unmbase_error_message(session, status, str);
    printf("Returnes status code %ld with message: %s\n", status, str);
}

//! Макрос для проверки ошибок при работе с UNMKO
#define unmkocheck(f) if ((status = (f)) < 0) { \
    printf("%s %d %s ", __FILE__, __LINE__, __FUNCTION__); \
    process_unmmko1_error(session, status); return status; } \
    else

//! Макрос для проверки ошибок
#define unmbasecheck(f) if ((status = (f)) < 0) { \
    printf("%s %d %s ", __FILE__, __LINE__, __FUNCTION__); \
    process_unmbase_error(carrier_session, status); return status; } \
    else

//! Поиск мезонина MKO
//! \param resource_name Адрес Носителя Мезонинов, на котором найден мезонин MKO
//! \param position Позиция мезонина MKO на Носителе Мезонинов
//! \returns VI_TRUE в случае, если найден мезонин MKO, VI_FALSE - в противном случае
ViStatus search_unmmko1(ViChar resource_name[], ViUInt16* position) {
    ViSession resource_manager_session = 0;
    ViString search_pattern = "?*[0-9]?*::?*::INSTR";
    ViFindList find_list;
    ViStatus found = VI_ERROR_RSRC_NFOUND;
    ViUInt32 index = 0, count = 0;
    ViSession device_session = 0, carrier_session = 0;
    ViUInt16 interface_type = 0;
    ViInt16 mezzanine_number = 1;
    char address[256];

    // Открываем сессию с VISA
    if (viOpenDefaultRM(&resource_manager_session) < 0)
        goto Error;

    // Поиск устройств
    if (viFindRsrc(resource_manager_session, search_pattern, &find_list, &count, address) < 0)
        goto Error;

    // Проходим по всем найденным устройствам
    for (index = 0; index < count; ++index) {
        // Устройства не найдены
        if (index && viFindNext(find_list, address) < 0)
            goto Error;

        // Открываем устройство
        if (viOpen(resource_manager_session, address, VI_NULL, VI_NULL, &device_session) < 0)
            continue;

        // Считываем тип интерфейса
        viGetAttribute(device_session, VI_ATTR_INTF_TYPE, &interface_type);

        // Тип интерфейса VXI или GPIB-VXI
        if (VI_INTF_VXI == interface_type || VI_INTF_GPIB_VXI == interface_type) {
            ViUInt32 slot_number = 0;
            ViUInt16 manufactory_id = 0, model_code = 0;

            // Не работаем с устройствами в слоте 0
            if (viGetAttribute(device_session, VI_ATTR_SLOT, &slot_number) < 0 || 0 == slot_number)
                goto CloseDevice;

            // Запрашиваем идентификатор производителя и код модели устройства
            if (viGetAttribute(device_session, VI_ATTR_MANF_ID, &manufactory_id) < 0)
                goto CloseDevice;
            if (viGetAttribute(device_session, VI_ATTR_MODEL_CODE, &model_code) < 0)
                goto CloseDevice;

            // Сравниваем идентификаторы с идентификаторами различных версий Носителей Мезонинов
            if (UN_MANUFACTURER_ID != manufactory_id)
                goto CloseDevice;
            model_code &= 0x0fff;
            if (UNMBASE_MODEL_CODE != model_code && UNMBASEU_MODEL_CODE != model_code && UNMBASE_MODEL_ARMVXI != model_code)
                goto CloseDevice;
        }
        // Тип интерфейса VXI или GPIB-VXI
        else
            if (VI_INTF_TCPIP == interface_type || VI_INTF_USB == interface_type || VI_INTF_GPIB == interface_type || VI_INTF_ASRL == interface_type) {
                ViChar idn[256];
                ViStatus status = VI_SUCCESS;

                if (viLock(device_session, VI_EXCLUSIVE_LOCK, 2000, 0, 0) < 0)
                    goto CloseDevice;

                status = viQueryf(device_session, "*IDN?\n", "%t", idn);
                viUnlock(device_session);

                if (status < 0)
                    goto CloseDevice;

                if (0 != strncmp(idn, UNMBASE_MEZABOX_IDN, strlen(UNMBASE_MEZABOX_IDN)))
                    goto CloseDevice;
            }

        // Инициализируем Носитель Мезонинов и считываем коды мезонинов
        if (unmbase_init(address, VI_ON, VI_ON, &carrier_session) < 0)
            goto CloseDevice;

        for (mezzanine_number = 1; mezzanine_number <= 8; ++mezzanine_number) {
            ViInt16 present, model_code;
            if (unmbase_m_type_q(carrier_session, mezzanine_number, &present, &model_code) < 0 || 0 == present)
                continue;

            if (UNMMKO1_MODEL_CODE == (model_code & 0x0fff)) {
                strcpy(resource_name, address);
                *position = (ViUInt16)mezzanine_number;
                found = VI_SUCCESS;
                break;
            }
        }

        unmbase_close(carrier_session);

CloseDevice:
        viClose(device_session);
        if (VI_SUCCESS == found)
            break;
    }

Error:
    if (resource_manager_session)
        viClose(resource_manager_session);

    if (VI_SUCCESS == found)
        printf("Mezzanine MKO found at %s on %d position\n", resource_name, *position);

    return found;
}

void print_messages(ViUInt32 messages_count, unmmko1_message* messages) {
    ViUInt32 message_index = 0;
    for (message_index = 0; message_index < messages_count; ++message_index) {
        ViUInt16 data_word_index = 0;
        unmmko1_message message = messages[message_index];
        uint64_t timestamp = (((uint64_t)message.timestamp_high) << 32) + message.timestamp_low;
        printf("%llu %s\n", timestamp, (message.activity & UNMMKO1_MSG_ACT_BUS_A) ? "(A)" : "(B)");

        if (message.activity & UNMMKO1_MSG_ACT_CWD_1)
            printf("CW1 %x\n", message.command.command_word_1);
        if (message.activity & UNMMKO1_MSG_ACT_CWD_2)
            printf("CW2 %x\n", message.command.command_word_2);

        if (0 != message.command.data_words_count) {
            printf("DWS_C (%u):", message.command.data_words_count);
            for (data_word_index = 0; data_word_index < message.command.data_words_count; ++data_word_index)
                printf(" %x", message.command.data_words[data_word_index]);
            printf("\n");
        }

        if (message.activity & UNMMKO1_MSG_ACT_SWD_1) {
            printf("SW1 %x\n", message.response_1.status_word);
            if (0 != message.response_1.data_words_count) {
                printf("DWS_R1 (%u):", message.response_1.data_words_count);
                for (data_word_index = 0; data_word_index < message.response_1.data_words_count; ++data_word_index)
                    printf(" %x", message.response_1.data_words[data_word_index]);
                printf("\n");
            }
        }
        if (message.activity & UNMMKO1_MSG_ACT_SWD_2) {
            printf("SW2 %x\n", message.response_2.status_word);
            if (0 != message.response_2.data_words_count) {
                printf("DWS_R2 (%u):", message.response_2.data_words_count);
                for (data_word_index = 0; data_word_index < message.response_2.data_words_count; ++data_word_index)
                    printf(" %x", message.response_2.data_words[data_word_index]);
                printf("\n");
            }
        }

        printf("State:\n");
        if (UNMMKO1_MSG_ERR_OK == message.error)
            printf("   OK\n");
        if (message.error & UNMMKO1_MSG_ERR_NO_RESPONSE)
            printf("   No response\n");
        if (message.error & UNMMKO1_MSG_ERR_ANY_ERROR_BIT)
            printf("   Any error bit\n");
        if (message.error & UNMMKO1_MSG_ERR_PROTOCOL)
            printf("   Protocol error\n");
        if (message.error & UNMMKO1_MSG_ERR_DATA_COUNT)
            printf("   Data count error\n");
        if (message.error & UNMMKO1_MSG_ERR_MANCHECTER)
            printf("   Manchester error\n");
        if (message.error & UNMMKO1_MSG_ERR_SYSTEM)
            printf("   System error\n");

        printf("\n");
    }

    fflush(stdout);
}

#endif // UNMMKO1_EXAMPLES_COMMON_H
