#pragma once

#include "defines.h"

class ITestMmko {
public:
	ITestMmko() = default;
	virtual ~ITestMmko() { MKOTEXT("~ITestMmko()") }

/* methods for working Mezzanine MKO */
/* Base methods */
	virtual void InitialiseMezzanine() = 0; // Base initialisation Mezzanine MMKO
	virtual void SelfTest() = 0; // make test with Mezzanine
	virtual void GetInfoMezz() = 0; // get information about devices Mezzanine
	virtual void UnmkoTestExchange() = 0; // Change Test
	virtual void TestMemory() = 0; // Test Memory
	virtual void CloseSession() = 0; // close connect Mezzanine MKO and carrier Mezzanine
/* Methods for monitoring messages */
	virtual void MonitorConfigure() = 0; // Work Mezzanine in Bus Monitor Mode
protected:
};

