#pragma once

#include <iostream>
#include <boost/format.hpp>

#include "MMKOErrors.h"
#include "Actions.h"

using boost::format;

using uint16 = uint16_t;
using uint32 = uint32_t;
using int32 = int32_t;
using int16 = int16_t;

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
/* Function for validation C-functions from unmmko1.h */
template<class TObjectName, class TSession, class TFunc>
int32_t MkoValidation(const TObjectName& objectName, TSession session, const TFunc& func)
{
	if (func < 0)
	{
		auto err = MMKOErrors::ErrorMessage(session, &unmmko1_error_message);
		std::cerr << objectName  << " " << format("%s %i") % std::get<0>(err) % std::get<1>(err);
	}
	return func;
}




