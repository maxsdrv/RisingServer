#include "Actions.h"

SearchUnmmko::SearchUnmmko()
		:
		position(nullptr),
		resource_manager_session(0), find_list(0), index(0),
		count(0), device_session(0),
		carrier_session(0), interface_type(0), mezzanine_number(1)
{
}

int32_t SearchUnmmko::search()
{

	std::cout << "Debug information about calling method search" << '\n';

	/* Lambdas instead goto definitions in C implementation common.h */
	auto Error = [this]() {
	  if (resource_manager_session)
		  viClose(resource_manager_session);

	  if (VI_SUCCESS==found)
		  printf("Mezzanine MKO found at %s on %d position\n", resourceName.c_str(), *position);
	};
	auto CloseDevice = [this]() {
	  viClose(device_session);
	  if (VI_SUCCESS==found)
		  return;
	};

	//  Open Session with VISA
	if (viOpenDefaultRM(&resource_manager_session)<0)
		Error();

	// Find devices
	if (viFindRsrc(resource_manager_session, const_cast<char*>(search_pattern.c_str()), &find_list, &count, address)<0)
		Error();

	// Pass to all found devices
	for (index = 0; index<count; ++index) {
		// Devices not found
		if (index && viFindNext(find_list, address)<0)
			Error();

		// Open device
		if (viOpen(resource_manager_session, address, VI_NULL, VI_NULL, &device_session)<0)
			continue;

		// Read interface type
		viGetAttribute(device_session, VI_ATTR_INTF_TYPE, &interface_type);

		// Interface type VXI или GPIB-VXI
		if (VI_INTF_VXI==interface_type || VI_INTF_GPIB_VXI==interface_type) {
			ViUInt32 slot_number = 0;
			ViUInt16 manufactory_id = 0, model_code = 0;

			// Don't work in slot number 0
			if (viGetAttribute(device_session, VI_ATTR_SLOT, &slot_number)<0 || 0==slot_number)
				CloseDevice();

			// Request the manufacturer's identifier and device model code
			if (viGetAttribute(device_session, VI_ATTR_MANF_ID, &manufactory_id)<0)
				CloseDevice();
			if (viGetAttribute(device_session, VI_ATTR_MODEL_CODE, &model_code)<0)
				CloseDevice();

			//Compare ID with ID any version Carriers Mezzanines
			if (UN_MANUFACTURER_ID!=manufactory_id)
				CloseDevice();

			model_code &= 0x0fff;
			if (UNMBASE_MODEL_CODE!=model_code && UNMBASEU_MODEL_CODE!=model_code
					&& UNMBASE_MODEL_ARMVXI!=model_code)
				CloseDevice();
		}
			//Interface type VXI or GPIB-VXI
		else if (VI_INTF_TCPIP==interface_type || VI_INTF_USB==interface_type || VI_INTF_GPIB==interface_type
				|| VI_INTF_ASRL==interface_type) {
			ViChar idn[256];
			ViStatus status = VI_SUCCESS;

			if (viLock(device_session, VI_EXCLUSIVE_LOCK, 2000, 0, 0)<0)
				CloseDevice();

			status = viQueryf(device_session, "*IDN?\n", "%t", idn);
			viUnlock(device_session);

			if (status<0)
				CloseDevice();

			if (0!=strncmp(idn, UNMBASE_MEZABOX_IDN, strlen(UNMBASE_MEZABOX_IDN)))
				CloseDevice();
		}

		// Initialise Carrier Mezzanine and read code of mezzanines
		if (unmbase_init(address, VI_ON, VI_ON, &carrier_session)<0)
			CloseDevice();

		for (mezzanine_number = 1; mezzanine_number<=8; ++mezzanine_number) {
			ViInt16 present, model_code;
			if (unmbase_m_type_q(carrier_session, mezzanine_number, &present, &model_code)<0 || 0==present)
				continue;

			if (UNMMKO1_MODEL_CODE==(model_code & 0x0fff)) {
				strcpy(const_cast<char*>(resourceName.c_str()), address);
				*position = (ViUInt16)mezzanine_number;
				found = VI_SUCCESS;
				break;
			}
		}

		unmbase_close(carrier_session);

	}

	return this->found;
}

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
