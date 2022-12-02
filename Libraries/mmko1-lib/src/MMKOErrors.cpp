#include "MMKOErrors.h"
#include "unmbase.h"

void ThrowErrorIf(bool expression, const uint32_t& session, const int32_t& status, ErDevices d)
{
	if (expression)
	{
		char str[256];
		if (d == ErDevices::UNMBASE) {
			unmbase_error_message(session, status, str);
			throw(MkoExceptions(status, str));
		}
		else if (d == ErDevices::UNMMKO) {
			unmmko1_error_message(session, status, str);
			throw(MkoExceptions(status, str));
		}
	}
	
}
std::string FormatErrorMessage(int32_t status, const std::string &msg)
{
	return str(format("Returns status code %i with message: %s/n") % status % msg);
}

MkoExceptions::MkoExceptions(int32_t status, const std::string &msg) : std::runtime_error(FormatErrorMessage(status, msg)), mError(status) {}




