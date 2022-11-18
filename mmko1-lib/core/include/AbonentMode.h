#pragma once

#include <cstdint>
#include <vector>

class MMKOInterface;

enum class State : unsigned
{
	START,
	STOP
};

class AbonentMode
{
private:
	friend class MMKOInterface;

	explicit AbonentMode(MMKOInterface* testMmko, int address);
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
	MMKOInterface* objMmko;
	uint32_t abonentSession{};
	uint32_t abonentAddr{};
};

