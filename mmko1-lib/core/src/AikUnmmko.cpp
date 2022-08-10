#include "AikUnmmko.h"
#include "Actions.h"
#include "ITestMmko.h"

class AikMmkoInterface::PrivateData
{
public:
    PrivateData();
	~PrivateData() { MKOTEXT( std::string(__FUNCTION__ )); }

public:
    ViSession mSession{}; //Mezonin session ID
    static const int NO_SWD = 0xFF;
    bool baseBus; //current line by MKO

	/* variables for definition initial settings Mezzanine */
	std::string softwareVersion;
	std::string hardwareVersion;
	int16_t resultCode;
	std::string message;
	std::unique_ptr<Common> initActions;
};

AikMmkoInterface::AikMmkoInterface() : m_data(std::make_unique<PrivateData>()),
									   status(VI_SUCCESS)
{
	/*if (initUnmkoUnmbase() < 0) {
		throw std::runtime_error("MMKO::NOT::FOUND");
	}*/
	selfTest();
}

AikMmkoInterface::PrivateData::PrivateData() : baseBus(true),
											   resultCode(0),
											   initActions(std::make_unique<Common>(VI_SUCCESS)
{
	MKOTEXT(std::string(__FUNCTION__ ));
}

AikMmkoInterface::~AikMmkoInterface()
{
    std::cout << "~AikMmkoInterface()" << std::endl;
}

int32_t AikMmkoInterface::selfTest()
{
	/*unmkocheck(m_data->initActions->search()); // search mezzanine MKO
	unmkocheck(unmbase_init(const_cast<char*>(m_data->initActions->resourceName.c_str()), VI_TRUE, VI_TRUE,
			&m_data->initActions->carrierSession)); // make connection with mezzanine carrier
	unmkocheck(unmmko1_init(const_cast<char*>(m_data->initActions->resourceName.c_str()), VI_TRUE, VI_TRUE,
			&session)); // make connection with mezzanine MKO
	getInfoMezzanine();*/
}
int AikMmkoInterface::getInfoMezzanine()
{
	/*unmkocheck(unmmko1_revision_query(session, const_cast<char*>(m_data->softwareVersion.c_str()),
			const_cast<char*>(m_data->hardwareVersion.c_str())));

	printf("Software version: %s\n", m_data->softwareVersion.c_str());
	printf("Hardware version: %s\n", m_data->hardwareVersion.c_str());*/
}



