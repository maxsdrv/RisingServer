#pragma once

#include <vector>

#include "defines.h"

class ITestMmko {
public:
	ITestMmko() = default;
	virtual ~ITestMmko() { MKOTEXT("~ITestMmko()") }

/* methods for working Mezzanine MKO */
/* Base methods */
	virtual void Init() = 0; // Base initialisation Mezzanine MMKO
	virtual void SelfTest() = 0; // make test with Mezzanine
	virtual void Close() = 0; // close connect Mezzanine MKO and carrier Mezzanine
/* Methods for monitoring messages */
	virtual int32_t MonitorConfigure() = 0; // Work Mezzanine in Bus Monitor Mode
	virtual int32_t SendMessage(const std::vector<uint16_t>& words) = 0; // Sending individual messages
protected:
};

