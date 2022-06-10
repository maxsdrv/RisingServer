/* It is wrapper class based on common.h which wrote on C.  */
#pragma once

#include <iostream>
#include <boost/format.hpp>
#include <visa.h>
#include <unmbase.h>
#include <unmmko1.h>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
int key_pressed() {
    return _kbhit();
}
#else
#include <unistd.h>
int key_pressed() {
    return 0;
}
void Sleep(int msec) {
    int sec;
    int usec;

    sec = msec / 1000;
    usec = (msec % 1000) * 1000;
    if (sec > 0)
        sleep(sec);
    if (usec > 0)
        usleep(usec);
}
#endif

using boost::format;

class UpdateCommon
{
public:
    UpdateCommon() = default;
    ~UpdateCommon() { std::cout << "~UpdateCommon()" << std::endl; }
private:
    static ViChar m_resource_name[256];
    static const ViUInt16 m_position = 0;
    static const ViSession m_carrier_session = 0, m_session = 0;
private:
    /* methods for checking errors */
    /* Check errors, when called function of Mezonin Driver MKO */
    void process_unmmko1_error(ViSession session, ViStatus status);
    /* Check erros, when called function of Mezonin carrier */
    void process_unmbase_error(ViSession session, ViStatus status);
    /* Find mezonin MKO
     * \param resource_name Address Mezonin Carrier, which found MKO mezonin
     * \param position MKO Mezonin position on Mezonin Carrier
     * \returns VI_TRUE in case, if found MKO mezonin, VI_FALSE - else */
    ViStatus search_unmmko1(ViChar resource_name, ViUInt16 *position);
    auto error(ViSession _res_manager_session, ViStatus _found) const;
public:
    int unmko_check(int32_t status);
    int unmbase_check(int32_t status);
};

auto UpdateCommon::error(ViSession _res_manager_session, ViStatus _found) const
{
    auto res =  [=]()
    {
        if (_res_manager_session)
            viClose(_res_manager_session);
        if (VI_SUCCESS == _found)
            std::cout << format("Mezzanine MKO found at %s on %i position") % m_resource_name % m_position;
    };

    return res;
}

void UpdateCommon::process_unmmko1_error(ViSession session, ViStatus status)
{
    ViChar str[256];
    unmmko1_error_message(session, status, str);
    std::cout << format("Returns status code %i with message %s\n")  % status % str;
}
void UpdateCommon::process_unmbase_error(ViSession session, ViStatus status)
{
    ViChar str[256];
    unmbase_error_message(session, status, str);
    std::cout << format("Returns status code %i with message %s\n") % status % str;
}
ViStatus UpdateCommon::search_unmmko1(ViChar resource_name, ViUInt16 *position)
{
    ViSession resource_manager_session = 0;
    std::string search_pattern = "?*[0-9]?*::?*::INSTR";
    ViFindList find_list;
    ViStatus found = VI_ERROR_RSRC_NFOUND;
    ViUInt32 index = 0, count = 0;
    ViSession device_session = 0, carrier_session = 0;
    ViUInt16 interface_type = 0;
    ViInt16 mezzanine_number = 1;
    char address[256];

    //Open session to VISA
    if (viOpenDefaultRM(&resource_manager_session) < 0)
        error(resource_manager_session, found);

    return 0;
}
int UpdateCommon::unmbase_check(int32_t status)
{
    return 0;
}
int UpdateCommon::unmko_check(int32_t status)
{
    return 0;
}













