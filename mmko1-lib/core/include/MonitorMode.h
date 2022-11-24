#pragma once

/* Class for work in Monitor-mode */
#include <vector>
#include <memory>

#include <unmmko1.h>

class Mmko;
using Msg = std::vector<std::unique_ptr<unmmko1_message>>;

class MonitorMode {
private:
	friend class Mmko;

	explicit MonitorMode(Mmko* objMko);

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
	Mmko* mMko;
	Msg messages; // Monitor messages list
	uint32_t monitorSession;
	int32_t monitorStatus;

	bool MessagesRead(); //read all messages
};

