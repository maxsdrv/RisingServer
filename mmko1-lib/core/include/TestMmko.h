#pragma once

#include "ITestMmko.h"


class TestMmko : public ITestMmko {
public:
	explicit TestMmko(unmmko1_bus bus = UNMMKO1_BUS_A);
	~TestMmko() override;

	void Init() override; // Initialise MMKO1 and carrier Mezzanine
	void SelfTest() override; // Mezzanine self-test, info, version, memory test
	void Close() override; // close connect Mezzanine MKO and carrier Mezzanine
    /* Create command word */
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

    std::unique_ptr<Common> common;
	std::unique_ptr<unmmko1_command> commands;
private:
	/* Getters and Setters */
	void setBus(unmmko1_bus) override;
	unmmko1_bus getBus() override;
};



