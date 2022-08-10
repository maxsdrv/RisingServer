#pragma once

#include <memory>
#include <unmmko1.h>

#include "ITestMmko.h"


class Common;

class TestMmko : public ITestMmko {
public:
	TestMmko();
	~TestMmko() override;

	void InitialiseMezzanine() override;
	void SelfTest() override; // make test with Mezzanine
	void GetInfoMezz() override; // get information about devices Mezzanine
	void UnmkoTestExchange() override; // Change Test
	void TestMemory() override; // Test Memory
	void CloseSession() override; // close connect Mezzanine MKO and carrier Mezzanine
/* Methods for monitoring messages */
	void MonitorConfigure() override; // Work Mezzanine in Bus Monitor Mode
private:
	std::unique_ptr<Common> searchMko;
};

