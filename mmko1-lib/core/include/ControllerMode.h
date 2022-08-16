#pragma once

#include "TestMmko.h"

class ControllerMode : public TestMmko {
public:
	ControllerMode() = default;
	~ControllerMode() override { MKOTEXT("~ControllerMode()"); }

	bool TransmitCommand(const unmmko1_command& structCommand, unmmko1_bus bus, ViUInt16 command_word, std::vector<uint16_t> data_words);
};

