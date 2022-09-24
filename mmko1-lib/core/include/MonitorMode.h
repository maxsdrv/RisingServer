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
 /* class which store message values */
	struct MonitorMessage
	{
		uint64_t timestamp;
		uint16_t commandWord1;
		uint16_t commandWord2;
		uint16_t dataWordsCount;
		std::vector<uint16_t> dataWords;
	};
using Msg = std::vector<std::unique_ptr<unmmko1_message>>;
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
	MonitorMessage& PullMessage();
private:
	TestMmko* mMko;
	MonitorMessage monMessage{};
	Msg messages; // Monitor messages list
	uint32 monitorSession;
	int32 monitorStatus;

	bool MessagesRead(); //read all messages
};

