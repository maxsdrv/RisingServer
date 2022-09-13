#pragma once

/* Class for work in Bus-Controller mode */

#include <functional>

#include "TestMmko.h"

class ControllerMode {
private:
	friend class TestMmko;
	explicit ControllerMode(TestMmko* objectMmko1, const uint16& rxtx, int bcoptions);

public:
	~ControllerMode();
	/* Create command word
     * method creates 16-bit command word from fields
	 * address - address terminal device
	 * rx_tx - Reception/transmission bit(reception - 0, transmission - 1
	 * subaddress - subaddress/manage mode
	 * word_count - count of words/manage command code
	 * */
	static uint16 PackCw(uint16 address, uint16 RxTx, uint16 subAddress, uint16 wordCount);
	/* Method for exchange data between bus-controller and terminal-device */
	int32 BusToTerminalReceive(uint16 address, uint16 subAddress, uint16 wordCount, uint16* dataWords) const;
	/* Method for exchange messages in format F1
    * - messages format for transmit data-word from controller to terminal-device */
	int32 transmitCmdF1(uint16 address, uint16 subAddress, uint16 wordCount, uint16 *dataWords);

    /* noncopyable class */
    ControllerMode(const ControllerMode&) = delete;
    ControllerMode(ControllerMode&&) = delete;
    ControllerMode& operator=(const ControllerMode&) = delete;
    ControllerMode& operator=(ControllerMode&&) = delete;

	/* Getters and Setters */
	void setRxTx(uint16 RxTx);
	[[nodiscard]] uint16 getRxTx() const;
	void setBcOptions(int bcOptions_);
	[[nodiscard]] int getBcOptions() const;

private:
	TestMmko* testMmko;
	std::unique_ptr<unmmko1_command> commands;
	uint16 mRxTx; // TODO data transmit/receive bit, needed will know how this use
	int bcOptions; // for function bc_configure, 0 by default
};








