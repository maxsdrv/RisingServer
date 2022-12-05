#include <iostream>

#include "MmkoModule.h"

MKOModule::MKOModule(BUSLINE line)
{
	device = new ModuleFactory;
	bus = device->CreateMKOBus(line);
	std::cout << "MKOModule()" << '\n';
}
MKOModule::~MKOModule()
{
	delete device;
	delete bus;
	std::cout << "~MKOModule()" << '\n';
}