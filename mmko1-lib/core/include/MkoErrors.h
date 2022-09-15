#pragma once

#include <iostream>
#include <functional>
#include <boost/format.hpp>

class MkoErrors : public std::exception {
public:
	MkoErrors(const std::string& eM, int eC);

	std::string what();
private:
	std::string errorMsg;
	int errorCode;
	boost::format fmt;
};

