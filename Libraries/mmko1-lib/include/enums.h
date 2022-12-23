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