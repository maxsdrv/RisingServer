#pragma once

/* Class Singleton of Logging for common.h and lib unmmko */

#include <fstream>
#include <iostream>


class SFileLogger {
public:
	std::ofstream logOut;

	static SFileLogger& getInstance() {
		static SFileLogger theInstance;
		return theInstance;
	}

	void openLogFile(const std::string& fn);
	void closeLogFile();
	void writeToLog(int32_t status, const std::string& msg);

private:
	SFileLogger() = default;
	~SFileLogger() = default;
	SFileLogger(const SFileLogger&) = delete;
	SFileLogger& operator=(const SFileLogger&) = delete;
	SFileLogger(SFileLogger&&) = delete;
	SFileLogger& operator=(SFileLogger&&) = delete;
};

