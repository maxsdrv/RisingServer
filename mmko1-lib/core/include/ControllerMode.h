#pragma once

/* Class for work in Bus-Controller mode */

#include <functional>

#include "Mmko.h"

class ControllerMode
{
private:
	friend class Mmko;
	explicit ControllerMode(Mmko* objectMmko1, int bcOptions = UNMMKO1_BC_DEFAULT);

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
	int32_t BusToTerminalTransmit(uint16_t address, uint16_t subAddress, uint16_t wordCount, uint16_t* dataWords) const;
	/* Method for transmit message from controller to terminal-device in format F1 */
	int32_t transmitCmdF1(uint16_t address, uint16_t subAddress, uint16_t wordCount, uint16_t* dataWords);

	/* noncopyable class */
	ControllerMode(const ControllerMode&) = delete;
	ControllerMode(ControllerMode&&) = delete;
	ControllerMode& operator=(const ControllerMode&) = delete;
	ControllerMode& operator=(ControllerMode&&) = delete;

private:
	Mmko* mMmko;
	std::unique_ptr<unmmko1_command> commands;
	uint16_t mRxTx; /* data receive/transmit bit. It must point to action which perform terminal-device
	if 0 that means what Terminal-Device should accept Data-Word(Cmd), if 1 then transmit*/
	BUSLINE busLine;
	uint32_t currentSession;
};








