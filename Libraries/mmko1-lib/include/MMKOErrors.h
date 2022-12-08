#pragma once

#include <iostream>
#include <boost/format.hpp>
#include <unmmko1.h>

enum class FLAG {
	UNMMKO,
	UNMBASE,
};


using boost::format;

void ThrowErrorIf(bool expression, const uint32_t& session, const int32_t& status, FLAG d);
void ThrowMKOErrorIf(bool expression, const int& status, const format& f);

class MkoExceptions : public std::runtime_error {
private:
	int32_t mError;
public:
	MkoExceptions(int32_t status, const std::string& msg);
	MkoExceptions(int32_t status, const format& f);
	[[nodiscard]] int32_t GetError() const { return mError; }
};


