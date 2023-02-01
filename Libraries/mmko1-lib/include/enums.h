#pragma once

enum class BUSLINE {
	MKO_BUS_A = 0x0001,
	MKO_BUS_B = 0x0002
};

/* NOTE: rxtx it is Reception/Transmission bit that specifies in unmmko1.h function
 * by default it is using like Receive mode (i.e 0) */
enum class RXTX {
	RECEIVE,
	TRANSMIT
};

/* Enum class of Command Direction by ГОСТ Р52070-2003 */
enum class CONTROL_COMMANDS {
	CTR_INTERFACE,
	SYNC,
	TRANSMIT_RESPONSE_WORD,
	START_SELF_TEST,
	BLOCK_TRANSMITTER,
	UNBLOCK_TRANSMITTER,
	BLOCK_ERROR_FLAG,
	UNBLOCK_ERROR_FLAG,
	RESET_DEVICE_TRANSMIT,
	TRANSMIT_VECTOR_WORD = 16,
	SYNC_DATA_WORD,
	TRANSMIT_LAST_CMD,
	TRANSMIT_VSK_WORD,
	BLOCK_Ith_TR,
	UNBLOCK_Ith_TR,
	END
};