#pragma once

#include <unmmko1.h>
#include <memory>

#include "defines.h"
#include "Actions.h"
#include "Object.h"

class ITestMmko {
public:
	virtual ~ITestMmko() { MKOTEXT("~ITestMmko()"); }

/* methods for working Mezzanine MKO */
/* Base methods */
	virtual void Init() = 0; // Base initialisation Mezzanine MMKO
	virtual void SelfTest() = 0; // make test with Mezzanine
	virtual void Close() = 0; // close connect Mezzanine MKO and carrier Mezzanine

	/* method creates 16-bit command word from fields
	 * address - address terminal device
	 * rx_tx - Reception/transmission bit(reception - 0, transmission - 1
	 * subaddress - subaddress/manage mode
	 * word_count - count of words/manage command code
	 * */
	virtual uint16_t PackCw(uint16_t address, uint16_t RxTx, uint16_t subAddress, uint16_t wordCount) = 0;

protected:
	virtual void setBus(unmmko1_bus) = 0;
	virtual unmmko1_bus getBus() const = 0;
};







