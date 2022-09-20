#pragma once

/* Class for work in Monitor-mode */
#include <vector>

#include "defines.h"
#include <unmmko1.h>

class TestMmko;

class MonitorMode {
private:
	friend class TestMmko;
	explicit MonitorMode(TestMmko* objMko);
	using Msg = std::vector<std::unique_ptr<unmmko1_message>>;
public:
	~MonitorMode() = default;
	/* non-copyable class */
	MonitorMode(const MonitorMode&) = delete;
	MonitorMode(MonitorMode&&) = delete;
	MonitorMode& operator=(const MonitorMode&) = delete;
	MonitorMode& operator=(MonitorMode&&) = delete;
	/* Methods for processing messages */
	void StartMonitor();
	void StopMonitor() const;
	void MessagesRead();
	void ViewMessage();
private:
	TestMmko* mMko;
	Msg messages; // Monitor messages list
	uint32 monitorSession;
	int32 monitorStatus;
};

