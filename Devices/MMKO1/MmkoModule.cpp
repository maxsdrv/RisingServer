#include <iostream>

#include "MmkoModule.h"
#include "ControllerMode.h"
#include "AbonentMode.h"
#include "MonitorMode.h"
#include "MMKOErrors.h"

namespace {
	std::unique_ptr<IDevice> device_instance = std::make_unique<ModuleFactory>();
}

MKOModule::MKOModule()
{
	mainbus = device_instance->create_mko_bus(); // Create MainBus object

	f4_commands["ИСХ"] 			= CONTROL_COMMANDS::RESET_DEVICE_TRANSMIT;
	f4_commands["БЛКПРД"]		= CONTROL_COMMANDS::BLOCK_TRANSMITTER;
	f4_commands["РБЛКПРД"] 		= CONTROL_COMMANDS::UNBLOCK_TRANSMITTER;
	f4_commands["ПОС"] 			= CONTROL_COMMANDS::TRANSMIT_RESPONSE_WORD;
	f4_commands["СИНХР"]			= CONTROL_COMMANDS::SYNC;
	f4_commands["ПРИНУПРИНТ"]	= CONTROL_COMMANDS::CTR_INTERFACE;
	f4_commands["НАЧСАМОКОНТР"]	= CONTROL_COMMANDS::START_SELF_TEST;
	f4_commands["ВЕКТОР"]		= CONTROL_COMMANDS::TRANSMIT_VECTOR_WORD;
	f4_commands["ПОСЛЕДКОМ"]		= CONTROL_COMMANDS::TRANSMIT_LAST_CMD;
	f4_commands["ВСК"]			= CONTROL_COMMANDS::TRANSMIT_VSK_WORD;

	auto insert_it (std::end(mko_addresses));
	for (const auto& mA : {1, 2, 3, 4, 5, 6, 7, 9, 12, 13, 18, 19, 20, 21}) {
		insert_it = mko_addresses.insert(insert_it, { mA, static_cast<int>(BUSLINE::MKO_BUS_B)});
	}
	for (const auto& mA : {10, 11, 23, 24, 14, 15, 16, 17, 27, 22}) {
		insert_it = mko_addresses.insert(insert_it, { mA, static_cast<int>(BUSLINE::MKO_BUS_A)});
	}
	selected_bus = BUSLINE::MKO_BUS_B;
	try {
		add_controller(BUSLINE::MKO_BUS_B);
	}
	catch(const MkoExceptions& ex) {
		std::cerr << ex.what();
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what();
	}

	std::cout << "MKOModule()" << '\n';
}
MKOModule::~MKOModule()
{
	std::cout << "~MKOModule()" << '\n';
}
void MKOModule::add_controller(BUSLINE line) const
{
	try {
		mainbus->create_abonent(line, 1);
		auto ctrl = mainbus->create_controller(line);
		uint16_t word[10] {1, 2, 3, 4};
		ctrl->transmit_cmd_f1(RT_3, SA_2, 4, word);
		ctrl->transmit_data_cycle(RT_3, SA_2, 4, word, 10);
	}
	catch (const MkoExceptions& ex) {
		std::cerr << ex.what();
	}
}
bool MKOModule::self_test()
{
	bool test_result;
	try {
		test_result = mainbus->self_test();
	}catch (const MkoExceptions& ex) {
		std::cerr << ex.what();
	}
	return test_result;
}
bool MKOModule::write_to_abonent()
{

	return false;
}
bool MKOModule::write_to_abonent_cycle()
{
	return false;
}
bool MKOModule::read_from_abonent()
{
	return false;
}
