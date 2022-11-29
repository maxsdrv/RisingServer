#pragma once

/* Base class for Init and Self-test MMKO1 and work with Controller, Monitor,
 * Terminal-device */
#include <unmmko1.h>
#include <memory>
#include <map>

#include "Actions.h"

class ControllerMode;
class MonitorMode;
class AbonentMode;

/* Bus line for transmitting data */
using BUSLINE = unmmko1_bus;

class Mmko {
public:
	explicit Mmko(BUSLINE line);
	~Mmko();
	[[nodiscard]] bool SelfTest() const; // Mezzanine self-test, info, version, memory test
	void CloseSession() const; // close connect Mezzanine MKO and carrier Mezzanine
	int32_t search(); // Function for Search Mmko
	ControllerMode* addController(int bcOptions); /* Add controller and return instance for it */
	MonitorMode* addMonitor(); /* Add monitor and return instance for it */
	AbonentMode* addAbonent(uint32_t address);/* Add abonent to abonent and return instance for it */
	/* Getters and Setters */
	[[nodiscard]] int32_t getMkoStatus() const;
	[[nodiscard]] uint32_t getMkoSession() const;
	[[nodiscard]] BUSLINE getLineBus() const;
private:
	BUSLINE lineBus;
	char resourceName[256]{}; // address mezzanine carrier which found MKO
	uint16_t position {}; // position mezzanine MKO on mezzanine carrier
	int32_t status = VI_SUCCESS;
	uint32_t session {};
	uint32_t carrierSession {};
	std::unique_ptr<ControllerMode> controllers;
	std::unique_ptr<MonitorMode> monitor;
	std::unique_ptr<AbonentMode> abonent;
	/*init carrier mezzanine and MKO */
	void DeviceInit();
};



