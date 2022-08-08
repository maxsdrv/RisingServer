#ifndef UNMMKO1_EXAMPLES_COMMON_H
#define UNMMKO1_EXAMPLES_COMMON_H

#include <visa.h>
#include <vpptype.h>
#include <unmbase.h>
#include <unmmko1.h>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <cstdlib>

#include "Actions.h"
#include "SFileLogger.h"

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
int key_pressed()
{
	return 0;
}
void Sleep(int msec)
{
	int sec;
	int usec;

	sec = msec/1000;
	usec = (msec%1000)*1000;
	if (sec>0)
		sleep(sec);
	if (usec>0)
		usleep(usec);
}
#endif

//! Проверка ошибок, используется при вызове функций драйвера мезонина MKO
void process_unmmko1_error(ViSession session, ViStatus status)
{
	ViChar str[256];
	unmmko1_error_message(session, status, str);
	printf("Returnes status code %ld with message: %s\n", status, str);
	SFileLogger::getInstance().writeToLog(status, str);
}

//! Проверка ошибок, используется при вызове функций драйвера Носителя Мезонинов
void process_unmbase_error(ViSession session, ViStatus status)
{
	ViChar str[256];
	unmbase_error_message(session, status, str);
	printf("Returnes status code %ld with message: %s\n", status, str);
	SFileLogger::getInstance().writeToLog(status, str);
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

void print_messages(ViUInt32 messages_count, unmmko1_message* messages)
{
	ViUInt32 message_index = 0;
	for (message_index = 0; message_index<messages_count; ++message_index) {
		ViUInt16 data_word_index = 0;
		unmmko1_message message = messages[message_index];
		uint64_t timestamp = (((uint64_t)message.timestamp_high) << 32)+message.timestamp_low;
		printf("%llu %s\n", timestamp, (message.activity & UNMMKO1_MSG_ACT_BUS_A) ? "(A)" : "(B)");

		if (message.activity & UNMMKO1_MSG_ACT_CWD_1)
			printf("CW1 %x\n", message.command.command_word_1);
		if (message.activity & UNMMKO1_MSG_ACT_CWD_2)
			printf("CW2 %x\n", message.command.command_word_2);

		if (0!=message.command.data_words_count) {
			printf("DWS_C (%u):", message.command.data_words_count);
			for (data_word_index = 0; data_word_index<message.command.data_words_count; ++data_word_index)
				printf(" %x", message.command.data_words[data_word_index]);
			printf("\n");
		}

		if (message.activity & UNMMKO1_MSG_ACT_SWD_1) {
			printf("SW1 %x\n", message.response_1.status_word);
			if (0!=message.response_1.data_words_count) {
				printf("DWS_R1 (%u):", message.response_1.data_words_count);
				for (data_word_index = 0; data_word_index<message.response_1.data_words_count; ++data_word_index)
					printf(" %x", message.response_1.data_words[data_word_index]);
				printf("\n");
			}
		}
		if (message.activity & UNMMKO1_MSG_ACT_SWD_2) {
			printf("SW2 %x\n", message.response_2.status_word);
			if (0!=message.response_2.data_words_count) {
				printf("DWS_R2 (%u):", message.response_2.data_words_count);
				for (data_word_index = 0; data_word_index<message.response_2.data_words_count; ++data_word_index)
					printf(" %x", message.response_2.data_words[data_word_index]);
				printf("\n");
			}
		}

		printf("State:\n");
		if (UNMMKO1_MSG_ERR_OK==message.error)
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
