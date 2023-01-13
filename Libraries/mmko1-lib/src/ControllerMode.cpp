#include <iomanip>

#include "ControllerMode.h"
#include "MMKOErrors.h"
#include "MainBus.h"

ControllerMode::ControllerMode(MainBus* object_mmko, BUSLINE mko_line)
		:
		bus_line(mko_line),
		controller_session(object_mmko->get_mko_session())
{
	try {
		controller_status = MkoExceptions::check_functions("Controller configure",
				controller_session, unmmko1_bc_configure, controller_session, UNMMKO1_BC_DEFAULT);
	}
	catch(const MkoExceptions& ex) {
		std::cerr << ex.what();
	}
	std::cout << "ControllerMode()" << '\n';
}
ControllerMode::~ControllerMode()
{
	std::cout << "~ControllerMode()" << '\n';
}

uint16_t ControllerMode::pack_cw(uint16_t address, uint16_t rxtx, uint16_t sub_address, uint16_t word_count)
{
	return unmmko1_pack_cw(address, rxtx, sub_address, word_count);
}

int32_t ControllerMode::bus_to_terminal_transmit(uint16_t address, uint16_t sub_address, uint16_t word_count,
		uint16_t* data_words, RXTX type)
{
	auto commandWord = pack_cw(address, static_cast<uint16_t>(type), sub_address, word_count);
	*commands = unmmko1_bc_rt(static_cast<unmmko1_bus>(bus_line), commandWord, data_words);
	return unmmko1_bc_transmit_command(controller_session, *commands);
}
int32_t ControllerMode::transmitCmdF1(uint16_t address, uint16_t sub_address, uint16_t word_count,
		uint16_t* data_words)
{
	*commands = unmmko1_f1(static_cast<unmmko1_bus>(bus_line), address, sub_address, word_count, data_words);
	return unmmko1_bc_transmit_command(controller_session, *commands);
}

void ControllerMode::start_controller() const {
	MkoExceptions::check_functions
		("start_controller", controller_session, unmmko1_bc_start(controller_session));

	std::cout << boost::format("Controller started %i") %controller_session << '\n';
}
void ControllerMode::stop_controller() const {
	MkoExceptions::check_functions
		("stop controller", controller_session, unmmko1_bc_stop(controller_session));
	std::cout << "Controller stopped" << '\n';
}








