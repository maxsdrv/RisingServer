#pragma once

#include <functional>

#include "TestMmko.h"
#include "Actions.h"

class ControllerMode : public TestMmko {
public:
	ControllerMode() = default;
	explicit ControllerMode(unmmko1_bus bus);
	~ControllerMode() override { /*MKOTEXT("~ControllerMode()");*/ }
	/* *Template methods for send singly message* */
	template <class T>
	constexpr auto BaseTransmitCmd(T address, T subAddr, T wordCount);
    /* noncopyable class */
public:
    ControllerMode(const ControllerMode&) = delete;
    ControllerMode(ControllerMode&&) = delete;
    ControllerMode& operator=(const ControllerMode&) = delete;
    ControllerMode& operator=(ControllerMode&&) = delete;
private:
};

template<class T>
constexpr auto ControllerMode::BaseTransmitCmd(T address, T subAddr, T wordCount)
{
	std::cerr << "BaseTransmitCmd\n";
	auto cwd = TestMmko::PackCw(address, subAddr, wordCount, 0);
	*commands = unmmko1_bc_rt(static_cast<unmmko1_bus>(commands->activity), cwd, nullptr);
	checkProcess(unmmko1_bc_configure(common->session, UNMMKO1_BC_DEFAULT));
	checkProcess(unmmko1_bc_start(common->session));
	checkProcess(unmmko1_bc_transmit_command(common->session, *commands));

	return common->status;
}






