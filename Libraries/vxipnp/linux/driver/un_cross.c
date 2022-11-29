#include "visatype.h"
#include "un_cross.h"

#ifdef __UN_WINDOWS__
//>>>>>>>>>>>>>>>>>>>>>>> W I N D O W S >>>>>>>>>>>>>>>>>>>>>>>
#ifdef _CVI_
#include <utility.h>
//CVI defined Timer(), Delay()
#else
static double PerfFreq=0;					//Performance Frequency
static ViUInt64 PerfCount0=0;				//Initial Performance Counter
static int		PerfCount0set=0;			//Performance Counter Started flag
// Return seconds
static double Timer(void)
{
	static double firsttime = -1.0;
	
	ViUInt64 PerfCount;
	
	QueryPerformanceCounter((LARGE_INTEGER*)&PerfCount);
	if (!PerfCount0set)
	{
		ViUInt64 pf;
		QueryPerformanceFrequency((LARGE_INTEGER*)&pf);
		PerfFreq = (double)pf;
		PerfCount0set = 1;
		QueryPerformanceCounter((LARGE_INTEGER*)&PerfCount);
		PerfCount0 = PerfCount;
		return 0.0;
	}
	return (double)(PerfCount - PerfCount0) / PerfFreq;
}

static void Delay(double d)
{
	double t = Timer()+dt;

	if (d > 0.002)
	{
		Sleep(d*1e3);
	}
	while (Timer() < t)
		;
}
#endif	//!_CVI_

// занимаем глобальную расшаренную память
HANDLE cross_map_global(const char* mapname, int size, void** mapptr, ViStatus *fInit)
{
	int global, first;
	HANDLE hMapObject;
	static SECURITY_ATTRIBUTES sa;	// Поле sa.bInheritHandle задаёт возможность
									// наследования HANDLE дочерним процессом.
	static SECURITY_DESCRIPTOR sd;	// SECURITY_DESCRIPTOR содержит права доступа
									// и идентифицирует владельца объекта.

	global = !memcmp(mapname, "Global\\", sizeof("Global\\")-1);
	if (global)
	{
		int ok = 0;
		HANDLE hToken = NULL;
		LUID luidSEDebugNameValue;
		TOKEN_PRIVILEGES tkpPrivileges;

		if (OpenProcessToken(GetCurrentProcess(),
							TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
							&hToken))
		{
			if (LookupPrivilegeValue(NULL, 0/*SE_CREATE_GLOBAL_NAME*/, &luidSEDebugNameValue))
			{
				tkpPrivileges.PrivilegeCount = 1;
				tkpPrivileges.Privileges[0].Luid = luidSEDebugNameValue;
				tkpPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
				if (AdjustTokenPrivileges(hToken,
										  0,
										  &tkpPrivileges,
										  0,
										  0,
										  0))
				{
					//OK
					ok = 1;
				}
			}
		}
		if (!ok)
		{	//если не получилось, пробуем открыть без Global,
			//хотя при этом ВСЕ процессы должны сработать так же...
			mapname += sizeof("Global\\");
			global = 0;
		}
		if (hToken)
			CloseHandle(hToken);
	}

	// Инициализация дескриптора безопасности
	InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
	SetSecurityDescriptorDacl(&sd, 1, NULL, 0);

	// Инициализация security attributes
	sa.lpSecurityDescriptor = &sd;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	// разрешить наследование дескриптора дочерним процессом
	sa.bInheritHandle = 1;


	//выравниваем по границе 256 байт
	size = 0xFFFFFF00 & (size + 0xFF);

	if (global)
	{	//смотрим - если ктото бесправный уже открыл без Global\,
		//то и мы откроем так же
		hMapObject = CreateFileMapping(
			INVALID_HANDLE_VALUE, // use paging file
			&sa,                 // security attributes
			PAGE_READWRITE,       // read/write access
			0,                    // size: high 32-bits
			size,				  // size: low 32-bits
			mapname + sizeof("Global\\"));  // name of map object
		first = (GetLastError() != ERROR_ALREADY_EXISTS);
		if (!first)
		{	//таки да :(
			goto MapFile;
		}
		//Мы первые, тогда пробуем Global\ !!!
		CloseHandle(hMapObject);
	}
	// Create a named file mapping object.
	hMapObject = CreateFileMapping(
		INVALID_HANDLE_VALUE, // use paging file
		&sa,                 // security attributes
		PAGE_READWRITE,       // read/write access
		0,                    // size: high 32-bitsstrchr(&name[1], '/')
		size,				  // size: low 32-bits
		mapname);  // name of map object

	if (!hMapObject &&
		global)
	{
		hMapObject = CreateFileMapping(
			INVALID_HANDLE_VALUE, // use paging file
			&sa,                 // security attributes
			PAGE_READWRITE,       // read/write access
			0,                    // size: high 32-bits
			size,				  // size: low 32-bits
			mapname + sizeof("Global\\"));  // name of map object NO "Globals"
	}

	if (hMapObject)
	{
		// The first process to attach initializes memory.
		first = (GetLastError() != ERROR_ALREADY_EXISTS);
MapFile:
		if (fInit)
			*fInit = first;

		// Get a pointer to the file-mapped shared memory.
		*mapptr = MapViewOfFile(
			hMapObject,     // object to map view of
			FILE_MAP_WRITE, // read/write access
			0,              // high offset:  map from
			0,              // low offset:   beginning
			0);             // default: map entire file
		if (*mapptr == NULL)
		{
			CloseHandle(hMapObject);
			hMapObject = NULL;
		}
		else
		if (first)
			memset(*mapptr, 0, size);
	}
	return hMapObject;
}

