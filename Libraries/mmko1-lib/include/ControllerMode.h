#pragma once

/* Class for work in Bus-Controller mode */

#include <functional>
#include <memory>

#include "enums.h"

extern "C" {
#include "unmmko1.h"
}

class MainBus;

class ControllerMode
{
private:
	friend class MainBus;
	explicit ControllerMode(MainBus* object_mmko, BUSLINE mko_line);

public:
	~ControllerMode();
	/* Create command word
     * method creates 16-bit command word from fields
	 * address - address terminal device
	 * rx_tx - Reception/transmission bit(reception - 0, transmission - 1
	 * subaddress - subaddress/manage mode
	 * word_count - count of words */
	static uint16_t pack_cw(uint16_t address, uint16_t rxtx, uint16_t sub_address, uint16_t word_count);
	/* Method for transmit message from bus-controller to terminal-device with one cmd word
	 * address - address terminal device
	 * subaddress - subaddress/manage mode
	 * type - rxtx Reception/Transmission bit(reception - 0, transmission - 1
	 * word_count - count of words
	 * data_words - pointer on array of data-words(array must not be empty) */
	int32_t bus_to_terminal_transmit(uint16_t address, uint16_t sub_address, uint16_t word_count,
			uint16_t* data_words, RXTX type = RXTX::RECEIVE);
	/* Method for transmit message from controller to terminal-device in format F1 */
	int32_t transmitCmdF1(uint16_t address, uint16_t sub_address, uint16_t word_count, uint16_t* data_words);
	void start_controller() const;
	void stop_controller() const;
	/* noncopyable class */
	ControllerMode(const ControllerMode&) = delete;
	ControllerMode(ControllerMode&&) = delete;
	ControllerMode& operator=(const ControllerMode&) = delete;
	ControllerMode& operator=(ControllerMode&&) = delete;

private:
	unmmko1_command* commands{};
	/* uint16_t mRxTx;  data receive/transmit bit. It must point to action which perform terminal-device
	if 0 that means what Terminal-Device should accept Data-Word(Cmd), if 1 then transmit*/
	BUSLINE bus_line;
	uint32_t controller_session{};
	int32_t controller_status{};
};








