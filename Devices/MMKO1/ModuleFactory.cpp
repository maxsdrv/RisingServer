#include <iostream>
#include <memory>
#include "ModuleFactory.h"

MainBus* ModuleFactory::CreateMKOBus(BUSLINE line)
{
	return new MainBus(line);
}
