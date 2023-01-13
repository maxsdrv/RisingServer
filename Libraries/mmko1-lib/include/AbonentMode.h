#pragma once

/* Class for working of bus in terminal device mode */

#include <cstdint>
#include <vector>

#include "unmmko1.h"
#include "enums.h"

class MainBus;
class AbonentMode
{
private:
	friend class MainBus;

	/* Ctor accepts transmit-device address and rt_options(but rt_options declare by default
	 * UNMMKO1_RT_DEFAULT_RESPONSES) */
	explicit AbonentMode(MainBus* object_mmko, BUSLINE bus_line, uint32_t address);
public:
	~AbonentMode();
	/* non-copyable class */
	AbonentMode(const AbonentMode&) = delete;
	AbonentMode(AbonentMode&&) = delete;
	AbonentMode& operator=(const AbonentMode&) = delete;
	AbonentMode& operator=(AbonentMode&&) = delete;
	/***************************************************/
	void start_abonent() const; // start mezzanine in terminal-device
	void stop_abonent() const; // stop mezzanine, in running terminal-devices mode
	/* set_data is method which calls c-function unmko1_rt_set_subaddress_data
	 * for chooses sub addresses will set data-words then transmit of terminal-devices in response
	 * to a data transfer command */
	void set_data(uint16_t sub_addr, int data_words_count, std::vector<uint16_t>& data_words) const;
	/* method for set data-words in response to command of handling in format-message 5 */
	void set_data_f5(uint16_t command_code, uint16_t data_word) const;
	[[nodiscard]] uint32_t get_address() const;
private:
	uint32_t abonent_session{};
	int32_t abonent_status{};
	uint32_t abonent_addr{};
	BUSLINE bus_line{};
};

