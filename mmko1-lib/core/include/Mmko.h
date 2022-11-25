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

/* Bus line for transmitting data */
using BUSLINE = unmmko1_bus;

class Mmko {
public:
	explicit Mmko(BUSLINE line);
	~Mmko();
	void SelfTest(); // Mezzanine self-test, info, version, memory test
	void CloseSession() const; // close connect Mezzanine MKO and carrier Mezzanine
	int32_t search(); // Function for Search Mmko

	ControllerMode* addController(int bcOptions);
	MonitorMode* addMonitor();
	/* Add abonent to abonent list on address */
	AbonentMode* addAbonent(uint32_t address);
	/* Getters and Setters */
	[[nodiscard]] int32_t getMkoStatus() const;
	[[nodiscard]] uint32_t getMkoSession() const;
	[[nodiscard]] uint32_t getCarrierSession() const;
	[[nodiscard]] BUSLINE getLineBus() const;
private:
	BUSLINE lineBus;
	char resourceName[256]{}; // address mezzanine carrier which found MKO
	uint16_t position {}; // position mezzanine MKO on mezzanine carrier
	int32_t status = VI_SUCCESS;
	uint32_t session = 0;
	uint32_t carrierSession = 0;
	std::unique_ptr<ControllerMode> controllers;
	std::unique_ptr<MonitorMode> monitor;
	std::unique_ptr<AbonentMode> abonent;

	/* Adds arguments into class constructor and return instance */
	/*template<class T, class TBit>
	std::shared_ptr<T>& insertObject(const TBit& rt);*/
	/* This method necessary to use class with private constructor
	 * Method accepts arguments and class type then return created class object */
	/*template<class T, class B>
	constexpr T* add(const B& bit);*/
	/* Getting MonitorMode class instance */
	[[nodiscard]] MonitorMode* getMonitor() const;
	/*init carrier mezzanine and MKO */
	void DeviceInit();
};

/*template<class T, class B>
constexpr T* Mmko::add(const B& bit)
{
	std::shared_ptr<T>& pObj = insertObject<T>(bit);
	return pObj.get();
}*/

int32_t search(Mmko* state); // Function for Search Mmko


