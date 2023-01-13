#pragma once

/* Base class for Init and Self-test MMKO1 and work with Controller, Monitor,
 * Terminal-device */

#include <memory>
#include <map>
#include <iostream>
#include <iterator>
#include <functional>

#include "enums.h"

#include <unmmko1.h>

class MonitorMode;
class AbonentMode;
class ControllerMode;

class MainBus {
public:
	static constexpr int no_swd = 0xFF; // if wasn't responding-word set this flag;

	explicit MainBus();
	~MainBus();
	[[nodiscard]] bool self_test(); // Mezzanine self-test, info, version, memory test
	/* Add controller and return instance for it
	 * bcOptions - Controller bus settings
	 * UNMMKO1_BC_DEFAULT - TRANSFORMER CONNECTION(DEFAULT)*/
	ControllerMode* create_controller(BUSLINE busLine);
	/* Add monitor and return instance for it
	 * monOptions - Monitor flags settings
	 * UNMMKO1_MON_TRANSFORM - TRANSFORMER CONNECTION(DEFAULT)
	 * UNMMKO1_MON_BUS_A_AND_B - MONITORING MESSAGES ONLY BUS A AND B */
	void remove_controller(BUSLINE bus_line);
	MonitorMode* create_monitor();
	/* Add abonent to abonent and return instance for it
	 * rtOptions - Abonent device settings
	 * UNMMKO1_RT_TRANSFORM - TRANSFORMER CONNECTION(DEFAULT)
	 * UNMMKO1_RT_BUS_A_AND_B - TERMINAL DEVICE RESPONSE TO MESSAGES THAT WERE SENT BY A AND B BUS(DEFAULT)
	 * UNMMKO1_RT_DEFAULT_RESPONSE - TERMINAL DEVICE CREATES RESPONSES BY DEFAULT ON ALL MESSAGES TYPE*/
	MonitorMode* get_monitor() const {
		return monitor.get();
	}
	void remove_monitor();
	AbonentMode* create_abonent(BUSLINE busLine, uint32_t address);
	void remove_abonent(BUSLINE bus_line, uint32_t address);
	/* Getters and Setters */
	[[nodiscard]] int32_t get_mko_status() const;
	[[nodiscard]] uint32_t get_mko_session() const;
	/* */
	void reset(uint32_t session) const;
	/* */

private:
	BUSLINE line_mko{};
	char resource_name[256]{}; // address mezzanine carrier which found MKO
	uint16_t position; // position mezzanine MKO on mezzanine carrier
	int32_t status;
	uint32_t m_Session; //Unique ID of connection session with device
	uint32_t carrier_session;
	void device_init(); /*init carrier mezzanine and MKO */
	void close_session() const; // close connect Mezzanine MKO and carrier Mezzanine
	int32_t search(); // Function for Search MainBus
	std::map<BUSLINE, std::shared_ptr<ControllerMode>> controllers; // list of controllers
	std::map<BUSLINE, std::shared_ptr<AbonentMode>> terminal_devices; //list of terminal devices
	std::unique_ptr<MonitorMode> monitor;
	/* Method for creating MKO-mode that
	 * return smart-pointer instance in dependency on transmitted arguments*/


	template<typename T_r, typename... TArgs>
	T_r* create_mode(TArgs&&... args) {
		std::cout << __func__ << ": ";
		std::cout << sizeof...(args);
		std::cout << '\n';

		auto returning_mode = get<T_r>(std::forward<TArgs>(args) ...);
		if (returning_mode != NULL)
			return returning_mode;
		else
			return nullptr;
	}

	template <typename T_r, typename Obj, typename B>
	T_r* get_container(Obj* object, B bus_line)  noexcept {
		const auto p_itr = controllers.find(bus_line);
		if (p_itr != controllers.end()) {
			return p_itr->second.get();
		}
		else {
			const auto f_itr = controllers[bus_line] = std::shared_ptr<T_r>(new T_r(object, bus_line));
			return f_itr.get();
		}
	}
	template <typename T_r, typename Obj, typename B, typename A>
	T_r* get_container(const Obj& object, B bus_line, A address) noexcept {
		const auto p_itr = terminal_devices.find(bus_line);
		if (p_itr != terminal_devices.end()) {
			const auto adr_itr = p_itr->second;
			if (adr_itr->get_address() == address) {
				return adr_itr.get();
			}
			return nullptr;
		}
		else {
			terminal_devices[bus_line] =
					std::shared_ptr<T_r>(new T_r(object, bus_line, address));
			const auto new_itr = terminal_devices.find(bus_line);
			return new_itr->second.get();
		}
	}

	template <typename T_r, typename... TArgs>
	auto get(TArgs&&... args) noexcept {
		auto mode = get_container<T_r>(std::forward<TArgs>(args)...);
		return mode;
	}

	/* */
};



















