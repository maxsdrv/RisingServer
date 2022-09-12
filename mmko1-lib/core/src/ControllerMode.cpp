#include "ControllerMode.h"

namespace {
	const int sizeBcOptions = 3;
}

/*ControllerMode::ControllerMode(const TestMmko& objectMmko1) :
		 testMmko(objectMmko1),
		 mRxTx(0),
		 commands(std::make_unique<unmmko1_command>()),
		 bcOptions(0)
{
	MKOTEXT("ControllerMode()");
}*/
ControllerMode::ControllerMode(TestMmko* objectMmko1) :
		 testMmko(objectMmko1),
		 mRxTx(0),
		 commands(std::make_unique<unmmko1_command>()),
		 bcOptions(0)
{
	MKOTEXT("ControllerMode()");
}
/*ControllerMode::~ControllerMode()
{
	MKOTEXT("~ControllerMode()");
}*/

uint16_t ControllerMode::PackCw(uint16_t address, uint16_t RxTx, uint16_t subAddress, uint16_t wordCount)
{
	return unmmko1_pack_cw(address, RxTx, subAddress, wordCount);
}

int32_t ControllerMode::BusToTerminalReceive(uint16_t address, uint16_t subAddress, uint16_t wordCount, uint16_t* dataWords) const
{
//	auto line = testMmko.getLine();
	auto line = testMmko->getLine();
	if (bcOptions < 0 || bcOptions > sizeBcOptions)
		throw MkoErrors("BAD::ARGUMENTS::BC_OPTIONS");

	auto commandWord = PackCw(address, mRxTx, subAddress, wordCount);
	*commands = unmmko1_bc_rt(line, commandWord, dataWords);
	unmmko1_bc_configure(TestMmko::getSession(), bcOptions);
	unmmko1_bc_start(TestMmko::getSession());
	unmmko1_bc_transmit_command(TestMmko::getSession(), *commands);
	unmmko1_bc_stop(TestMmko::getSession());

	return TestMmko::getStatus();
}
int32_t ControllerMode::transmitCmdF1( uint16_t address, uint16_t subAddress, uint16_t wordCount,
		uint16_t* dataWords)
{
	auto line = testMmko->getLine();

	if (bcOptions < 0 || bcOptions > sizeBcOptions)
		throw MkoErrors("BAD::ARGUMENTS::BC_OPTIONS");

	*commands = unmmko1_f1(line, address, subAddress, wordCount, dataWords);
	unmmko1_bc_configure(TestMmko::getSession(), bcOptions);
	unmmko1_bc_start(TestMmko::getSession());
	unmmko1_bc_transmit_command(TestMmko::getSession(), *commands);
	unmmko1_bc_stop(TestMmko::getSession());

	return TestMmko::getStatus();
}
void ControllerMode::setRxTx(uint16_t RxTx)
{
	mRxTx = RxTx;
}
uint16_t ControllerMode::getRxTx() const
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


