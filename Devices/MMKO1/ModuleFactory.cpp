#include <iostream>
#include <memory>
#include "ModuleFactory.h"

std::unique_ptr<MainBus> ModuleFactory::create_mko_bus()
{
	return std::make_unique<MainBus>();
}
