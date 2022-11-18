#include "ControllerMode.h"
#include "defines.h"

ControllerMode::ControllerMode(Mmko* objectMmko1, const uint16_t& rxtx)
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

uint16_t ControllerMode::PackCw(uint16_t address, uint16_t RxTx, uint16_t subAddress, uint16_t wordCount)
{
	return unmmko1_pack_cw(address, RxTx, subAddress, wordCount);
}

int32_t ControllerMode::BusToTerminalReceive(uint16_t address, uint16_t subAddress, uint16_t wordCount, uint16_t* dataWords) const
{
	auto line = static_cast<unmmko1_bus>(testMmko->getLine());

	auto commandWord = PackCw(address, mRxTx, subAddress, wordCount);
	*commands = unmmko1_bc_rt(line, commandWord, dataWords);
	unmmko1_bc_configure(Mmko::getMkoSession(), UNMMKO1_BC_DEFAULT);
	unmmko1_bc_start(Mmko::getMkoSession());
	unmmko1_bc_transmit_command(Mmko::getMkoSession(), *commands);
	unmmko1_bc_stop(Mmko::getMkoSession());

	return Mmko::getStatus();
}
int32_t ControllerMode::transmitCmdF1(uint16_t address, uint16_t subAddress, uint16_t wordCount,
		uint16_t* dataWords)
{
	auto line = testMmko->getLine();

	*commands = unmmko1_f1(line, address, subAddress, wordCount, dataWords);
	unmmko1_bc_configure(Mmko::getMkoSession(), UNMMKO1_BC_DEFAULT);
	unmmko1_bc_start(Mmko::getMkoSession());
	unmmko1_bc_transmit_command(Mmko::getMkoSession(), *commands);
	unmmko1_bc_stop(Mmko::getMkoSession());

	return Mmko::getStatus();
}
void ControllerMode::setRxTx(uint16_t RxTx)
{
	mRxTx = RxTx;
}
uint16_t ControllerMode::getRxTx() const
{
	return mRxTx;
}



