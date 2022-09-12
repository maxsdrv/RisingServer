#pragma once

/* Class for work in Bus-Controller mode */

#include <functional>

#include "TestMmko.h"

class ControllerMode {
private:
//	explicit ControllerMode(const TestMmko& objectMmko1);
	explicit ControllerMode(TestMmko* objectMmko1);
//	~ControllerMode();
public:
	/* Create command word
     * method creates 16-bit command word from fields
	 * address - address terminal device
	 * rx_tx - Reception/transmission bit(reception - 0, transmission - 1
	 * subaddress - subaddress/manage mode
	 * word_count - count of words/manage command code
	 * */
	static uint16_t PackCw(uint16_t address, uint16_t RxTx, uint16_t subAddress, uint16_t wordCount);
	/* Method for exchange data between bus-controller and terminal-device */
	int32_t BusToTerminalReceive(uint16_t address, uint16_t subAddress, uint16_t wordCount, uint16_t* dataWords) const;
	/* Method for exchange messages in format F1
    * - messages format for transmit data-word from controller to terminal-device */
	int32_t transmitCmdF1(uint16_t address, uint16_t subAddress, uint16_t wordCount, uint16_t *dataWords);

    /* noncopyable class */
public:
    ControllerMode(const ControllerMode&) = delete;
    ControllerMode(ControllerMode&&) = delete;
    ControllerMode& operator=(const ControllerMode&) = delete;
    ControllerMode& operator=(ControllerMode&&) = delete;
private:
//	const TestMmko& testMmko; // instance of class TestMmko
	std::unique_ptr<TestMmko> testMmko;
	std::unique_ptr<unmmko1_command> commands;
	uint16_t mRxTx{}; // TODO data transmit/receive bit, needed will know how this use
	int bcOptions; // for function bc_configure, 0 by default
	/* Getters and Setters */
	void setRxTx(uint16_t RxTx);
	[[nodiscard]] uint16_t getRxTx() const;
	void setBcOptions(int bcOptions_);
	[[nodiscard]] int getBcOptions() const;
};








