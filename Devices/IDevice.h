#pragma once

#include <memory>

#include "MainBus.h"

class IDevice {
public:
	IDevice() { std::cout << "IDevice()" << '\n'; }
	virtual ~IDevice() { std::cout << "~IDevice()" << '\n'; }
	virtual std::unique_ptr<MainBus> create_mko_bus() = 0;
};