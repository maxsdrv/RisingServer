#pragma once

#include "ITestMmko.h"


class TestMmko : public ITestMmko {
public:
	explicit TestMmko(unmmko1_bus bus);
	~TestMmko() override;

	static TestMmko* create();
	void Init() override;
	void SelfTest() override; // Mezzanine self-test, info, version, memory test
	void Close() override; // close connect Mezzanine MKO and carrier Mezzanine

	int PackCw(uint16_t address, uint16_t RxTx, uint16_t subAddress, uint16_t wordCount) override;
protected:
	bool statusInit{}; // stores condition of initialise unmmko1 and unmbase

	/* *Test*  expression for checking condition of Status Unmmko1
	 * TO DO return value */
	constexpr ViStatus checkProcess(ViStatus status) {
		if (status < 0) {
			return common->processUnmmkoError();
		}
		else {
			return 1;
		}
	}
private:
	static unmmko1_bus mBus;
};



