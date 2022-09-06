#pragma once

#include <functional>

#include "TestMmko.h"
#include "Actions.h"

class ControllerMode : public TestMmko {
public:
	ControllerMode() = default;
	explicit ControllerMode(unmmko1_bus bus);
	~ControllerMode() override { MKOTEXT("~ControllerMode()"); }

	/* Method for exchange data between bus-controller and terminal-device */
	int32_t baseTransmitCmd(uint16_t address, uint16_t subAddress, uint16_t wordCount, uint16_t* dataWords);
	/* Method for exchange messages in format F1
    * - messages format for transmit data-word from controller to terminal-device */
	int32_t transmitCmdF1(unmmko1_bus bus, uint16_t address, uint16_t subAddress, uint16_t wordCount, uint16_t *dataWords);
    /* noncopyable class */
public:
    ControllerMode(const ControllerMode&) = delete;
    ControllerMode(ControllerMode&&) = delete;
    ControllerMode& operator=(const ControllerMode&) = delete;
    ControllerMode& operator=(ControllerMode&&) = delete;
private:
	uint16_t mRxTx{}; // TODO data transmit/receive bit, needed will know how this use
	void setRxTx(uint16_t RxTx);
	uint16_t getRxTx() const;
};








