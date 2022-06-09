/* It is wrapper class based on common.h which wrote on C.  */
#pragma once

#include <iostream>
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


class UpdateCommon
{
public:
    UpdateCommon() = default;
    ~UpdateCommon() { std::cout << "~UpdateCommon()" << std::endl; }
    /* methods for checking errors */
    /* Check errors, when called function of Mezonin Driver MKO */
    void process_unmmko1_error(ViSession session, ViStatus status);
    /* Check erros, when called function of Mezonin carrier */
    void process_unmbase_error(ViSession session, ViStatus status);
    /* Find mezonin MKO
     * \param resource_name Address Mezonin Carrier, which found MKO mezonin
     * \param position MKO Mezonin position on Mezonin Carrier
     * \returns VI_TRUE in case, if found MKO mezonin, VI_FALSE - else */
    ViStatus search_unmmko1(std::string resource_name, ViUInt16 *position);

private:
    static ViChar resource_name[256];
    static ViUInt16 position;
    static ViSession carrier_session, session;
};

void UpdateCommon::process_unmmko1_error(ViSession session, ViStatus status)
{
    ViChar str[256];
    unmmko1_error_message(session, status, str);

}












