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
    UpdateCommon();
    ~UpdateCommon() { std::cout << "~UpdateCommon()" << std::endl; }
private:
    ViChar m_resource_name[256];
    ViUInt16 *m_position;
    const ViSession m_carrier_session, m_session;

    //search variables mmko
    ViSession resource_manager_session;
    ViStatus found = VI_ERROR_RSRC_NFOUND;
    ViSession device_session;
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
    ViStatus search_unmmko1();
public:
    int unmko_check(int32_t status);
    int unmbase_check(int32_t status);
    void error() const;
    void close_device() const;
    void print_message(ViUInt32 messages_count, unmmko1_message* messages) const;
};















