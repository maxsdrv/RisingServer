#pragma once

#include <iostream>

class MkoErrors : public std::exception {
public:
	explicit MkoErrors(std::string msg, int  error, std::string title = "");
	std::string what();
private:
	std::string errorMessage;
	int errorCode;
	std::string sTitle;
};

