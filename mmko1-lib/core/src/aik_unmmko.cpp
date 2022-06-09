#include "aik_unmmko.h"
#include "common.h"

class AikMmkoInterface::PrivateData
{
public:
    static const int NO_SWD = 0xFF;
private:
    //current line by MKO
    bool base_bus;
};

AikMmkoInterface::AikMmkoInterface(CARD_NUM card, CORE_NUM core)
    : m_data(std::make_unique<PrivateData>())
{
    /* m_data->m_session = 0; //example PIMPL work */

}
AikMmkoInterface::~AikMmkoInterface()
{
    std::cout << "~AikMmkoInterface()" << std::endl;
}

bool AikMmkoInterface::self_test()
{
    ViStatus status = VI_SUCCESS;
    std::string software_version;
    std::string hardware_version;
    int16_t result_code;
    std::string message;


    return false;
}


