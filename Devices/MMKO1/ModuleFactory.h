#pragma once

#include "IDevice.h"

class ModuleFactory : public IDevice {
public:
	MainBus* CreateMKOBus() override;
};