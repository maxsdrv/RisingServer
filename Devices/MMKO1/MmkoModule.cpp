#include <iostream>

#include "MmkoModule.h"
#include "ControllerMode.h"
#include "MMKOErrors.h"
#include "IDevice.h"


namespace {
	std::unique_ptr<IDevice> device_instance = std::make_unique<ModuleFactory>();
}

MKOModule::MKOModule()
{
	mainbus = device_instance->create_mko_bus(); // Create MainBus object

	f4_commands["ИСХ"] 			= CONTROL_COMMANDS::RESET_TR_DEVICE;
	f4_commands["БЛКПРД"]		= CONTROL_COMMANDS::BLOCK_TRANSMITTER;
	f4_commands["РБЛКПРД"] 		= CONTROL_COMMANDS::UNBLOCK_TRANSMITTER;
	f4_commands["ПОС"] 			= CONTROL_COMMANDS::TR_RESPONSE_WORD;
	f4_commands["СИНХР"]			= CONTROL_COMMANDS::SYNC;
	f4_commands["ПРИНУПРИНТ"]	= CONTROL_COMMANDS::CTR_INTERFACE;
	f4_commands["НАЧСАМОКОНТР"]	= CONTROL_COMMANDS::START_SELF_TEST;
	f4_commands["ВЕКТОР"]		= CONTROL_COMMANDS::TR_VECTOR_WORD;
	f4_commands["ПОСЛЕДКОМ"]		= CONTROL_COMMANDS::TR_LAST_CMD;
	f4_commands["ВСК"]			= CONTROL_COMMANDS::TR_VSK_WORD;

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
//	add_controller(BUSLINE::MKO_BUS_B);

	std::cout << "MKOModule()" << '\n';
}
MKOModule::~MKOModule()
{
	std::cout << "~MKOModule()" << '\n';
}
void MKOModule::add_controller(BUSLINE line) const
{
	auto ctrl = mainbus->create_controller(line);
	mainbus->reset_state ?
	throw std::runtime_error("ERROR::ADDING::CONTROLLER::MOD\n") :
	ctrl->start_controller();
//	auto abonent = mainbus->create_abonent(line, 0);

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
