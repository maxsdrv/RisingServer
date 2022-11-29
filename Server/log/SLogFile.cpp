#include "SLogFile.h"

void SLogFile::open_log_file(const std::string &file)
{
    mlog_out.open(file, std::ios_base::out);
}

void SLogFile::close_log_file()
{
    if (mlog_out.is_open())
    {
        mlog_out.close();
    }
}

void SLogFile::write_to_log(const std::string &info)
{
    if (mlog_out.is_open())
    {
        mlog_out << QDateTime::currentDateTime().toString("yyyy.MM.dd").toStdString()
                 << " "
                 << QTime::currentTime().toString("hh:mm:ss.zzz ").toStdString()
                 << " " << info << std::endl;
    }
}