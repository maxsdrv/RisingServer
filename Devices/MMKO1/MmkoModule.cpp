#include <iostream>

#include "MmkoModule.h"
#include "ControllerMode.h"
#include "MMKOErrors.h"

namespace {
	std::unique_ptr<IDevice> device = std::make_unique<ModuleFactory>();
}

MKOModule::MKOModule(BUSLINE line)
{
	mainbus = device->CreateMKOBus(line);
	if (SelfTest()) {
		AddController(BUSLINE::MKO_BUS_A);
		AddController(BUSLINE::MKO_BUS_B);
	}
	std::cout << "MKOModule()" << '\n';
}
MKOModule::~MKOModule()
{
	std::cout << "~MKOModule()" << '\n';
}
void MKOModule::AddController(BUSLINE line) const
{
	try {
		mainbus->addController(mainbus.get(), line);
	}catch (const MkoExceptions& ex) {
		std::cerr << ex.what() << '\n';
	}
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
