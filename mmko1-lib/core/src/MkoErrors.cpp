#include "MkoErrors.h"
#include "defines.h"


MkoErrors::MkoErrors(const std::string& eM, int eC) : errorMsg(eM), errorCode(eC)
{
	fmt = boost::format("%s %i \n") % eM % eC;
}
std::string MkoErrors::what()
{
	return fmt.str();
}
