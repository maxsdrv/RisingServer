#pragma once

#include <memory>

#include "MainBus.h"

class IDevice {
public:
	IDevice() { std::cout << "IDevice()" << '\n'; }
	virtual ~IDevice() { std::cout << "~IDevice()" << '\n'; }
	virtual MainBus* CreateMKOBus(BUSLINE line) = 0;
};