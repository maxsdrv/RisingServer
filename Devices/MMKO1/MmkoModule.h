#pragma once

class IDevice;
class MainBus;

class MKOModule {
public:
	MKOModule();
private:
	IDevice* device;
	MainBus* bus;
};