// Освобождаем глобальную расшаренную память
void cross_unmap_global(HANDLE hMapObject, void *mapptr)
{
	if (hMapObject)
	{
		UnmapViewOfFile(mapptr);
		CloseHandle(hMapObject);
	}
}

//<<<<<<<<<<<<<<<<<<<<<<< W I N D O W S <<<<<<<<<<<<<<<<<<<<<<<
#else
//>>>>>>>>>>>>>>>>>>>>>>> L I N U X >>>>>>>>>>>>>>>>>>>>>>>
 
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
#include <semaphore.h>
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include <dlfcn.h>
#include <string.h>

//#define _GNU_SOURCE         /* Debug*/
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/mman.h>

static struct timespec diff_timespec(struct timespec start, struct timespec end)
{
	struct timespec temp;

	if ((end.tv_nsec-start.tv_nsec)<0)
	{
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1e9 + end.tv_nsec - start.tv_nsec;
	}
	else
	{
		temp.tv_sec = end.tv_sec - start.tv_sec;
		temp.tv_nsec = end.tv_nsec - start.tv_nsec;
	}
	return temp;
}

static struct timespec get_timespec(void)
{
	struct timespec start_time;
	clock_gettime(CLOCK_MONOTONIC, &start_time);
	return start_time;
}

// Return seconds
static double Timer(void)
{
	static double firsttime = -1.0;
	
	struct timespec t = get_timespec();
	if (firsttime < 0)
	{
		firsttime = (double)(*(time_t*)&t.tv_sec) + 1e-9*(double)t.tv_nsec;
		return 0.0;
	}
	return ((double)(*(time_t*)&t.tv_sec) + 1e-9*(double)t.tv_nsec) - firsttime;
}

static void Delay(double d)
{
	usleep(d*1e6);
}

typedef struct __attribute__((__packed__))
{
	void *mapptr;
	int fd;
	unsigned int size;
	ViChar name[NAME_MAX - 4];
} shared_mem_t, *pshared_mem_t;

// занимаем глобальную расшаренную память
HANDLE cross_map_global(const char* mapname, int size, void** mapptr, ViStatus *fInit)
{
	pshared_mem_t pshmem = (pshared_mem_t)calloc(1, sizeof(shared_mem_t));
	if (!pshmem)
		return NULL;
	strcpy(pshmem->name, mapname);
	
	/* Create shared memory object and set its size */

	/* boundary alignment up to 256 bytes */
	size = 0xFFFFFF00 & (size + 0xFF);
	pshmem->size = size;
	
	errno = 0;
	pshmem->fd = shm_open(mapname, O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (pshmem->fd == -1) 
	{
		if (errno != EEXIST) 
		{
			/* Handle error */;
			free(pshmem);
			return NULL;
		}
		// Already exist
		*fInit = 0;
		pshmem->fd = shm_open(mapname,
					  O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH); // without O_EXCL
	}
	else
	{	// First init
		*fInit = 1;
	}
	if (pshmem->fd) 
	{
		if (ftruncate(pshmem->fd, size) == -1)
		{
			/* Handle error */;
			free(pshmem);
			return NULL;
		}
	}
	else
	{
		free(pshmem);
		return NULL;
	}

	/* Map shared memory object */
	*mapptr = pshmem->mapptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, pshmem->fd, 0);
	if (pshmem->mapptr == MAP_FAILED)
	{
		shm_unlink(mapname);
		free(pshmem);
		return NULL;
	}
	return pshmem;
}

// Освобождаем глобальную расшаренную память
void cross_unmap_global(HANDLE hMapObject, void *mapptr)
{
	if (NULL == hMapObject) return;

	pshared_mem_t pshmem = (pshared_mem_t)hMapObject;

	if (0 == munmap(pshmem->mapptr, pshmem->size))
	{
		shm_unlink(pshmem->name);
		free(pshmem);
	}
}

