#pragma once

/* This class wrapper for function search_unmmko1 in common.h
 * it necessary because there was goto defines and is not convenient methods used to
 * old C code */

#include <cstring>
#include <visa.h>
#include <vpptype.h>
#include <unmbase.h>
#include <unmmko1.h>
#include <cstdio>
#include <cstdint>
#include <cstdlib>

#include "SFileLogger.h"
#include "defines.h"


//! Макрос для проверки ошибок при работе с UNMKO
#define unmkocheck(f) if ((status = (f)) < 0) { \
    printf("%s %d %s ", __FILE__, __LINE__, __FUNCTION__); \
    process_unmmko1_error(session, status); return status; } \
    else

//! Макрос для проверки ошибок
#define unmbasecheck(f) if ((status = (f)) < 0) { \
    printf("%s %d %s ", __FILE__, __LINE__, __FUNCTION__); \
    process_unmbase_error(carrier_session, status); return status; } \
    else

void process_unmmko1_error(ViSession session, ViStatus status);
void process_unmbase_error(ViSession session, ViStatus status);
void print_messages(ViUInt32 messages_count, unmmko1_message* messages);

//static ViChar resource_name[256];
//static ViUInt16 position = 0;
static ViSession session = 0;

class SearchUnmmko {
public:
	SearchUnmmko();
	~SearchUnmmko() { MKOTEXT("~SearchUnmmko()"); }

public:
	std::string resourceName{}; // address mezzanine carrier which found MKO
	ViUInt16* position; // position mezzanine MKO on mezzanine carrier

	ViSession resource_manager_session;
	std::string search_pattern = "?*[0-9]?*::?*::INSTR";
	ViFindList find_list{}; // uint32_t
	ViStatus found = VI_ERROR_RSRC_NFOUND;
	ViUInt32 index, count;
	ViSession device_session, carrier_session;
	ViUInt16 interface_type;
	ViInt16 mezzanine_number;
	ViChar address[256]{};

	int32_t search(); // method for search mezzanine MKO
};
