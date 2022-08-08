#include "AikUnmmko.h"

class AikMmkoInterface::PrivateData
{
public:
    PrivateData();
public:
    ViSession m_session; //Mezonin session ID
    ViStatus m_status;
    static const int NO_SWD = 0xFF;
    bool base_bus; //current line by MKO
private:
};
AikMmkoInterface::PrivateData::PrivateData() : base_bus(true), m_session(0),
                                               m_status(VI_SUCCESS)
{
    std::cout << std::string(__FUNCTION__ ) << std::endl;
}

AikMmkoInterface::AikMmkoInterface()
    : m_data(std::make_unique<PrivateData>())
{
    std::cout << std::string(__FUNCTION__ ) << std::endl;
}
AikMmkoInterface::~AikMmkoInterface()
{
    std::cout << "~AikMmkoInterface()" << std::endl;
}

bool AikMmkoInterface::self_test()
{

}


