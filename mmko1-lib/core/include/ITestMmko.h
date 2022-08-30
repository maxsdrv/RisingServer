#pragma once

#include <vector>
#include <unmmko1.h>
#include <memory>

#include "defines.h"
#include "Actions.h"


class ITestMmko {
public:
	explicit ITestMmko()
			:
			common(std::make_unique<Common>()),
			commands(std::make_unique<unmmko1_command>())
	{
		MKOTEXT("ITestMmko()");
	};
	virtual ~ITestMmko() { MKOTEXT("~ITestMmko()") }

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
	virtual int PackCw(uint16_t address, uint16_t RxTx, uint16_t subAddress, uint16_t wordCount) = 0;

protected:
	std::unique_ptr<Common> common;
	std::unique_ptr<unmmko1_command> commands;
};