//<<<<<<<<<<<<<<<<<<<<<<< L I N U X <<<<<<<<<<<<<<<<<<<<<<<
#endif

/* cross_timer - Return the number of SECONDS from first call */
ViReal64 _VI_FUNC cross_timer(void)
{
	return Timer();
}

void _VI_FUNC cross_delay(ViReal64 d)
{
	Delay(d);
}

ViUInt64 _VI_FUNC cross_timer_ms(void)
{
	return (ViUInt64)(Timer()*1e3 + 0.5);
}

ViUInt64 _VI_FUNC cross_timer_us(void)
{
	return (ViUInt64)(Timer()*1e6 + 0.5);
}

#ifdef __UN_WINDOWS__
// >>> W I N D O W S
ViStatus _VI_FUNC cross_mutex_open(
								ViChar *mutexName,
								MUTEX_TYPE *hMutex)
{
	ViStatus status = 0;

	*hMutex = CreateMutex(
					NULL,        // no security attributes
					FALSE,       // initially not owned
					mutexName);  // name of mutex
	if (! *hMutex)
	{
		status = VI_ERROR_SYSTEM_ERROR;
	}
	else
	{
		if (GetLastError() != ERROR_ALREADY_EXISTS) // == ERROR_ALREADY_EXISTS???
			status = 1;
	}
	return status;
}

void _VI_FUNC cross_mutex_close(MUTEX_TYPE hMutex)
{
	if (hMutex)
		CloseHandle(hMutex);
}


ViStatus _VI_FUNC cross_mutex_lock(
								MUTEX_TYPE hMutex,
								ViUInt32 s_tmo)	//Number of milliseconds!!!
{
	int nRet;
	
	if (!hMutex)
		return VI_ERROR_INV_OBJECT;

	nRet = WaitForSingleObject(hMutex, s_tmo*1000);
	if (nRet != WAIT_OBJECT_0 && nRet != WAIT_ABANDONED)
		return VI_ERROR_TMO;
	return 0;
}
	
ViStatus _VI_FUNC cross_mutexes_lock(
								ViUInt32 nMutex,
								MUTEX_TYPE *hMutex,
								ViUInt32 s_tmo)	//Number of milliseconds!!!
{
	ViUInt32 i;
	ViUInt32 nRet;

	if (!hMutex)
		return VI_ERROR_INV_OBJECT;
	
	nRet = WaitForMultipleObjects(nMutex, hMutex, 1, 1000*s_tmo);

	if (nRet == WAIT_TIMEOUT || nRet == WAIT_FAILED)
	{
		for (i=0; i<nMutex; i++)
			ReleaseMutex(hMutex[i]);
		return VI_ERROR_TMO;
	}
	return 0;
}

void _VI_FUNC cross_mutex_unlock(MUTEX_TYPE hMutex)
{
	if (hMutex)
		ReleaseMutex(hMutex);
}

ViUInt32 _VI_FUNC cross_getpid(void)
{
	return (ViUInt32)GetCurrentProcessId();
}

/*cross_gettid - Retrieves the thread identifier of the calling thread*/
ViUInt32 _VI_FUNC cross_gettid(void)
{
	return (ViUInt32)GetCurrentThreadId();
}

int cross_switch_thread(void)
{
	SwitchToThread();
	return 0;
}

HMODULE cross_load_dll(const char * dll_name) 
{
	return LoadLibrary(dll_name);
}

/* cross_free_dll - on success return 0, nonzero in the other cases*/
int cross_free_dll(const HMODULE dll_handle) 
{
	return !FreeLibrary(dll_handle);
}

void * cross_get_dll_sym(const HMODULE dll_handle, const char * sym_name) 
{
	return GetProcAddress(dll_handle, sym_name);
}

// <<< W I N D O W S
#else
// >>> L I N U X

//return 1 if already exist
ViStatus _VI_FUNC cross_mutex_open(
											ViChar *mutexName,
											MUTEX_TYPE *hMutex)
{
	ViStatus status = 0;
	sem_t *hm;
	pshared_mem_t shm = NULL;
	int n;
	
	n = strlen(mutexName);
	if (n == 0 || n > (NAME_MAX - 5) || strchr(&mutexName[1], '/'))
		return VI_ERROR_ABORT; // Name not valid

	*hMutex = (MUTEX_TYPE)cross_map_global((const char *)mutexName, sizeof(sem_t), (void **)&hm, &status);
	if (!*hMutex)
		return VI_ERROR_ALLOC;

	if (status) 
	{ // first init
		if (sem_init(hm, 1, 1) < 0)
		{
			//perror("semaphore initialization"); // TODO: use UNSPY
			cross_unmap_global((void *)hm, mutexName);
			return VI_ERROR_ALLOC;
		}
	}
	return status;
}

