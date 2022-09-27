#include "MMKOErrors.h"
#include "defines.h"
#include "Actions.h"

MMKOErrors::MMKOErrors(const std::string& eM, int eC)
		:errorMsg(eM), errorCode(eC)
{
	fmt = boost::format("%s %i \n") % eM % eC;
}

std::string MMKOErrors::what()
{
	return fmt.str();
}

std::tuple<std::string, int32> MMKOErrors::ErrorMessage(uint32 session,
		const std::function<int(uint32, int32, char*)>& f)
{
	char buf[256];
	f(session, Common::getInstance().status, buf);
	return std::make_tuple(buf, Common::getInstance().status);
}










