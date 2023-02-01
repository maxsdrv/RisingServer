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

	/* filling map with control of commands */
	RangeControlCommand range_control1 {(CONTROL_COMMANDS::CTR_INTERFACE),
						 (CONTROL_COMMANDS::TRANSMIT_VECTOR_WORD)};
	for (auto i = std::begin(range_control1); i!=std::end(range_control1); ++i) {
		ctrl_commands[*i] = std::make_pair(true, false);
	}
	RangeControlCommand range_control2 {(CONTROL_COMMANDS::TRANSMIT_VECTOR_WORD),
										(CONTROL_COMMANDS::END)};
	for (auto i = std::begin(range_control2); i != std::end(range_control2); ++i) {
		ctrl_commands[*i] = std::make_pair(true, true);
	}
	ctrl_commands[CONTROL_COMMANDS::SYNC_DATA_WORD].first = false;
	ctrl_commands[CONTROL_COMMANDS::BLOCK_Ith_TR].first = false;
	ctrl_commands[CONTROL_COMMANDS::UNBLOCK_Ith_TR].first = false;

	std::cout << "ControllerMode()" << '\n';
}
ControllerMode::~ControllerMode()
{
	std::cout << "~ControllerMode()" << '\n';
}
uint16_t ControllerMode::pack_cw(uint16_t address, uint16_t rxtx, uint16_t sub_address, uint16_t word_count) {
	return unmmko1_pack_cw(address, rxtx, sub_address, word_count);
}
int32_t ControllerMode::transmit_cmd_f1(uint16_t address, uint16_t sub_address, uint16_t word_count,
		uint16_t* data_words)
{
	auto commands = unmmko1_f1(static_cast<unmmko1_bus>(bus_line), address, sub_address, word_count, data_words);
	return unmmko1_bc_transmit_command(controller_session, commands);
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
int32_t ControllerMode::transmit_data_cycle(uint16_t address, uint16_t sub_address, uint16_t word_count,
		uint16_t* data_words, uint16_t repeat_count) {
	auto word_ = pack_cw(address, static_cast<uint16_t>(RXTX::RECEIVE), sub_address, word_count);
	auto cwd = unmmko1_bc_rt(static_cast<unmmko1_bus>(bus_line), word_, data_words);
	unmmko1_bc_set_schedule_repeat_count(controller_session, repeat_count);

	return unmmko1_bc_schedule_command(controller_session, cwd);
}
int32_t ControllerMode::transmit_exist_cwd(uint16_t formed_cwd, uint16_t word_count, const uint16_t* data_words) {
	if (data_words == nullptr) {
		throw std::invalid_argument("Buffer for receive/transmit not specify");
	}
	uint16_t address;
	uint16_t sub_addr;
	uint16_t rx_tx;
	unmmko1_unpack_cw(formed_cwd, &address, &rx_tx, &sub_addr, &word_count);

	return 0;
}








