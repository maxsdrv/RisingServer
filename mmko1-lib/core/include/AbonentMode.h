/* Class for working of bus in terminal device mode */

#pragma once

#include <cstdint>
#include <vector>

class Mmko;

enum class State : unsigned
{
	START,
	STOP
};

class AbonentMode
{
private:
	friend class Mmko;

	explicit AbonentMode(Mmko* testMmko, uint32_t address);
public:
	~AbonentMode();
	/* non-copyable class */
	AbonentMode(const AbonentMode&) = delete;
	AbonentMode(AbonentMode&&) = delete;
	AbonentMode& operator=(const AbonentMode&) = delete;
	AbonentMode& operator=(AbonentMode&&) = delete;
	/***************************************************/
	void stopAbonent();
	void setData(uint16_t subAddr, int dataWordsCount, std::vector<uint16_t>& dataWords) const;
	void setDataF5(uint16_t commandCode, uint16_t dataWord) const;
private:
	State state;
	Mmko* objMmko;
	uint32_t abonentSession{};
	uint32_t abonentAddr{};
};

