#pragma once

#include <iostream>
#include <errno.h>
#include <functional>
#include <tuple>
#include <boost/format.hpp>
#include <unmmko1.h>

enum class ErDevices {
	UNMMKO,
	UNMBASE,
};


using boost::format;

void ThrowErrorIf(bool expression, const uint32_t& session, const int32_t& status, ErDevices d);

class MkoExceptions : public std::runtime_error {
private:
	int32_t mError;
public:
	MkoExceptions(int32_t status, const std::string& msg);

	[[nodiscard]] int32_t GetError() const { return mError; }
};

/* Template functions for print message */
template<class TString>
void MkoText(const TString& str)
{
	std::cout << format("%1%") % str << '\n';
}
template<class TText, class TStatus, class TSession, class TErrorMessage>
void MkoText(const TText& str, TStatus session, TSession status,
		const TErrorMessage& erMsg)
{
	std::cerr << format("%s %i %i %s \n") % str % session % status % erMsg;
}
/* Variadic template function for print message */
template<class TString, class... Args>
void MkoText(const TString& str, const Args& ... args)
{
	std::cerr << str;
	MKOTEXT(args...);
}
