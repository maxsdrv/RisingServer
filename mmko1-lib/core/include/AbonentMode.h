/* Class for working of bus in terminal device mode */

#pragma once

#include <cstdint>
#include <vector>

class Mmko;

class AbonentMode
{
private:
	friend class Mmko;

	/* Ctor accepts transmit-device address and rt_options(but rt_options declare by default
	 * UNMMKO1_RT_DEFAULT_RESPONSES) */
	explicit AbonentMode(Mmko* testMmko, uint32_t address);
public:
	~AbonentMode();
	/* non-copyable class */
	AbonentMode(const AbonentMode&) = delete;
	AbonentMode(AbonentMode&&) = delete;
	AbonentMode& operator=(const AbonentMode&) = delete;
	AbonentMode& operator=(AbonentMode&&) = delete;
	/***************************************************/
	void startAbonent() const; // start mezzanine in terminal-device
	void stopAbonent() const; // stop mezzanine, in running terminal-devices mode
	/* setData is method which calls c-function unmko1_rt_set_subaddress_data
	 * for chooses sub addresses will set data-words then transmit of terminal-devices in response
	 * to a data transfer command */
	void setData(uint16_t subAddr, int dataWordsCount, std::vector<uint16_t>& dataWords) const;

	void setDataF5(uint16_t commandCode, uint16_t dataWord) const;
private:
	Mmko* objMmko;
	uint32_t abonentSession{};
	int32_t abonentStatus{};
	uint32_t abonentAddr{};
};

