#pragma once

/* This Singleton Class-Wrapper for C-header common.h
*/

#include <cstring>
#include <visa.h>
#include <vpptype.h>
#include <unmbase.h>
#include <unmmko1.h>
#include <cstdio>
#include <cstdint>
#include <cstdlib>

#include "SFileLogger.h"
#include "BaseMkoEnums.h"
#include "MMKOErrors.h"

class Common
{
private:
	Common();
	~Common();
public:
	static Common& getInstance()
	{
		static Common instance;
		return instance;
	}

	Common(const Common&) = delete;
	Common(Common&&) = delete;
	Common& operator=(const Common&) = delete;
	Common& operator=(Common&&) = delete;

	char resourceName[256]{}; // address mezzanine carrier which found MKO
	ViUInt16 position; // position mezzanine MKO on mezzanine carrier
	ViStatus status;
	ViSession session;
	ViSession resourceManagerSession;
//	std::string search_pattern = "?*[0-9]?*::?*::INSTR";
	ViFindList findList{}; // uint32_t
	ViStatus found = VI_ERROR_RSRC_NFOUND;
	ViUInt32 index, count;
	ViSession deviceSession, carrierSession;
	ViUInt16 interfaceType;
	ViInt16 mezzanineNumber;
	ViChar address[256]{};

	int32_t search(); // method for search mezzanine MKO
	void processUnmmkoError() const;
	void processUnmbaseError() const;

	/* ******************************************** */
};










