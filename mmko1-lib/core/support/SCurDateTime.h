#pragma once

#include <chrono>
#include <vector>
#include <numeric>
#include <ctime>
#include <string>
#include <cstring>

class SCurDateTime {
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1>>;
public:
	static SCurDateTime& getInstance() {
		static SCurDateTime theInstance;
		return theInstance;
	}

	std::string getCurDateTime();
	void start();
	void saveTime();

private:
	SCurDateTime() = default;
	~SCurDateTime() = default;
	SCurDateTime(const SCurDateTime&) = delete;
	SCurDateTime& operator=(const SCurDateTime&) = delete;
	SCurDateTime(SCurDateTime&&) = delete;
	SCurDateTime& operator=(SCurDateTime&&) = delete;

private:
	std::chrono::time_point<clock_t> m_beg;
	std::vector<double> storage_time;
};

