#pragma once

/* Base class for Init and Self-test MMKO1 and work with Controller, Monitor,
 * Terminal-device */

#include <unmmko1.h>
#include <memory>

#include "defines.h"
#include "Actions.h"

class ControllerMode;

class TestMmko {
public:
	TestMmko();
	~TestMmko();
	void Init(); // Initialise MMKO1 and carrier Mezzanine
	static void SelfTest(); // Mezzanine self-test, info, version, memory test
	void CloseSession(); // close connect Mezzanine MKO and carrier Mezzanine
	bool isInit() const; // check for initialisation
	/* Getters and Setters */
	[[nodiscard]] static int32_t getStatus() ;
	[[nodiscard]] static uint32_t getSession() ;
	[[nodiscard]] unmmko1_bus getLine() const;
private:
	unmmko1_bus lineBus; //condition bus-line mmko1	(main/reserve)
//    std::unique_ptr<Common> common; // class pointer Actions
	bool initStatus; // activation status MKO

	/* Controller record type */
	std::unique_ptr<ControllerMode> controllers;
public:
	ControllerMode* addController(unmmko1_bus bus);

private:

};







