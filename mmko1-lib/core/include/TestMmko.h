#pragma once

/* Base class for Init and Self-test MMKO1 */

#include <vector>

#include "ITestMmko.h"

class TestMmko : public ITestMmko {
public:
	explicit TestMmko(unmmko1_bus bus = UNMMKO1_BUS_A);
	~TestMmko() override;

	void Init() override; // Initialise MMKO1 and carrier Mezzanine
	void SelfTest() override; // Mezzanine self-test, info, version, memory test
	void Close() override; // close connect Mezzanine MKO and carrier Mezzanine
    /* Create command word */
	uint16_t PackCw(uint16_t address, uint16_t RxTx, uint16_t subAddress, uint16_t wordCount) override;
public:
	static bool statusInit; // stores condition of initialise unmmko1 and unmbase
protected:
	//static bool statusInit; // stores condition of initialise unmmko1 and unmbase
	bool isInit() const;
	/* *Test*  expression for checking condition of Status Unmmko1
	 * TO DO return value */
	inline ViStatus checkProcess(ViStatus status) {
		if (status < 0) {
			return common->processUnmmkoError();
		}
		else {
			return 1;
		}
	}

    std::unique_ptr<Common> common; // class pointer Actions
	std::vector<std::shared_ptr<unmmko1_command>> commands; // struct commands vector
	unmmko1_bus bus; // bus condition
private:
	/* Getters and Setters */
	void setBus(unmmko1_bus) override;
	unmmko1_bus getBus() const override;
};



