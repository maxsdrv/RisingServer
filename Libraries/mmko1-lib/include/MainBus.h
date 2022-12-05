#pragma once

/* Base class for Init and Self-test MMKO1 and work with Controller, Monitor,
 * Terminal-device */
#include <unmmko1.h>
#include <memory>
#include <map>

class ControllerMode;
class MonitorMode;
class AbonentMode;

/* Bus line for transmitting data */
enum class BUSLINE {
	MKO_BUS_A = 0x0001             /* General Bus Line */,
	MKO_BUS_B = 0x0002             /* Reserve Bus Line */
};

class MainBus
{
public:
	explicit MainBus(BUSLINE line);
	~MainBus();
	[[nodiscard]] bool SelfTest() const; // Mezzanine self-test, info, version, memory test
	ControllerMode* addController(int bcOptions); /* Add controller and return instance for it */
	MonitorMode* addMonitor(); /* Add monitor and return instance for it */
	AbonentMode* addAbonent(uint32_t address);/* Add abonent to abonent and return instance for it */
	/* Getters and Setters */
	[[nodiscard]] int32_t getMkoStatus() const;
	[[nodiscard]] uint32_t getMkoSession() const;
	[[nodiscard]] BUSLINE getLineBus() const;
private:
	BUSLINE lineBus {};
	char resourceName[256]{}; // address mezzanine carrier which found MKO
	uint16_t position{}; // position mezzanine MKO on mezzanine carrier
	int32_t status = VI_SUCCESS;
	uint32_t session{};
	uint32_t carrierSession{};
	ControllerMode* controllers{};
	MonitorMode* monitor{};
	AbonentMode* abonent{};
	void DeviceInit(); /*init carrier mezzanine and MKO */
	void CloseSession() const; // close connect Mezzanine MKO and carrier Mezzanine
	int32_t search(); // Function for Search MainBus
};

