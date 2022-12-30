#include "MMKOErrors.h"

void throw_mko_error_if(bool expression, const int& status, const uint32_t& session,
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
std::string format_error_message(int32_t status, const std::string &msg) {
	return str(format("Returns status code %i with message: %s\n") % status % msg);
}
MkoExceptions::MkoExceptions(int32_t status, const std::string &msg) :
		std::runtime_error(format_error_message(status, msg)), m_error(status) {}
MkoExceptions::MkoExceptions(int32_t status, const format& f) :
		std::runtime_error(format_error_message(status, boost::str(f))), m_error(status) {}




