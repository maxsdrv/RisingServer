#include <memory>

#include "Actions.h"
#include "defines.h"

ViStatus CallFunc::error()
{
    auto ret = std::make_shared<CallFunc>();
    if (!ret->initWithFunc(ERROR))
    {
        throw std::runtime_error("ERROR::WITH::CALLBACK::FUNCTION");
    }
    else
    {
        return VI_SUCCESS;
    }
}
void CallFunc::closeDevice()
{
    auto ret = std::make_shared<CallFunc>();
    ret->initWithFunc(CL_DV);
}
bool CallFunc::initWithFunc(const std::string& type)
{
    if (type == "error")
    {
        if (resource_manager_session)
            viClose(resource_manager_session);

        if (VI_SUCCESS == found)
            printf("Mezzanine MKO found at %s on %d position\n", m_resource_name, *m_position);

        return true;
    }
    if (type == "close_device")
    {

        return true;
    }

    return false;
}
