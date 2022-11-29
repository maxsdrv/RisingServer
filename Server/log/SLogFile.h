#pragma once

#include <QTime>

#include <string>
#include <fstream>

class SLogFile
{
public:
    static SLogFile& get_instance()
    {
        static SLogFile the_instance;
        return the_instance;
    }
    void open_log_file(const std::string& file);
    void close_log_file();
    void write_to_log(const std::string& info);
private:
    std::ofstream mlog_out;
private:
    SLogFile() = default;
    ~SLogFile() = default;
    SLogFile(const SLogFile&) = delete;
    SLogFile(SLogFile&&) = delete;
    SLogFile& operator=(const SLogFile&) = delete;
    SLogFile& operator=(SLogFile&&) = delete;
};


