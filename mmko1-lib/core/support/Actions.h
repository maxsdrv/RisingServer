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

struct Condition {
	ViStatus cStatus;
	ViSession cSession;
};

class Common {
public:
	Common();
	~Common() { MKOTEXT("~SearchUnmmko()"); }

public:
	std::string resourceName{}; // address mezzanine carrier which found MKO
	ViUInt16 position; // position mezzanine MKO on mezzanine carrier

	ViStatus status;
	ViSession session;
	ViSession resourceManagerSession;
	std::string search_pattern = "?*[0-9]?*::?*::INSTR";
	ViFindList findList{}; // uint32_t
	ViStatus found = VI_ERROR_RSRC_NFOUND;
	ViUInt32 index, count;
	ViSession deviceSession, carrierSession;
	ViUInt16 interfaceType;
	ViInt16 mezzanineNumber;
	ViChar address[256]{};

	int32_t search(); // method for search mezzanine MKO
	[[nodiscard]] bool processUnmmkoError() const;
	[[nodiscard]] bool processUnmbaseError() const;
	ViStatus getStatus();
};