void _VI_FUNC cross_mutex_close(MUTEX_TYPE hMutex)
{
	if (hMutex)
	{
		pshared_mem_t psem = (pshared_mem_t)hMutex;
		cross_unmap_global(hMutex, psem->name);
	}
}

ViStatus _VI_FUNC cross_mutex_lock(
								MUTEX_TYPE hMutex,
								ViUInt32 s_tmo)	//Number of milliseconds!!!
{
	pshared_mem_t psem = (pshared_mem_t)hMutex;
	double tEnd = Timer() + s_tmo;
	do {
		errno = 0;
		if (!sem_trywait((sem_t *)psem->mapptr))
		{
			//unFRSpyLog(SPY_MSG, SPY_F_USER6,"\n%s (%s) locked\n", __func__, psem->name);
			return VI_SUCCESS;
		}
		else {
			if (errno != EAGAIN)
				return VI_ERROR_SYSTEM_ERROR;
		}
	} while (Timer() < tEnd);
	//unFRSpyLog(SPY_MSG, SPY_F_USER6,"\n%s (%s) ERROR already locked \n", __func__, psem->name);
	return VI_ERROR_TMO;
}

ViStatus _VI_FUNC cross_mutexes_lock(ViUInt32 nMutex,
									MUTEX_TYPE *hMutex,
									ViUInt32 s_tmo)	//Number of milliseconds!!!
{
	ViUInt32 i;

	if (!hMutex)
		return VI_ERROR_INV_OBJECT;

	ViUInt32 waits = 0, waits_to = 0;
	pshared_mem_t mutex_buf[nMutex];

	for (i = 0; i < nMutex; i++) {
		if (!hMutex[i])
			return VI_ERROR_INV_OBJECT;
		mutex_buf[i] = (pshared_mem_t)hMutex[i];
		waits_to |= (1<<i);
	}

//	errno = 0;
	unsigned int t0 = cross_timer_ms();
	ViUInt32 delta = 0;
	while (waits_to != waits)
	{
		for (i=0; i<nMutex; i++)
		{
			if (!(waits & (1<<i)))
			{
				if (sem_trywait((sem_t *)mutex_buf[i]->mapptr))
					waits |= (1<<i);
			}
		}
		if (waits_to != waits)
		{
			delta = cross_timer_ms() - t0;
			if (delta > s_tmo)
			{
				for (i=0; i<nMutex; i++)
				{
					if (waits & (1<<i))
					{
						sem_post((sem_t *)mutex_buf[i]->mapptr);
					}
				}
				return VI_ERROR_TMO;
			}
		}
	}
	return VI_SUCCESS;
}

void _VI_FUNC cross_mutex_unlock(MUTEX_TYPE hMutex)
{
	if (!hMutex) return;

	int nRet = 0;
	int sval, ret = 0;
	pshared_mem_t psem = (pshared_mem_t )hMutex;

	ret = sem_getvalue((sem_t *)psem->mapptr, &sval);

	if (!sem_getvalue((sem_t *)psem->mapptr, &nRet) && nRet == 0)
	{
		errno = 0;
		sem_post((sem_t *)psem->mapptr);
		//unFRSpyLog(SPY_MSG, SPY_F_USER6,"\n%s (%s) unlocked\n", __func__, psem->name);
		return;
	}
	//unFRSpyLog(SPY_MSG, SPY_F_USER6,"\n%s (%s) unlocked ERROR!\n", __func__, psem->name);
}

/*cross_getpid - Retrieves the process identifier of the calling process*/
ViUInt32 _VI_FUNC cross_getpid(void)
{
	return (ViUInt32)getpid();
}

/*cross_gettid - Retrieves the thread identifier of the calling thread*/
ViUInt32 _VI_FUNC cross_gettid(void)
{
	return (ViUInt32)syscall(SYS_gettid);
}

int cross_switch_thread(void)
{
	pthread_yield();
	return 0;
}


HMODULE cross_load_dll(const char * dll_name)
{
	return dlopen(dll_name, RTLD_LAZY);
}

/* cross_free_dll - on success return 0, nonzero in the other cases*/
int cross_free_dll(const HMODULE dll_handle)
{
	return dlclose(dll_handle);
}

void * cross_get_dll_sym(const HMODULE dll_handle, const char * sym_name)
{
	return dlsym(dll_handle, sym_name);
}

// <<< L I N U X
#endif

