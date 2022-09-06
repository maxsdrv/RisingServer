#pragma once

#include <iostream>
#include <boost/format.hpp>

using boost::format;
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

