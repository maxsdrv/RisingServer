#include "MMKOErrors.h"

void ThrowMKOErrorIf(bool expression, const int& status, const uint32_t& session,
		const std::string& name) {
	if (expression) {
		char str[256];
		unmmko1_error_message(session, status, str);
		std::string exp{};
		format f(exp.append("When (") + name + (") ") + str + (" occurred!\n"));
		throw (MkoExceptions(status, f));
	}
	else
		return;
}
std::string FormatErrorMessage(int32_t status, const std::string &msg) {
	return str(format("Returns status code %i with message: %s\n") % status % msg);
}
MkoExceptions::MkoExceptions(int32_t status, const std::string &msg) :
	std::runtime_error(FormatErrorMessage(status, msg)), mError(status) {}
MkoExceptions::MkoExceptions(int32_t status, const format& f) :
	std::runtime_error(FormatErrorMessage(status, boost::str(f))), mError(status) {}




