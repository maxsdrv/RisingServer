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
	explicit MonitorMode(MainBus* object_mmko);
public:
	~MonitorMode();
	/* non-copyable class */
	MonitorMode(const MonitorMode&) = delete;
	MonitorMode(MonitorMode&&) = delete;
	MonitorMode& operator=(const MonitorMode&) = delete;
	MonitorMode& operator=(MonitorMode&&) = delete;

	void start_monitor() const;
	void stop_monitor() const;
	/* Methods for processing messages */
	const Msg& pull_message();
private:
	Msg messages; // Monitor messages list
	uint32_t monitor_session;
	int32_t monitor_status;
	bool messages_read(); //read all messages
};
