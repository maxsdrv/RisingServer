#pragma once

#include "IDevice.h"

class ModuleFactory : public IDevice {
public:
	ModuleFactory() { std::cout << "ModuleFactory()" << '\n'; }
	~ModuleFactory() override { std::cout << "~ModuleFactory()" << '\n'; }
	std::unique_ptr<MainBus> CreateMKOBus() override;
};