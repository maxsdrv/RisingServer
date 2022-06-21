#ifndef UNMMKO1_UTILITIES_H
#define UNMMKO1_UTILITIES_H

#include "internal/unmmko1_device_data.h"
#ifndef __GNUC__
#include "ansi_c.h"
#endif

#define unerror(x) do { \
    if ((status = (x)) < 0) goto Error; \
    else break; \
    } while(1)

#define unfail(x) do { \
    if ((status = (x)) < 0) goto Fail; \
    else break; \
    } while(1)

#define fail_test(status, message_status) do { \
    strcpy(message, message_status); \
    *result = status; \
    goto Fail; \
    } while(1)

ViBoolean is_valid_boolean(ViBoolean value);
ViBoolean is_not_valid_boolean(ViBoolean value);

ViBoolean is_valid_pointer(void* value);
ViBoolean is_not_valid_pointer(void* value);

ViBoolean is_valid_session(ViSession value);
ViBoolean is_not_valid_session(ViSession value);

ViBoolean is_valid_uint16(ViUInt16 value, ViUInt16 minimal, ViUInt16 maximal);
ViBoolean is_not_valid_uint16(ViUInt16 value, ViUInt16 minimal, ViUInt16 maximal);

ViBoolean is_valid_uint32(ViUInt32 value, ViUInt32 minimal, ViUInt32 maximal);
ViBoolean is_not_valid_uint32(ViUInt32 value, ViUInt32 minimal, ViUInt32 maximal);

#endif // UNMMKO1_UTILITIES_H
