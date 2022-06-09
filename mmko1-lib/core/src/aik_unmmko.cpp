#include "aik_unmmko.h"
#include "common.h"

class AikMmkoInterface::PrivateData
{
public:
    static const int NO_SWD = 0xFF;
    ViSession *m_session;
private:
};

AikMmkoInterface::AikMmkoInterface(CARD_NUM card, CORE_NUM core) : m_data(std::make_unique<PrivateData>())
{
    m_data->m_session = 0; //example PIMPL work
}
AikMmkoInterface::~AikMmkoInterface()
{
    std::cout << "~AikMmkoInterface()" << std::endl;
}


