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

class MainBus {
public:
	explicit MainBus(BUSLINE line);
	~MainBus();
	[[nodiscard]] bool SelfTest(); // Mezzanine self-test, info, version, memory test
	/* Add controller and return instance for it
	 * bcOptions - Controller bus settings
	 * UNMMKO1_BC_DEFAULT - TRANSFORMER CONNECTION(DEFAULT)*/
	std::shared_ptr<ControllerMode>& addController(MainBus* mb, const int& bcOptions = UNMMKO1_BC_DEFAULT);
	/* Add monitor and return instance for it
	 * monOptions - Monitor flags settings
	 * UNMMKO1_MON_TRANSFORM - TRANSFORMER CONNECTION(DEFAULT)
	 * UNMMKO1_MON_BUS_A_AND_B - MONITORING MESSAGES ONLY BUS A AND B */
	std::unique_ptr<MonitorMode> addMonitor(const int& monOptions =
	UNMMKO1_MON_TRANSFORM | UNMMKO1_MON_BUS_A_AND_B);
	/* Add abonent to abonent and return instance for it
	 * rtOptions - Abonent device settings
	 * UNMMKO1_RT_TRANSFORM - TRANSFORMER CONNECTION(DEFAULT)
	 * UNMMKO1_RT_BUS_A_AND_B - TERMINAL DEVICE RESPONSE TO MESSAGES THAT WERE SENT BY A AND B BUS(DEFAULT)
	 * UNMMKO1_RT_DEFAULT_RESPONSE - TERMINAL DEVICE CREATES RESPONSES BY DEFAULT ON ALL MESSAGES TYPE*/
	std::unique_ptr<AbonentMode> addAbonent(uint32_t address, const int& rtOptions =
	UNMMKO1_RT_DEFAULT | UNMMKO1_RT_BUS_A_AND_B | UNMMKO1_RT_DEFAULT_RESPONSES);
	/* Getters and Setters */
	[[nodiscard]] int32_t getMkoStatus() const;
	[[nodiscard]] uint32_t getMkoSession() const;
	[[nodiscard]] BUSLINE getLineBus() const;
private:
	BUSLINE lineBus;
	char resourceName[256]{}; // address mezzanine carrier which found MKO
	uint16_t position{}; // position mezzanine MKO on mezzanine carrier
	int32_t status{};
	uint32_t session{};
	uint32_t carrierSession{};
	void DeviceInit(); /*init carrier mezzanine and MKO */
	void CloseSession() const; // close connect Mezzanine MKO and carrier Mezzanine
	int32_t search(); // Function for Search MainBus
	std::map<BUSLINE, std::shared_ptr<ControllerMode>> controllers; // list of controllers
};

