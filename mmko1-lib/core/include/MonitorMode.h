#pragma once

/* Class for work in Monitor-mode */
#include "defines.h"
#include <unmmko1.h>

class TestMmko;

class MonitorMode {
private:
	friend class TestMmko;
	explicit MonitorMode(TestMmko* objMko);

	int32 StartMonitor();
public:
	~MonitorMode() = default;
	/* non-copyable class */
	MonitorMode(const MonitorMode&) = delete;
	MonitorMode(MonitorMode&&) = delete;
	MonitorMode& operator=(const MonitorMode&) = delete;
	MonitorMode& operator=(MonitorMode&&) = delete;
private:
	TestMmko* mMko;
	uint16 monSession;
};

