#pragma once

/* Class for work in Bus-Controller mode */

#include <functional>

#include "TestMmko.h"

class ControllerMode
{
private:
	friend class TestMmko;
	explicit ControllerMode(TestMmko* objectMmko1, const uint16_t& rxtx, int bcoptions);

public:
	~ControllerMode();
	/* Create command word
     * method creates 16-bit command word from fields
	 * address - address terminal device
	 * rx_tx - Reception/transmission bit(reception - 0, transmission - 1
	 * subaddress - subaddress/manage mode
	 * word_count - count of words/manage command code
	 * */
	static uint16_t PackCw(uint16_t address, uint16_t RxTx, uint16_t subAddress, uint16_t wordCount);
	/* Method for transmit message from bus-controller to terminal-device with one cmd word*/
	int32_t BusToTerminalReceive(uint16_t address, uint16_t subAddress, uint16_t wordCount, uint16_t* dataWords) const;
	/* Method for transmit message from controller to terminal-device in format F1 */
	int32_t transmitCmdF1(uint16_t address, uint16_t subAddress, uint16_t wordCount, uint16_t* dataWords);

	/* noncopyable class */
	ControllerMode(const ControllerMode&) = delete;
	ControllerMode(ControllerMode&&) = delete;
	ControllerMode& operator=(const ControllerMode&) = delete;
	ControllerMode& operator=(ControllerMode&&) = delete;

	/* Getters and Setters */
	void setRxTx(uint16_t RxTx);
	[[nodiscard]] uint16_t getRxTx() const;
	void setBcOptions(int bcOptions_);
	[[nodiscard]] int getBcOptions() const;

private:
	TestMmko* testMmko;
	std::unique_ptr<unmmko1_command> commands;
	uint16_t mRxTx; // TODO data transmit/receive bit, necessary will know how this use form 41 department
	int bcOptions; // for function bc_configure, 0 by default, TODO what is it from 41 department
};








