#pragma once

#include <memory>

#include "MainBus.h"

class IDevice {
public:
	virtual ~IDevice() = default;
	virtual MainBus* CreateMKOBus() = 0;
};