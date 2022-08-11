#pragma once

#include <memory>
#include <unmmko1.h>

#include "ITestMmko.h"


class Common;

class TestMmko : public ITestMmko {
public:
	TestMmko();
	~TestMmko() override;

	void Init() override;
	void SelfTest() override; // Mezzanine self-test, info, version, memory test
	void Close() override; // close connect Mezzanine MKO and carrier Mezzanine

	/* Message monitoring */
	int32_t MonitorConfigure() override;
	int32_t SendMessage(const std::vector<uint16_t>& words) override;
private:
	std::unique_ptr<Common> searchMko;
	bool statusInit;
};



