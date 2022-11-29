#ifndef UN_THREADS_H
#define UN_THREADS_H

#include "internal/un_threads_types.h"
#include "internal/un_threads_errors.h"

/* Work with mutexes */
int  un_mutex_init(un_mutex_t* handle);
void un_mutex_destroy(un_mutex_t* handle);
void un_mutex_lock(un_mutex_t* handle);
void un_mutex_unlock(un_mutex_t* handle);

/* Miscellaneous utilities */
void un_sleep(int msec);

#endif /* UN_THREADS_H */
