#pragma once

#include <iostream>
#include <functional>
#include <boost/format.hpp>
#include <unmmko1.h>

#include "defines.h"

class MkoErrors : public std::exception {
public:
	MkoErrors(const std::string& eM, int eC);
    static int32 ErrorMessage(std::function<int(uint32, int32, char*)> f);
	std::string what();
private:
	std::string errorMsg;
	int errorCode;
	boost::format fmt;
};

