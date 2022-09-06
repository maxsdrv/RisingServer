#include "ControllerMode.h"

ControllerMode::ControllerMode(unmmko1_bus bus) : mRxTx(0), TestMmko(bus) {}

int32_t ControllerMode::baseTransmitCmd(uint16_t address, uint16_t subAddress, uint16_t wordCount, uint16_t* dataWords)
{
	auto cwd = TestMmko::PackCw(address, mRxTx, subAddress, wordCount);
	if (!isInit()) {
		MKOTEXT("ERROR::INIT::PLEASE FIRST INIT AND SEARCH MKO");
		throw std::runtime_error("TEST::ERROR::INIT");
	}

//	*commands = unmmko1_bc_rt(static_cast<unmmko1_bus>(commands->activity), cwd, nullptr);
	checkProcess(unmmko1_bc_configure(common->session, UNMMKO1_BC_DEFAULT));
	checkProcess(unmmko1_bc_start(common->session));
	checkProcess(unmmko1_bc_transmit_command(common->session, *commands.back()));

	return common->status;
}
int32_t ControllerMode::transmitCmdF1(unmmko1_bus bus, uint16_t address, uint16_t subAddress, uint16_t wordCount,
		uint16_t* dataWords)
{
	return 0;
}
void ControllerMode::setRxTx(uint16_t RxTx)
{
	mRxTx = RxTx;
}
uint16_t ControllerMode::getRxTx() const
{
	return mRxTx;
}

