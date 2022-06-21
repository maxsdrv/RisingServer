#include "unmmko1_utilities.h"

#include <stdlib.h>
#include <stddef.h>

ViBoolean is_valid_boolean(ViBoolean value) {
    return ((value != VI_FALSE && value != VI_TRUE) ? VI_FALSE : VI_TRUE);
}

ViBoolean is_not_valid_boolean(ViBoolean value) {
    return ((value != VI_FALSE && value != VI_TRUE) ? VI_TRUE : VI_FALSE);
}

ViBoolean is_valid_pointer(void* value) {
    return ((NULL != value) ? VI_TRUE : VI_FALSE);
}

ViBoolean is_not_valid_pointer(void* value) {
    return ((NULL == value) ? VI_TRUE : VI_FALSE);
}

ViBoolean is_valid_session(ViSession value) {
    return ((0 != value) ? VI_TRUE : VI_FALSE);
}

ViBoolean is_not_valid_session(ViSession value) {
    return ((0 == value) ? VI_TRUE : VI_FALSE);
}

ViBoolean is_valid_uint16(ViUInt16 value, ViUInt16 minimal, ViUInt16 maximal) {
    return ((value >= minimal && value <= maximal) ? VI_TRUE : VI_FALSE);
}

ViBoolean is_not_valid_uint16(ViUInt16 value, ViUInt16 minimal, ViUInt16 maximal) {
    return ((value < minimal || value > maximal) ? VI_TRUE : VI_FALSE);
}

ViBoolean is_valid_uint32(ViUInt32 value, ViUInt32 minimal, ViUInt32 maximal) {
    return ((value >= minimal && value <= maximal) ? VI_TRUE : VI_FALSE);
}

ViBoolean is_not_valid_uint32(ViUInt32 value, ViUInt32 minimal, ViUInt32 maximal) {
    return ((value < minimal || value > maximal) ? VI_TRUE : VI_FALSE);
}
