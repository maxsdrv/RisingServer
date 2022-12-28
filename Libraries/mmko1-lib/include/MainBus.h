#pragma once

/* Base class for Init and Self-test MMKO1 and work with Controller, Monitor,
 * Terminal-device */
#include <memory>
#include <map>
#include <iostream>
#include <iterator>
#include <functional>

#include "enums.h"

extern "C" {
#include <unmmko1.h>
}
class MonitorMode;
class AbonentMode;
class ControllerMode;

class MainBus {
public:
	static constexpr int NoSWD = 0xFF; // if wasn't responding-word set this flag;

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
	MonitorMode* CreateMonitor();
	/* Add abonent to abonent and return instance for it
	 * rtOptions - Abonent device settings
	 * UNMMKO1_RT_TRANSFORM - TRANSFORMER CONNECTION(DEFAULT)
	 * UNMMKO1_RT_BUS_A_AND_B - TERMINAL DEVICE RESPONSE TO MESSAGES THAT WERE SENT BY A AND B BUS(DEFAULT)
	 * UNMMKO1_RT_DEFAULT_RESPONSE - TERMINAL DEVICE CREATES RESPONSES BY DEFAULT ON ALL MESSAGES TYPE*/
	AbonentMode* CreateAbonent(BUSLINE busLine, uint32_t address);
	/* Getters and Setters */
	[[nodiscard]] int32_t getMkoStatus() const;
	[[nodiscard]] uint32_t getMkoSession() const;
	/* */
	void reset(uint32_t session);
	bool resetState;
	/* */

private:
	BUSLINE lineMKO{};
	char resourceName[256]{}; // address mezzanine carrier which found MKO
	uint16_t position; // position mezzanine MKO on mezzanine carrier
	int32_t status;
	uint32_t m_Session; //Unique ID of connection session with device
	uint32_t carrierSession;
	void DeviceInit(); /*init carrier mezzanine and MKO */
	void CloseSession() const; // close connect Mezzanine MKO and carrier Mezzanine
	int32_t search(); // Function for Search MainBus
	std::map<BUSLINE, std::shared_ptr<ControllerMode>> controllers{}; // list of controllers
	std::map<BUSLINE, std::shared_ptr<AbonentMode>> terminalDevices; //list of terminal devices
	/* Method for creating MKO-mode that
	 * return smart-pointer instance in dependency on transmitted arguments*/


	template<typename T_r, typename... TArgs>
	auto CreateMode(TArgs&&... args) {
		std::cout << __func__ << ": ";
		std::cout << sizeof...(args);
		std::cout << '\n';

		auto returningMode = Add<T_r>(std::forward<TArgs>(args) ...);
		if constexpr (std::is_pointer_v<decltype(returningMode)>) {
			if (returningMode != NULL)
				return returningMode;
			else
				throw std::runtime_error(__func__);
		}
		else
			throw std::runtime_error(__func__);
	}


	template <typename T_r, typename Obj, typename B>
	auto FindValueContainer(Obj object, B busLine)  noexcept {
		const auto pItr = controllers.find(busLine);
		if (pItr != controllers.end()) {
			return pItr->second.get();
		}
		else {
			controllers[busLine] = std::shared_ptr<T_r>(new T_r(object, busLine));
			const auto newpItr = controllers.find(busLine);
			return newpItr->second.get();
		}
	}

	template <typename T_r, typename... TArgs>
	auto Add(TArgs&&... args) {
		auto mode = FindValueContainer<T_r>(std::forward<TArgs>(args)...);
		if constexpr (std::is_pointer_v<decltype(mode)>) {
			return mode;
		}
		else
			return nullptr;
	}

	/* */
};



















