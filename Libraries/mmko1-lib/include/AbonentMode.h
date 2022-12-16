#pragma once

/* Class for working of bus in terminal device mode */

#include <cstdint>
#include <vector>

class MainBus;

class AbonentMode
{
private:
	friend class MainBus;

	/* Ctor accepts transmit-device address and rt_options(but rt_options declare by default
	 * UNMMKO1_RT_DEFAULT_RESPONSES) */
	explicit AbonentMode(MainBus* objectMmko, const uint32_t& address);
public:
	~AbonentMode();
	/* non-copyable class */
	AbonentMode(const AbonentMode&) = delete;
	AbonentMode(AbonentMode&&) = delete;
	AbonentMode& operator=(const AbonentMode&) = delete;
	AbonentMode& operator=(AbonentMode&&) = delete;
	/***************************************************/
	void StartAbonent() const; // start mezzanine in terminal-device
	void StopAbonent() const; // stop mezzanine, in running terminal-devices mode
	/* setData is method which calls c-function unmko1_rt_set_subaddress_data
	 * for chooses sub addresses will set data-words then transmit of terminal-devices in response
	 * to a data transfer command */
	void setData(uint16_t subAddr, int dataWordsCount, std::vector<uint16_t>& dataWords) const;
	/* method for set data-words in response to command of handling in format-message 5 */
	void setDataF5(uint16_t commandCode, uint16_t dataWord) const;
private:
	MainBus* m_objectMmko;
	uint32_t abonentSession{};
	int32_t abonentStatus{};
	uint32_t abonentAddr{};
};

