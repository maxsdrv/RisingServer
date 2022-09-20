#include "ControllerMode.h"
#include "defines.h"

namespace
{
	const int sizeBcOptions = 3;
}

ControllerMode::ControllerMode(TestMmko* objectMmko1, const uint16& rxtx, int bcoptions)
		:
		testMmko(objectMmko1),
		mRxTx(rxtx),
		commands(std::make_unique<unmmko1_command>()),
		bcOptions(bcoptions)
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
	if (bcOptions < 0 || bcOptions > sizeBcOptions)
		assert(bcOptions > 0 && bcOptions < sizeBcOptions);

	auto commandWord = PackCw(address, mRxTx, subAddress, wordCount);
	*commands = unmmko1_bc_rt(line, commandWord, dataWords);
	unmmko1_bc_configure(TestMmko::getMkoSession(), bcOptions);
	unmmko1_bc_start(TestMmko::getMkoSession());
	unmmko1_bc_transmit_command(TestMmko::getMkoSession(), *commands);
	unmmko1_bc_stop(TestMmko::getMkoSession());

	return TestMmko::getStatus();
}
int32 ControllerMode::transmitCmdF1(uint16 address, uint16 subAddress, uint16 wordCount,
		uint16* dataWords)
{
	auto line = testMmko->getLine();
	if (bcOptions < 0 || bcOptions > sizeBcOptions)
		assert(bcOptions > 0 && bcOptions < sizeBcOptions);

	*commands = unmmko1_f1(line, address, subAddress, wordCount, dataWords);
	unmmko1_bc_configure(TestMmko::getMkoSession(), bcOptions);
	unmmko1_bc_start(TestMmko::getMkoSession());
	unmmko1_bc_transmit_command(TestMmko::getMkoSession(), *commands);
	unmmko1_bc_stop(TestMmko::getMkoSession());

	return TestMmko::getStatus();
}
void ControllerMode::setRxTx(uint16 RxTx)
{
	mRxTx = RxTx;
}
uint16 ControllerMode::getRxTx() const
{
	return mRxTx;
}
void ControllerMode::setBcOptions(int bcOptions_)
{
	bcOptions = bcOptions_;
}
int ControllerMode::getBcOptions() const
{
	return bcOptions;
}


