#ifndef UNSPY_H
#define UNSPY_H

#ifdef __cplusplus
	extern "C" {
#endif

#include <stdarg.h>

#include "visa.h"

#if !defined(_WIN64) && !defined(WIN32) && !defined(_WIN32) && !defined(__WIN32__)
	#define _LIB_API __attribute__((visibility("default")))
#endif

//spy_reason
#define SPY_ERR		1
#define SPY_MSG		2
#define SPY_ALL		0xFFFF

//spy_filter
#define SPY_F_IO	1	//VISA Private Filters
#define SPY_F_OTHER	2	//
#define SPY_F_DBG	4	//

#define SPY_F_USER	0x10	//User defined filters
#define SPY_F_USER1	0x20
#define SPY_F_USER2	0x40
#define SPY_F_USER3	0x80

#define SPY_F_USER4	0x1000	//User defined filters NEW
#define SPY_F_USER5	0x2000
#define SPY_F_USER6	0x4000
#define SPY_F_USER7	0x8000

//spy_flags
#define SPY_FLAG_TIMESTAMP			0x01
#define SPY_FLAG_PROCESSNUM			0x02
#define SPY_FLAG_PROCESSID			0x04
#define SPY_FLAG_THREADID			0x08

#define SPY_FLAG_NOCYCLE			0x100
#define SPY_FLAG_ERRSTOP			0x200

#define SPY_FLAG_FIRST_PROCESS		0x1000
#define SPY_FLAG_FIRST_PROCESS_OK	0x2000

// Will be add to ini file
#define SPY_BUFFER_SIZE_DEFAULT  1000000

#pragma pack(push)
#pragma pack(8)
typedef struct __SUnSpy 
{
	ViInt32		spy_size;					//size of Spy buffer
	ViInt32		spy_idx;					//index of the last free char in buffer
	ViInt32		spy_allcount;				//count of all chars in buffer, if log loop to start of buffer
	ViInt32		spy_reason;					//SPY Reason: SPY_ERR, SPY_MSG, SPY_ALL
	ViInt32		spy_filter;					//SPY Filter: SPY_F_IO, SPY_F_OTHER, SPY_F_DBG, SPY_F_USER
	ViInt32		spy_flags;					//do or not insert time

	ViInt32 attachedViewerID;		//PID of active viewer
	
	struct 
	{
		ViInt32 ID;	//attached Process ID
		ViInt32 disabled;

	} attachedProcessID[256];

} SUnSpy, *PSUnSpy;
#pragma pack(pop)

typedef void (*PUnFSpyLogT) (int filter, const char *fmt, ...);
typedef void (*PUnFRSpyLogT) (int reason, int filter, const char *fmt, ...);
typedef int (*PUnGetSpyT) (PSUnSpy *SSpy, char **spy_ptr);

extern PUnFSpyLogT punFSpyLog;
extern PUnFRSpyLogT punFRSpyLog;
extern PUnGetSpyT punGetSpy;

//Get Spy struct and pointer to spy buffer
int _LIB_API unGetSpy (
			 PSUnSpy *SSpy,		//can be NULL 
			 char **spy_ptr		//can be NULL 
			 );

//Spy Log with defined reason and filter
//Check '\n' at end of message, and attach it if not present
void _LIB_API unFRTSpyLog (
				int reason, 
				int filter, 
				const char *fmt, 
				...
				);

//Spy Log with defined filter and any reason!=0
//Check '\n' at end of message, and attach it if not present
void _LIB_API unFSpyLog (
				int filter, 
				const char *fmt, 
				...
				);

//Spy Log with any filter!=0 and reason!=0
//Check '\n' at end of message, and attach it if not present
void _LIB_API unSpyLog (
				const char *fmt, 
				...
				);

//Spy Log with defined reason and filter
//Don't check '\n' at end of message, work as standard printf
void _LIB_API unFRSpyLogS (
				int reason, 
				int filter, 
				const char *fmt, 
				...
				);

//Spy Log with defined filter and any reason!=0
//Don't check '\n' at end of message, work as standard printf
void _LIB_API unFSpyLogS (
				int filter, 
				const char *fmt, 
				...
				);

//Spy Log with any filter!=0 and reason!=0
//Don't check '\n' at end of message, work as standard printf
void _LIB_API unSpyLogS (
				const char *fmt, 
				...
				);

//Spy Log with defined reason and filter
//Check '\n' at end of message, and attach it if not present
void _LIB_API unvFRSpyLog (
				int reason, 
				int filter, 
				const char *fmt, 
				va_list args
				);

//Spy Log with defined filter and any reason!=0
//Check '\n' at end of message, and attach it if not present
void _LIB_API unvFSpyLog (
				int filter, 
				const char *fmt, 
				va_list args
				);

//Spy Log with any filter!=0 and reason!=0
//Check '\n' at end of message, and attach it if not present
void _LIB_API unvSpyLog (
				const char *fmt, 
				va_list args
				);

//Spy Log with defined reason and filter
//Don't check '\n' at end of message, work as standard printf
void _LIB_API unvFRSpyLogS (
				int reason, 
				int filter, 
				const char *fmt, 
				va_list args
				);

//Spy Log with defined filter and any reason!=0
//Don't check '\n' at end of message, work as standard printf
void _LIB_API unvFSpyLogS (
				int filter, 
				const char *fmt, 
				va_list args
				);

//Spy Log with any filter!=0 and reason!=0
//Don't check '\n' at end of message, work as standard printf
void _LIB_API unvSpyLogS (
				const char *fmt, 
				va_list args
				);

//Function used in Spy Log Viewer
//Also application can use this with spy_reason=0 for stop log
int  _LIB_API unSpyReason (
				 int spy_reason
				 );

//Function used in Spy Log Viewer
int  _LIB_API unSpyFilter (
				 int filter, 
				 int spy_time
				 );

//fast unSpyLog call macros - run faster when LOG disabled
//Note: for use this, you must get unGetSpy with SSpy parameter 
/*
#define unFRSpyLog0(x0,y0,z0)									if(SSpy->spy_reason){unFRSpyLog(x0,y0,z0);}else
#define unFRSpyLog1(x0,y0,z0,a1)								if(SSpy->spy_reason){unFRSpyLog(x0,y0,z0,a1);}else
#define unFRSpyLog2(x0,y0,z0,a1,a2)								if(SSpy->spy_reason){unFRSpyLog(x0,y0,z0,a1,a2);}else
#define unFRSpyLog3(x0,y0,z0,a1,a2,a3)							if(SSpy->spy_reason){unFRSpyLog(x0,y0,z0,a1,a2,a3);}else
#define unFRSpyLog4(x0,y0,z0,a1,a2,a3,a4)						if(SSpy->spy_reason){unFRSpyLog(x0,y0,z0,a1,a2,a3,a4);}else
#define unFRSpyLog5(x0,y0,z0,a1,a2,a3,a4,a5)					if(SSpy->spy_reason){unFRSpyLog(x0,y0,z0,a1,a2,a3,a4,a5);}else
#define unFRSpyLog6(x0,y0,z0,a1,a2,a3,a4,a5,a6)					if(SSpy->spy_reason){unFRSpyLog(x0,y0,z0,a1,a2,a3,a4,a5,a6);}else
#define unFRSpyLog7(x0,y0,z0,a1,a2,a3,a4,a5,a6,a7)				if(SSpy->spy_reason){unFRSpyLog(x0,y0,z0,a1,a2,a3,a4,a5,a6,a7);}else
#define unFRSpyLog8(x0,y0,z0,a1,a2,a3,a4,a5,a6,a7,a8)			if(SSpy->spy_reason){unFRSpyLog(x0,y0,z0,a1,a2,a3,a4,a5,a6,a7,a8);}else
#define unFRSpyLog9(x0,y0,z0,a1,a2,a3,a4,a5,a6,a7,a8,a9)		if(SSpy->spy_reason){unFRSpyLog(x0,y0,z0,a1,a2,a3,a4,a5,a6,a7,a8,a9);}else
#define unFRSpyLog10(x0,y0,z0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10)	if(SSpy->spy_reason){unFRSpyLog(x0,y0,z0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10);}else
*/
const char unspy_name_lib[] = "libunspy.so";

#ifdef __cplusplus
	}
#endif

#endif

