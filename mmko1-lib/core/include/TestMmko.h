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

	int PackCw(uint16_t address, uint16_t RxTx, uint16_t subAddress, uint16_t wordCount) override;
private:
	std::unique_ptr<Common> searchMko;
	bool statusInit;
};



