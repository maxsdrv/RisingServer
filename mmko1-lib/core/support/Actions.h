#ifndef MMKO1_LIB_ACTIONS_H
#define MMKO1_LIB_ACTIONS_H

#include <functional>

#include "UpdateCommon.h"

class CallFunc : public UpdateCommon {
public:
    static ViStatus error();
    static void closeDevice();

    CallFunc(const CallFunc& ) = delete;
    CallFunc& operator=(const CallFunc& ) = delete;
    CallFunc(CallFunc&& ) = delete;
    CallFunc& operator=(CallFunc&& ) = delete;

public:
    CallFunc() = default;
    ~CallFunc() = default;

private:
    bool initWithFunc(const std::string& type);
};


#endif //MMKO1_LIB_ACTIONS_H
