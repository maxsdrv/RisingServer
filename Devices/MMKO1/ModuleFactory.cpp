#include <iostream>
#include <memory>
#include "ModuleFactory.h"

std::unique_ptr<MainBus> ModuleFactory::CreateMKOBus(BUSLINE line)
{
	return std::make_unique<MainBus>(line);
}
