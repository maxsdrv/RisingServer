#include <memory>

#include "Actions.h"

CallFunc *CallFunc::create(const std::function<void()> &func) {
    CallFunc *ret = new (std::nothrow) CallFunc();

    if (ret && ret->initWithFunction(func))
    {
        ret->autorelease();
        return ret;
    }


    return nullptr;
}

bool CallFunc::initWithFunction(const std::function<void()> &func) {
    _function = func;
    return true;
}
