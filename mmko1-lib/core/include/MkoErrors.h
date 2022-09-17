#pragma once

#include <iostream>
#include <functional>
#include <tuple>
#include <boost/format.hpp>
#include <unmmko1.h>

#include "defines.h"

class MkoErrors : public std::exception {
public:
	MkoErrors(const std::string& eM, int eC);
	static std::tuple<std::string, int32>
	ErrorMessage(uint32 session, const std::function<int(uint32, int32, char*)>& f);
	std::string what();
private:
	std::string errorMsg;
	int errorCode;
	boost::format fmt;
};

