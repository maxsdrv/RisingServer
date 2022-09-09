#pragma once

#include <iostream>

class MkoErrors : public std::exception {
public:
	explicit MkoErrors(std::string  msg, int32_t status = 0, std::string  error = "");
	std::string what();
private:
	std::string textMsg;
	int32_t mStatus;
	std::string error;
};

