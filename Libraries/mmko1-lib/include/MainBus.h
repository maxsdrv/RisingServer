#pragma once

/* Base class for Init and Self-test MMKO1 and work with Controller, Monitor,
 * Terminal-device */
#include <memory>
#include <map>
#include <iostream>
#include <iterator>
#include <boost/core/demangle.hpp>

extern "C" {
#include <unmmko1.h>
}
#include "ControllerMode.h"
#include "AbonentMode.h"

class MonitorMode;
//class AbonentMode;

class MainBus {
public:
	static const int NoSWD = 0xFF; // if wasn't responding-word set this flag;

	explicit MainBus();
	~MainBus();
	[[nodiscard]] bool SelfTest(); // Mezzanine self-test, info, version, memory test
	/* Add controller and return instance for it
	 * bcOptions - Controller bus settings
	 * UNMMKO1_BC_DEFAULT - TRANSFORMER CONNECTION(DEFAULT)*/
	ControllerMode* CreateController(BUSLINE busLine);
	/* Add monitor and return instance for it
	 * monOptions - Monitor flags settings
	 * UNMMKO1_MON_TRANSFORM - TRANSFORMER CONNECTION(DEFAULT)
	 * UNMMKO1_MON_BUS_A_AND_B - MONITORING MESSAGES ONLY BUS A AND B */
	void CreateMonitor(BUSLINE busLine);
	/* Add abonent to abonent and return instance for it
	 * rtOptions - Abonent device settings
	 * UNMMKO1_RT_TRANSFORM - TRANSFORMER CONNECTION(DEFAULT)
	 * UNMMKO1_RT_BUS_A_AND_B - TERMINAL DEVICE RESPONSE TO MESSAGES THAT WERE SENT BY A AND B BUS(DEFAULT)
	 * UNMMKO1_RT_DEFAULT_RESPONSE - TERMINAL DEVICE CREATES RESPONSES BY DEFAULT ON ALL MESSAGES TYPE*/
	void CreateAbonent(BUSLINE busLine, const uint32_t& address);
	/* Getters and Setters */
	[[nodiscard]] int32_t getMkoStatus() const;
	[[nodiscard]] uint32_t getMkoSession() const;
	/* */
	template <typename TObject, typename... TArgs>
	auto CreateMode(TArgs&&... args) -> decltype(std::shared_ptr<TObject>()){
		std::cout << __func__ << ": ";
//		((std::cout << args << ", "), ...);
		std::cout << '\n';
//		return std::shared_ptr<TObject>(new TObject(std::forward<TArgs>(args)...));
		if constexpr (std::is_constructible_v<TObject, TArgs...>) {
			std::cout << "Compile time start()" << '\n';
			return std::shared_ptr<TObject>(new TObject(std::forward<TArgs>(args)...));
		}
		else {
			std::cout << "OBJECT::NOT::CREATED" << '\n';
			return nullptr;
		}
	}
	/* */
private:
	BUSLINE lineMKO{};
	char resourceName[256]{}; // address mezzanine carrier which found MKO
	uint16_t position{}; // position mezzanine MKO on mezzanine carrier
	int32_t status{};
	uint32_t session{}; //Unique ID of connection session with device
	uint32_t carrierSession{};
	void DeviceInit(); /*init carrier mezzanine and MKO */
	void CloseSession() const; // close connect Mezzanine MKO and carrier Mezzanine
	int32_t search(); // Function for Search MainBus
	std::map<BUSLINE, std::shared_ptr<ControllerMode>> controllers; // list of controllers
	std::map<BUSLINE, std::shared_ptr<AbonentMode>> terminalDevices; //list of terminal devices
};
