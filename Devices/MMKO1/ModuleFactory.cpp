#include <iostream>
#include <memory>
#include "ModuleFactory.h"

std::unique_ptr<MainBus> ModuleFactory::CreateMKOBus()
{
	return std::make_unique<MainBus>();
}
