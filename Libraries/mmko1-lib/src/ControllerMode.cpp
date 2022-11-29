#include "ControllerMode.h"

ControllerMode::ControllerMode(Mmko* objectMmko, int bcOptions)
		:
		m_objectMmko(objectMmko),
		commands(std::make_unique<unmmko1_command>()),
		busLine(objectMmko->getLineBus()),
		controllerSession(objectMmko->getMkoSession()),
		controllerStatus(objectMmko->getMkoStatus())
{
	ThrowErrorIf(unmmko1_bc_configure(controllerSession, bcOptions) < 0,
			controllerSession, controllerStatus, ErDevices::UNMMKO);
	StartController();
	MkoText("ControllerMode()");
}
ControllerMode::~ControllerMode()
{
	StopController();
	MkoText("~ControllerMode()");
}

uint16_t ControllerMode::PackCw(uint16_t address, uint16_t rxtx, uint16_t subAddress, uint16_t wordCount)
{
	return unmmko1_pack_cw(address, rxtx, subAddress, wordCount);
}

int32_t ControllerMode::BusToTerminalTransmit(uint16_t address, uint16_t subAddress, uint16_t wordCount,
		uint16_t* dataWords, RXTX type)
{
	auto commandWord = PackCw(address, static_cast<uint16_t>(type), subAddress, wordCount);
	*commands = unmmko1_bc_rt(busLine, commandWord, dataWords);
	return unmmko1_bc_transmit_command(controllerSession, *commands);
}
int32_t ControllerMode::transmitCmdF1(uint16_t address, uint16_t subAddress, uint16_t wordCount,
		uint16_t* dataWords)
{
	*commands = unmmko1_f1(busLine, address, subAddress, wordCount, dataWords);
	return unmmko1_bc_transmit_command(controllerSession, *commands);
}

void ControllerMode::StartController() const {
	unmmko1_bc_start(controllerSession);
}
void ControllerMode::StopController() const {
	unmmko1_bc_stop(controllerSession);
}







