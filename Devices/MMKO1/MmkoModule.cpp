#include <iostream>

#include "MmkoModule.h"
#include "ModuleFactory.h"

MKOModule::MKOModule()
{
	device = new ModuleFactory;
	bus = device->CreateMKOBus();
}
