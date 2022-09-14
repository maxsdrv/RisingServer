#pragma once

#include <iostream>
#include <boost/format.hpp>

using boost::format;


using uint16 = uint16_t;
using uint32 = uint32_t;
using int32 = int32_t;
using int16 = int16_t;

/* Template functions for print message */
template<class TString>
void MKOTEXT(const TString& str) {
	std::cout << format("%1%") %str << '\n';
}
template<class TText, class TStatus, class TSession, class TErrorMessage>
void MKOTEXT(const TText& str, TStatus session, TSession status, const TErrorMessage& erMsg) {
	std::cerr << format("%s %i %i %s \n") % str % session % status % erMsg;
}
/* Variadic template function for print message */
template<class TString, class... Args>
void MKOTEXT(const TString& str, const Args&... args)  {
	std::cerr << str;
	MKOTEXT(args...);
}

