#include "MkoErrors.h"
#include "defines.h"
#include "Actions.h"


MkoErrors::MkoErrors(const std::string& eM, int eC) : errorMsg(eM), errorCode(eC)
{
	fmt = boost::format("%s %i \n") % eM % eC;
}

std::string MkoErrors::what()
{
	return fmt.str();
}

int32 MkoErrors::ErrorMessage(std::function<int(uint32, int32, char *)> f) {
}









