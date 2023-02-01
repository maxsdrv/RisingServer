#pragma once

/* Class for work in Bus-Controller mode */

#include <functional>
#include <memory>
#include <map>

#include "enums.h"
#include "unmmko1.h"

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
	/* Methods for transmit message from controller to terminal-device */
	int32_t transmit();
	int32_t transmit_cmd_f1(uint16_t address, uint16_t sub_address, uint16_t word_count, uint16_t* data_words);
	int32_t transmit_data_cycle(uint16_t address, uint16_t sub_address, uint16_t word_count,
			uint16_t* data_words, uint16_t repeat_count);
	int32_t transmit_exist_cwd(uint16_t formed_cwd, uint16_t word_count, const uint16_t* data_words);
	void start_controller() const;
	void stop_controller() const;
	/* noncopyable class */
	ControllerMode(const ControllerMode&) = delete;
	ControllerMode(ControllerMode&&) = delete;
	ControllerMode& operator=(const ControllerMode&) = delete;
	ControllerMode& operator=(ControllerMode&&) = delete;

private:
	/* uint16_t mRxTx;  data receive/transmit bit. It must point to action which perform terminal-device
	if 0 that means what Terminal-Device should accept Data-Word(Cmd), if 1 then transmit*/
	BUSLINE bus_line;
	uint32_t controller_session;
	int32_t controller_status;
	uint16_t last_cwd;
	uint16_t last_response_cwd;
	std::map<CONTROL_COMMANDS, std::pair<bool, bool>> ctrl_commands;
};

class ItrControlCommand {
public:
	explicit ItrControlCommand(CONTROL_COMMANDS command) : position(command) {}
	ItrControlCommand& operator++() {
		position = static_cast<CONTROL_COMMANDS>(static_cast<int>(position)+1);
		return *this;
	}
	CONTROL_COMMANDS operator*() const {
		return position;
	}
	bool operator!=(const ItrControlCommand& other) const {
		return position != other.position;
	}
	bool operator==(const ItrControlCommand& other) const {
		return !(*this != other);
	}
private:
	CONTROL_COMMANDS position;
};


class RangeControlCommand {
public:
	RangeControlCommand(CONTROL_COMMANDS from, CONTROL_COMMANDS to) : b(from), e(to) {}
	[[nodiscard]] ItrControlCommand begin() const { return  ItrControlCommand {b}; }
	[[nodiscard]] ItrControlCommand end() const { return ItrControlCommand {e}; }
private:
	CONTROL_COMMANDS b;
	CONTROL_COMMANDS e;
};




