#include <iostream>
#include <memory>
#include "ModuleFactory.h"

MainBus* ModuleFactory::CreateMKOBus()
{
	return new MainBus(UNMMKO1_BUS_A);
}
