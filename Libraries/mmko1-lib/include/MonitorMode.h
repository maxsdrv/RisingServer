#pragma once

/* Class for work in Monitor-mode */
#include <memory>
#include <vector>
#include "unmmko1.h"

class MainBus;
using Msg = std::vector<std::unique_ptr<unmmko1_message>>;

class MonitorMode {
private:
	friend class MainBus;
	explicit MonitorMode(MainBus* objectMmko, int monOptions);
public:
	~MonitorMode();
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
	MainBus* m_objectMko;
	Msg messages; // Monitor messages list
	uint32_t monitorSession;
	int32_t monitorStatus;
	int m_monOptions {};

	bool MessagesRead(); //read all messages
};
