#include "ControllerMode.h"
#include "defines.h"

ControllerMode::ControllerMode(MMKOInterface* objectMmko1, const uint16& rxtx)
		:
		testMmko(objectMmko1),
		mRxTx(rxtx),
		commands(std::make_unique<unmmko1_command>())
{
	MkoText("ControllerMode()");
}
ControllerMode::~ControllerMode()
{
	MkoText("~ControllerMode()");
}

uint16 ControllerMode::PackCw(uint16 address, uint16 RxTx, uint16 subAddress, uint16 wordCount)
{
	return unmmko1_pack_cw(address, RxTx, subAddress, wordCount);
}

int32 ControllerMode::BusToTerminalReceive(uint16 address, uint16 subAddress, uint16 wordCount, uint16* dataWords) const
{
	auto line = static_cast<unmmko1_bus>(testMmko->getLine());

	auto commandWord = PackCw(address, mRxTx, subAddress, wordCount);
	*commands = unmmko1_bc_rt(line, commandWord, dataWords);
	unmmko1_bc_configure(MMKOInterface::getMkoSession(), UNMMKO1_BC_DEFAULT);
	unmmko1_bc_start(MMKOInterface::getMkoSession());
	unmmko1_bc_transmit_command(MMKOInterface::getMkoSession(), *commands);
	unmmko1_bc_stop(MMKOInterface::getMkoSession());

	return MMKOInterface::getStatus();
}
int32 ControllerMode::transmitCmdF1(uint16 address, uint16 subAddress, uint16 wordCount,
		uint16* dataWords)
{
	auto line = testMmko->getLine();

	*commands = unmmko1_f1(line, address, subAddress, wordCount, dataWords);
	unmmko1_bc_configure(MMKOInterface::getMkoSession(), UNMMKO1_BC_DEFAULT);
	unmmko1_bc_start(MMKOInterface::getMkoSession());
	unmmko1_bc_transmit_command(MMKOInterface::getMkoSession(), *commands);
	unmmko1_bc_stop(MMKOInterface::getMkoSession());

	return MMKOInterface::getStatus();
}
void ControllerMode::setRxTx(uint16 RxTx)
{
	mRxTx = RxTx;
}
uint16 ControllerMode::getRxTx() const
{
	return mRxTx;
}



