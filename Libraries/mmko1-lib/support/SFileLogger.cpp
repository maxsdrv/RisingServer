#include "SFileLogger.h"
#include "SCurDateTime.h"

void SFileLogger::openLogFile(const std::string& fn)
{
	logOut.open(fn, std::ios_base::out);
}
void SFileLogger::closeLogFile()
{
	if (logOut.is_open())
	{
		logOut.close();
	}
}
void SFileLogger::writeToLog(int32_t status, const std::string& msg)
{
	if (logOut.is_open()) {
		logOut << SCurDateTime::getInstance().getCurDateTime()
			   << " Returnes status code with message: "
			   << status << " " << msg << '\n';
	}
}
