#pragma once

/* Class for work in Monitor-mode */
#include <vector>

#include "defines.h"
#include <unmmko1.h>

class MMKOInterface;
using Msg = std::vector<std::unique_ptr<unmmko1_message>>;

class MonitorMode {
private:
	friend class MMKOInterface;

	explicit MonitorMode(MMKOInterface* objMko);

public:
	~MonitorMode() = default;
	/* non-copyable class */
	MonitorMode(const MonitorMode&) = delete;
	MonitorMode(MonitorMode&&) = delete;
	MonitorMode& operator=(const MonitorMode&) = delete;
	MonitorMode& operator=(MonitorMode&&) = delete;

	void StartMonitor() const;
	void StopMonitor() const;
	/* Methods for processing messages */
	const Msg& PullMessage();
private:
	MMKOInterface* mMko;
	Msg messages; // Monitor messages list
	uint32 monitorSession;
	int32 monitorStatus;

	bool MessagesRead(); //read all messages
};

