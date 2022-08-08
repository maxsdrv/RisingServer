#include "SCurDateTime.h"

std::string SCurDateTime::getCurDateTime()
{
	auto cur = std::chrono::system_clock::now();
	time_t time = std::chrono::system_clock::to_time_t(cur);
	char buf[64] { 0 };
	ctime_r(&time, buf);
	buf[strlen(buf) - 1] = '\0';

	return std::string{buf};
}
void SCurDateTime::start()
{
	m_beg = clock_t::now();
}
void SCurDateTime::saveTime()
{
	storage_time.push_back(std::chrono::duration_cast<second_t>(clock_t::now() -
	m_beg).count());
}
