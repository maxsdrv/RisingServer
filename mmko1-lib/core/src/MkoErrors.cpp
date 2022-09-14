#include "MkoErrors.h"

#include <boost/format.hpp>

MkoErrors::MkoErrors(std::string msg, int error, std::string title) :
						errorMessage(std::move(msg)),
						errorCode(error),
						sTitle(std::move(title)) { }

std::string MkoErrors::what()
{
	auto tmpStr = boost::format("%s %i %s \n") % errorMessage % errorCode % sTitle;
	return tmpStr.str();
}

