#pragma once

/* Base class for Init and Self-test MMKO1 and work with Controller, Monitor,
 * Terminal-device */

#include <unmmko1.h>
#include <memory>
#include <map>

#include "Actions.h"


class ControllerMode;
class MonitorMode;

class TestMmko {
public:
	explicit TestMmko(BUSLINE line);
	~TestMmko();
	static void SelfTest(); // Mezzanine self-test, info, version, memory test
	static void CloseSession(); // close connect Mezzanine MKO and carrier Mezzanine
	/* Getters and Setters */
	[[nodiscard]] static int32_t getStatus() ;
	[[nodiscard]] static uint32_t getMkoSession() ;
	[[nodiscard]] static uint32_t getCarrierSession();
	[[nodiscard]] BUSLINE getLine() const;
	int32_t mkoStatus{};
private:
	BUSLINE lineBus; //condition bus-line mmko1	(main/reserve)
	/* Controller record type */
	std::shared_ptr<ControllerMode> controllers;
	std::unique_ptr<MonitorMode> monitor;

public:
	ControllerMode* addController(const uint16_t& rxtx, int options);
	MonitorMode* addMonitor();

private:
	/* Adds arguments into class constructor and return instance */
	template<class T, class TBit, class TOptions >
	std::shared_ptr<T>& insertObject(const TBit& rt, TOptions options);
	/* This method necessary to use class with private constructor
	 * Method accepts arguments and class type then return created class object */
	template<class T, class B, class O>
	constexpr T* add(const B& bit, O options);
	/* Getting MonitorMode class instance */
	[[nodiscard]] MonitorMode* getMonitor() const;
	/*init carrier mezzanine and MKO */
	void DeviceInit();
};

template<class T, class B, class O>
constexpr T* TestMmko::add(const B& bit, O options)
{
	std::shared_ptr<T>& pObj = insertObject<T>(bit, options);
	return pObj.get();
}




