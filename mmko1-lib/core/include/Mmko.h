#pragma once

/* Base class for Init and Self-test MMKO1 and work with Controller, Monitor,
 * Terminal-device */
#include <unmmko1.h>
#include <memory>
#include <map>

#include "Actions.h"

/* Bus line for transmitting data */
using BUSLINE = unmmko1_bus;

class ControllerMode;
class MonitorMode;
class AbonentMode;


struct StateMko {
	~StateMko() { std::cout << "~StateMko()" << '\n'; }
	char resourceName[256]{}; // address mezzanine carrier which found MKO
	uint16_t position {}; // position mezzanine MKO on mezzanine carrier
	int32_t status = VI_SUCCESS;
	uint32_t session = 0;
	uint32_t carrierSession = 0;
};
int32_t search(StateMko* state); // Function for Search Mmko

class Mmko {
public:
	explicit Mmko(BUSLINE line);
	~Mmko();
	static void SelfTest(); // Mezzanine self-test, info, version, memory test
	static void CloseSession(); // close connect Mezzanine MKO and carrier Mezzanine

	ControllerMode* addController(int bcOptions);
	MonitorMode* addMonitor();
	/* Add abonent to abonent list on address */
	AbonentMode* addAbonent(uint32_t address);

	/* Getters and Setters */
	[[nodiscard]] static int32_t getStatus() ;
	[[nodiscard]] static uint32_t getMkoSession() ;
	[[nodiscard]] static uint32_t getCarrierSession();
	[[nodiscard]] BUSLINE getLine() const;
private:
	BUSLINE lineBus; //condition bus-line mmko1	(main/reserve)

	std::unique_ptr<ControllerMode> controllers;
	std::unique_ptr<MonitorMode> monitor;
	std::unique_ptr<AbonentMode> abonent;
	std::unique_ptr<StateMko> m_State;

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




