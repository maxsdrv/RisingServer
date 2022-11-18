#pragma once

/* Base class for Init and Self-test MMKO1 and work with Controller, Monitor,
 * Terminal-device */

#include <unmmko1.h>
#include <memory>
#include <map>

#include "Actions.h"

class ControllerMode;
class MonitorMode;
class AbonentMode;

class Mmko {
public:
	explicit Mmko(BUSLINE line);
	~Mmko();
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
	std::unique_ptr<AbonentMode> abonent;

public:
	ControllerMode* addController(const uint16_t& rxtx);
	MonitorMode* addMonitor();
	/* Add abonent to abonent list on address */
	AbonentMode* addAbonent(uint32_t address);

private:
	/* Adds arguments into class constructor and return instance */
	template<class T, class TBit>
	std::shared_ptr<T>& insertObject(const TBit& rt);
	/* This method necessary to use class with private constructor
	 * Method accepts arguments and class type then return created class object */
	template<class T, class B>
	constexpr T* add(const B& bit);
	/* Getting MonitorMode class instance */
	[[nodiscard]] MonitorMode* getMonitor() const;
	/*init carrier mezzanine and MKO */
	void DeviceInit();
};

template<class T, class B>
constexpr T* Mmko::add(const B& bit)
{
	std::shared_ptr<T>& pObj = insertObject<T>(bit);
	return pObj.get();
}




