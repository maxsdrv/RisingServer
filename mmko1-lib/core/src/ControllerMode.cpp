#include "ControllerMode.h"

ControllerMode::ControllerMode(Mmko* objectMmko1, int bcOptions)
		:
		mMmko(objectMmko1),
		commands(std::make_unique<unmmko1_command>())
{
	busLine = mMmko->getLine();
	currentSession = Mmko::getMkoSession();
	auto erMsg = unmmko1_bc_configure(currentSession, bcOptions);
	if (erMsg < 0) {

	}
	MkoText("ControllerMode()");
}
ControllerMode::~ControllerMode()
{
	MkoText("~ControllerMode()");
}

uint16_t ControllerMode::PackCw(uint16_t address, uint16_t RxTx, uint16_t subAddress, uint16_t wordCount)
{
	return unmmko1_pack_cw(address, RxTx, subAddress, wordCount);
}

int32_t ControllerMode::BusToTerminalTransmit(uint16_t address, uint16_t subAddress, uint16_t wordCount, uint16_t* dataWords) const
{
	auto commandWord = PackCw(address, mRxTx, subAddress, wordCount);
	*commands = unmmko1_bc_rt(busLine, commandWord, dataWords);
	unmmko1_bc_configure(currentSession, UNMMKO1_BC_DEFAULT);
	unmmko1_bc_start(currentSession);
	unmmko1_bc_transmit_command(currentSession, *commands);
	unmmko1_bc_stop(currentSession);

	return Mmko::getStatus();
}
int32_t ControllerMode::transmitCmdF1(uint16_t address, uint16_t subAddress, uint16_t wordCount,
		uint16_t* dataWords)
{
	*commands = unmmko1_f1(busLine, address, subAddress, wordCount, dataWords);
	unmmko1_bc_configure(currentSession, UNMMKO1_BC_DEFAULT);
	unmmko1_bc_start(currentSession);
	unmmko1_bc_transmit_command(currentSession, *commands);
	unmmko1_bc_stop(currentSession);

	return Mmko::getStatus();
}




