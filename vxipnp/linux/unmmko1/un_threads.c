#include "internal/un_threads.h"

int un_mutex_init(un_mutex_t* mutex) {
#if defined(NDEBUG) || !defined(PTHREAD_MUTEX_ERRORCHECK)
    return -pthread_mutex_init(mutex, NULL);
#else
    pthread_mutexattr_t attr;
    int err;

    if (pthread_mutexattr_init(&attr))
        abort();

    if (pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK))
        abort();

    err = pthread_mutex_init(mutex, &attr);

    if (pthread_mutexattr_destroy(&attr))
        abort();

    return -err;
#endif
}

void un_mutex_destroy(un_mutex_t* mutex) {
    if (pthread_mutex_destroy(mutex))
        abort();
}

void un_mutex_lock(un_mutex_t* mutex) {
    if (pthread_mutex_lock(mutex))
        abort();
}

int un_mutex_trylock(un_mutex_t* mutex) {
    int err;

    err = pthread_mutex_trylock(mutex);
    if (err) {
        if (err != EBUSY && err != EAGAIN)
            abort();
        return -EBUSY;
    }

    return 0;
}

void un_mutex_unlock(un_mutex_t* mutex) {
    if (pthread_mutex_unlock(mutex))
        abort();
}

void un_sleep(int msec) {
    int sec;
    int usec;

    sec = msec / 1000;
    usec = (msec % 1000) * 1000;
    if (sec > 0)
        sleep(sec);
    if (usec > 0)
        usleep(usec);
}
