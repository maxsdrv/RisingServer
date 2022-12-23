#pragma once

#include <iostream>
#include <vector>

#include "ModuleFactory.h"

/* Enum class of Command Direction by ГОСТ Р52070-2003 */
enum class CONTROL_COMMANDS {
	CTR_INTERFACE,
	SYNC,
	TR_RESPONSE_WORD,
	START_SELF_TEST,
	BLOCK_TRANSMITTER,
	UNBLOCK_TRANSMITTER,
	BLOCK_ERROR_FLAG,
	UNBLOCK_ERROR_FLAG,
	RESET_TR_DEVICE,
	RESERVE,
	TR_VECTOR_WORD = 16,
	SYNC_DATA_WORD,
	TR_LAST_CMD,
	TR_VSK_WORD,
	BLOCK_Nth_TR,
	UNBLOCK_Nth_TR
};

class MainBus;

class MKOModule {
public:
	MKOModule();
	~MKOModule();
	bool SelfTest(); /* produce the mezzanine self-test and return result */
	bool WriteToAbonent();
	bool WriteToAbonentCycle();
	bool ReadFromAbonent();
private:
	BUSLINE selectedBus;
	std::unique_ptr<MainBus> mainbus;
	void AddController(BUSLINE line) const;
	std::map<std::string, CONTROL_COMMANDS> f4Commands; // List type the command F4 format
	std::map<int, int> mkoAddresses; // MKO Addresses according to which they work with any devices
};









