#pragma once

#include <iostream>

#include "ModuleFactory.h"

class IDevice;

class MKOModule {
public:
	explicit MKOModule(BUSLINE line);
	~MKOModule();
private:
	IDevice* device;
	MainBus* bus;
};
