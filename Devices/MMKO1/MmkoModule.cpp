#include <iostream>

#include "MmkoModule.h"
#include "ControllerMode.h"
#include "MMKOErrors.h"
#include "IDevice.h"


namespace {
	std::unique_ptr<IDevice> deviceInstance = std::make_unique<ModuleFactory>();
}

MKOModule::MKOModule()
{
	mainbus = deviceInstance->CreateMKOBus(); // Create MainBus object

	f4Commands["ИСХ"] 			= CONTROL_COMMANDS::RESET_TR_DEVICE;
	f4Commands["БЛКПРД"]		= CONTROL_COMMANDS::BLOCK_TRANSMITTER;
	f4Commands["РБЛКПРД"] 		= CONTROL_COMMANDS::UNBLOCK_TRANSMITTER;
	f4Commands["ПОС"] 			= CONTROL_COMMANDS::TR_RESPONSE_WORD;
	f4Commands["СИНХР"]			= CONTROL_COMMANDS::SYNC;
	f4Commands["ПРИНУПРИНТ"]	= CONTROL_COMMANDS::CTR_INTERFACE;
	f4Commands["НАЧСАМОКОНТР"]	= CONTROL_COMMANDS::START_SELF_TEST;
	f4Commands["ВЕКТОР"]		= CONTROL_COMMANDS::TR_VECTOR_WORD;
	f4Commands["ПОСЛЕДКОМ"]		= CONTROL_COMMANDS::TR_LAST_CMD;
	f4Commands["ВСК"]			= CONTROL_COMMANDS::TR_VSK_WORD;

	auto insertIt (std::end(mkoAddresses));
	for (const auto& mA : {1, 2, 3, 4, 5, 6, 7, 9, 12, 13, 18, 19, 20, 21}) {
		insertIt = mkoAddresses.insert(insertIt, {mA, static_cast<int>(BUSLINE::MKO_BUS_B)});
	}
	for (const auto& mA : {10, 11, 23, 24, 14, 15, 16, 17, 27, 22}) {
		insertIt = mkoAddresses.insert(insertIt, {mA, static_cast<int>(BUSLINE::MKO_BUS_A)});
	}
	selectedBus = BUSLINE::MKO_BUS_B;
	/*try {
		AddController(BUSLINE::MKO_BUS_A);
		AddController(BUSLINE::MKO_BUS_B);
	}
	catch(const MkoExceptions& ex) {
		std::cerr << ex.what();
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what();
	}*/

	std::cout << "MKOModule()" << '\n';
}
MKOModule::~MKOModule()
{
	std::cout << "~MKOModule()" << '\n';
}
void MKOModule::AddController(BUSLINE line) const
{
	auto ctrl = mainbus->CreateController(line);
	mainbus->resetState ?
	throw std::runtime_error("ERROR::ADDING::CONTROLLER::MOD\n") :
	ctrl->StartController();
}
bool MKOModule::SelfTest()
{
	bool testResult;
	try {
		testResult = mainbus->SelfTest();
	}catch (const MkoExceptions& ex) {
		std::cerr << ex.what();
	}
	return testResult;
}
bool MKOModule::WriteToAbonent()
{

	return false;
}
bool MKOModule::WriteToAbonentCycle()
{
	return false;
}
bool MKOModule::ReadFromAbonent()
{
	return false;
}
