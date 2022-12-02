#pragma once

/* Class for work in Bus-Controller mode */

#include <functional>

#include "MainBus.h"

enum class RXTX {
	RECEIVE,
	TRANSMIT
};

class ControllerMode
{
private:
	friend class MainBus;
	explicit ControllerMode(MainBus* objectMmko, int bcOptions = UNMMKO1_BC_DEFAULT);

public:
	~ControllerMode();
	/* Create command word
     * method creates 16-bit command word from fields
	 * address - address terminal device
	 * rx_tx - Reception/transmission bit(reception - 0, transmission - 1
	 * subaddress - subaddress/manage mode
	 * word_count - count of words */
	static uint16_t PackCw(uint16_t address, uint16_t rxtx, uint16_t subAddress, uint16_t wordCount);
	/* Method for transmit message from bus-controller to terminal-device with one cmd word
	 * address - address terminal device
	 * subaddress - subaddress/manage mode
	 * type - rxtx Reception/Transmission bit(reception - 0, transmission - 1
	 * wordCount - count of words
	 * dataWords - pointer on array of data-words(array must not be empty) */
	int32_t BusToTerminalTransmit(uint16_t address, uint16_t subAddress, uint16_t wordCount,
			uint16_t* dataWords, RXTX type = RXTX::RECEIVE);
	/* Method for transmit message from controller to terminal-device in format F1 */
	int32_t transmitCmdF1(uint16_t address, uint16_t subAddress, uint16_t wordCount, uint16_t* dataWords);
	void StartController() const;
	void StopController() const;

	/* noncopyable class */
	ControllerMode(const ControllerMode&) = delete;
	ControllerMode(ControllerMode&&) = delete;
	ControllerMode& operator=(const ControllerMode&) = delete;
	ControllerMode& operator=(ControllerMode&&) = delete;

private:
	MainBus* m_objectMmko;
	std::unique_ptr<unmmko1_command> commands;
	/* uint16_t mRxTx;  data receive/transmit bit. It must point to action which perform terminal-device
	if 0 that means what Terminal-Device should accept Data-Word(Cmd), if 1 then transmit*/
	BUSLINE busLine;
	uint32_t controllerSession;
	int32_t controllerStatus;
};








