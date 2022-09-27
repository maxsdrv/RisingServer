#pragma once

#include <iostream>
#include <functional>
#include <tuple>
#include <boost/format.hpp>
#include <unmmko1.h>



class MMKOErrors : public std::exception
{
public:
	MMKOErrors(const std::string& eM, int eC);
	static std::tuple<std::string, int32_t>
	ErrorMessage(uint32_t session, const std::function<int(uint32_t, int32_t, char*)>& f);
	std::string what();

private:
	std::string errorMsg;
	int errorCode;
	boost::format fmt;
};

