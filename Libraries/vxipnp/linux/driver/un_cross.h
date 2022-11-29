#ifndef _UN_CROSS_HEADER_
#define _UN_CROSS_HEADER_

#include <limits.h>
#include <visa.h>

//support only WINDOWS or LINUX
#if defined(_WIN64) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#define __UN_WINDOWS__
#endif


#ifdef __UN_WINDOWS__	
//>>>>>>>>>>>>>>>>>>>>>>> W I N D O W S >>>>>>>>>>>>>>>>>>>>>>>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif

#include <windows.h>

#define _LIB_API_EXPORT __declspec(dllexport)
		
#ifndef _VI_INT64_UINT64_DEFINED
	#define _VI_INT64_UINT64_DEFINED
	typedef unsigned   __int64  ViUInt64;
	typedef _VI_SIGNED __int64  ViInt64;
#endif

	typedef HANDLE		MUTEX_TYPE;
	
#define InterlockedExchange_val LONG

//<<<<<<<<<<<<<<<<<<<<<<< W I N D O W S <<<<<<<<<<<<<<<<<<<<<<<
#else
//>>>>>>>>>>>>>>>>>>>>>>> L I N U X >>>>>>>>>>>>>>>>>>>>>>>

#include <semaphore.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

#define _LIB_API_EXPORT __attribute__((visibility("default")))
#define InterlockedExchange_val volatile ViUInt32
#define InterlockedExchange(_ptr_, _val_) __atomic_exchange_n((_ptr_), (_val_), __ATOMIC_SEQ_CST)
#define __cdecl

#ifndef _VI_INT64_UINT64_DEFINED

	#define _VI_INT64_UINT64_DEFINED
	#include <sys/types.h>

#endif

	typedef void * MUTEX_TYPE;
	typedef void * DL_HANDLE;
	typedef void * HMODULE;
	typedef void * HANDLE;

#define __int64 ViInt64
#define __int32 ViInt32
#define __int16 ViInt16
#define __int8  ViInt8

//<<<<<<<<<<<<<<<<<<<<<<< L I N U X <<<<<<<<<<<<<<<<<<<<<<<
#endif

ViReal64 _VI_FUNC cross_timer(void);

void _VI_FUNC cross_delay(ViReal64 sec);

ViStatus _VI_FUNC cross_mutex_open(ViChar *mutexName, MUTEX_TYPE *hMutex);

void _VI_FUNC cross_mutex_close(MUTEX_TYPE hMutex);

ViStatus _VI_FUNC cross_mutex_lock(MUTEX_TYPE hMutex, ViUInt32 s_tmo);	//Number of seconds!!!

ViStatus _VI_FUNC cross_mutexes_lock(ViUInt32 nMutex, MUTEX_TYPE *hMutex, ViUInt32 s_tmo);	//Number of seconds!!!

void _VI_FUNC cross_mutex_unlock(MUTEX_TYPE hMutex);

int cross_switch_thread(void);

ViUInt32 _VI_FUNC cross_getpid(void);
ViUInt32 _VI_FUNC cross_gettid(void);

HMODULE cross_load_dll(const char * dll_name);
int cross_free_dll(const HMODULE dll_handle);
void * cross_get_dll_sym(const HMODULE dll_handle, const char * sym_name);

HANDLE cross_map_global(const char *mapname, int size, void **mapptr, ViStatus *fInit);
void cross_unmap_global(HANDLE hMapObject, void *mapptr);

#endif // _UN_COMPAT_HEADER_
