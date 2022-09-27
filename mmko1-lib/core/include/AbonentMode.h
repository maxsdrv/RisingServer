#pragma once

#include <cstdint>
class MMKOInterface;

class AbonentMode
{
private:
	friend class MMKOInterface;

	explicit AbonentMode(MMKOInterface* testMmko, int address);
public:
	/* non-copyable class */
	AbonentMode(const AbonentMode&) = delete;
	AbonentMode(AbonentMode&&) = delete;
	AbonentMode& operator=(const AbonentMode&) = delete;
	AbonentMode& operator=(AbonentMode&&) = delete;
	/***************************************************/
private:
	MMKOInterface* objMmko;
	uint32_t abonentSession{};
	uint32_t abonentAddr{};
};

