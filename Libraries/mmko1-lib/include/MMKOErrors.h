#pragma once

#include <iostream>
#include <boost/format.hpp>
#include <unmmko1.h>
#include "MainBus.h"

using boost::format;

void throw_mko_error_if(bool expression, const int& status, const uint32_t& session,
		const std::string& name);

class MkoExceptions : public std::runtime_error {
private:
	int32_t m_error;
public:
	MkoExceptions(int32_t status, const std::string& msg);
	MkoExceptions(int32_t status, const format& f);
	[[nodiscard]] int32_t get_error() const { return m_error; }
	/* */
	template <typename N, typename S, typename F, typename... Args>
	static auto check_functions(N name, S session, F function, Args... args) {
		auto er_status = function(args...);
		throw_mko_error_if(er_status<0, er_status, session, name);
		return er_status;
	}
	template <typename N, typename S, typename F>
	static auto check_functions(N name, S session, F function) {
		auto er_status = function;
		throw_mko_error_if(er_status<0, er_status, session, name);
		return er_status;
	}
	/* */
};


