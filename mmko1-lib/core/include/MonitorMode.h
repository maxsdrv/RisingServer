#pragma once

/* Class for work in Monitor-mode */

class TestMmko;

class MonitorMode {
private:
	friend class TestMmko;
	MonitorMode() = default;
public:
	~MonitorMode() = default;
	/* non-copyable class */
	MonitorMode(const MonitorMode&) = delete;
	MonitorMode(MonitorMode&&) = delete;
	MonitorMode& operator=(const MonitorMode&) = delete;
	MonitorMode& operator=(MonitorMode&&) = delete;
private:
};

