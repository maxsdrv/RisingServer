#pragma once

#include <iostream>
#include <boost/format.hpp>

using boost::format;
/* Template functions for print message */
template<class TString>
TString MKOTEXT(const TString& str) {
	return format("%1%") %str;
}
/* Variadic template function for print message */
template<class TString, class... Args>
void MKOTEXT(const TString& str, const Args&... args)  {
	format("%1%") %str;
	MKOTEXT(str, args...);
}

