#pragma once

/* Base class for Init and Self-test MMKO1 and work with Controller, Monitor,
 * Terminal-device */

#include <unmmko1.h>
#include <memory>

#include "defines.h"
#include "Actions.h"

class ControllerMode;

class TestMmko {
public:
	explicit TestMmko(BUSLINE line);
	~TestMmko();
	void Init(); // Initialise MMKO1 and carrier Mezzanine
	static void SelfTest(); // Mezzanine self-test, info, version, memory test
	void CloseSession(); // close connect Mezzanine MKO and carrier Mezzanine
	bool isInit() const; // check for initialisation
	/* Getters and Setters */
	[[nodiscard]] static int32 getStatus() ;
	[[nodiscard]] static uint32 getSession() ;
	[[nodiscard]] unmmko1_bus getLine() const;
private:
	unmmko1_bus lineBus; //condition bus-line mmko1	(main/reserve)
	bool initStatus; // activation status MKO
	/* Controller record type */
	std::shared_ptr<ControllerMode> controllers;

public:
	ControllerMode* addController(const uint16& rxtx, int options);

private:
	/* */
	template<class T, class TBit, class TOptions >
	std::shared_ptr<T>& insertObject(const TBit& rt, TOptions options);
	/* */
	template<class T, class B, class O>
	constexpr T* add(const B& bit, O options);
};

template<class T, class B, class O>
constexpr T* TestMmko::add(const B& bit, O options)
{
	std::shared_ptr<T>& pObj = insertObject<T>(bit, options);

	return pObj.get();
}




