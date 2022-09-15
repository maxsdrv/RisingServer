#pragma once

/* Base class for Init and Self-test MMKO1 and work with Controller, Monitor,
 * Terminal-device */

#include <unmmko1.h>
#include <memory>

#include "Actions.h"

class ControllerMode;

class TestMmko {
public:
	explicit TestMmko(BUSLINE line);
	~TestMmko();
	static void SelfTest(); // Mezzanine self-test, info, version, memory test
	static void CloseSession(); // close connect Mezzanine MKO and carrier Mezzanine
	/* Getters and Setters */
	[[nodiscard]] static int32 getStatus() ;
	[[nodiscard]] static uint32 getMkoSession() ;
	[[nodiscard]] static uint32 getCarrierSession();
	[[nodiscard]] BUSLINE getLine() const;
private:
	BUSLINE lineBus; //condition bus-line mmko1	(main/reserve)
	/* Controller record type */
	std::shared_ptr<ControllerMode> controllers;

public:
	ControllerMode* addController(const uint16& rxtx, int options);

private:
	/* Adds arguments into class constructor and return instance */
	template<class T, class TBit, class TOptions >
	std::shared_ptr<T>& insertObject(const TBit& rt, TOptions options);
	/* This method necessary to use class with private constructor
	 * Method accepts arguments and class type then return created class object */
	template<class T, class B, class O>
	constexpr T* add(const B& bit, O options);
};

template<class T, class B, class O>
constexpr T* TestMmko::add(const B& bit, O options)
{
	std::shared_ptr<T>& pObj = insertObject<T>(bit, options);

	return pObj.get();
}




