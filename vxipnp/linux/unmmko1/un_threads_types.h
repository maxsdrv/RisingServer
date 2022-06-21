#ifndef UN_THREADS_TYPES_H
#define UN_THREADS_TYPES_H

#if defined(_WIN32)
#include <windows.h>
typedef CRITICAL_SECTION un_mutex_t;
#else
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
typedef pthread_mutex_t un_mutex_t;
#endif

#endif /* UN_THREADS_TYPES_H */
