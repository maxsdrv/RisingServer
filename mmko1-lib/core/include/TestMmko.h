#pragma once

/* Base class for Init and Self-test MMKO1 */

#include <unmmko1.h>
#include <memory>

#include "defines.h"
#include "Actions.h"

class TestMmko {
public:
	explicit TestMmko(unmmko1_bus bus_);
	~TestMmko();
	void Init(); // Initialise MMKO1 and carrier Mezzanine
	void SelfTest(); // Mezzanine self-test, info, version, memory test
	void CloseSession(); // close connect Mezzanine MKO and carrier Mezzanine
	bool isInit() const; // check for initialisation
	/* Getters and Setters */
	int32_t getStatus() const;
	uint32_t getSession() const;
	unmmko1_bus getLine() const;
private:
	unmmko1_bus lineBus; //condition bus-line mmko1	(main/reserve)
    std::unique_ptr<Common> common; // class pointer Actions
	bool initStatus;
};



