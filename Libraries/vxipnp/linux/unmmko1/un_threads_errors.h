#ifndef UN_THREADS_ERRORS_H
#define UN_THREADS_ERRORS_H

#include <errno.h>

/*! UN_EBUSY */
/*! Resource busy or locked */
#if defined(EBUSY) && !defined(_WIN32)
# define UN_EBUSY (-EBUSY)
#else
# define UN_EBUSY (-4082)
#endif

#endif /* UN_THREADS_ERRORS_H  */
