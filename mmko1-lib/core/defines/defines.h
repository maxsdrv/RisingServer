#pragma once

#include <iostream>
#include <boost/format.hpp>

using boost::format;

//bus-line max count
#define BUSLINE_MAX 2

using BUSLINE = unmmko1_bus;
using uint16 = uint16_t;
using uint32 = uint32_t;
using int32 = int32_t;
using int16 = int16_t;

/* Template functions for print message */
template<class TString>
void MKOTEXT(const TString& str) {
	std::cout << format("%1%") %str << '\n';
}
template<class TText, class TChannel, class TError>
void MKOTEXT(const TText& str, TChannel channel, TError error) {
	std::cout << format("%1% %2% %3") %str %channel %error << '\n';
}
/* Variadic template function for print message */
template<class TString, class... Args>
void MKOTEXT(const TString& str, const Args&... args)  {
	std::cout << format("%1% %2%") %str %MKOTEXT(args...);
}

