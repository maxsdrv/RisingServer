#ifndef MMKO1_LIB_ACTIONS_H
#define MMKO1_LIB_ACTIONS_H

#include "UpdateCommon.h"

namespace CallFunc
{
    void error(ViSession _res_manager_session, ViStatus _found, const std::pair<std::string, ViUInt16*>& format)
    {
        if (_res_manager_session)
            viClose(_res_manager_session);
    }
    void close_device(ViSession _dev_session, ViStatus _found)
    {
        viClose(_dev_session);
        if (VI_SUCCESS == _found)
            return;
    }
}

#endif //MMKO1_LIB_ACTIONS_H
