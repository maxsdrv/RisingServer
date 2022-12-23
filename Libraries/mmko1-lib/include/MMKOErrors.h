#pragma once

#include <iostream>
#include <boost/format.hpp>
#include <unmmko1.h>
#include "MainBus.h"

using boost::format;

void ThrowMKOErrorIf(bool expression, const int& status, const uint32_t& session,
		const std::string& name);

class MkoExceptions : public std::runtime_error {
private:
	int32_t mError;
public:
	MkoExceptions(int32_t status, const std::string& msg);
	MkoExceptions(int32_t status, const format& f);
	[[nodiscard]] int32_t GetError() const { return mError; }
	/* */
	template <typename N, typename S, typename F, typename... Args>
	static auto CheckFunctions(N name, S session, F function, Args... args) {
		auto erStatus = function(args...);
		ThrowMKOErrorIf(erStatus < 0, erStatus, session, name);
		return erStatus;
	}
	template <typename N, typename S, typename F>
	static auto CheckFunctions(N name, S session, F function) {
		auto erStatus = function;
		ThrowMKOErrorIf(erStatus < 0, erStatus, session, name);
		return erStatus;
	}
	/* */
};


