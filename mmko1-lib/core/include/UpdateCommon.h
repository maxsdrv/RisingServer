/* It is wrapper class based on common.h which wrote on C. */

#pragma once

#include <iostream>
#include <boost/format.hpp>
#include <visa.h>

#include "aik_unmmko.h"

using boost::format;

class UpdateCommon
{
public:
    UpdateCommon(const UpdateCommon&) = delete;
    UpdateCommon(UpdateCommon&&) = delete;
    UpdateCommon& operator=(const UpdateCommon&) = delete;
    UpdateCommon& operator=(UpdateCommon&&) = delete;

    UpdateCommon();
    ~UpdateCommon() { std::cout << "~UpdateCommon()" << std::endl; }
private:
    std::pair<std::string, ViUInt16*> _format; // the pair of resource_name and position
    const ViSession m_carrier_session, m_session;

    //search variables mmko
    ViSession resource_manager_session;
    ViStatus found = VI_ERROR_RSRC_NFOUND;
    ViSession device_session;

private:
    /* methods for checking errors */
    /* Check errors, when called function of Mezonin Driver MKO */
    void processUnmmko1Error(ViStatus status) const;
    /* Check erros, when called function of Mezonin carrier */
    void processUnmbaseError(ViStatus status) const;
    /* Find mezonin MKO
     * \param resource_name Address Mezonin Carrier, which found MKO mezonin
     * \param position MKO Mezonin position on Mezonin Carrier
     * \returns VI_TRUE in case, if found MKO mezonin, VI_FALSE - else */
    ViStatus search_unmmko1();
public:
    inline ViStatus unmkoCheck(ViStatus status)
    {
        if (status == 0 || status > 0)
        {
            std::cout << __FILE__ << __LINE__ << __FUNCTION__ << '\n';
        }
        else processUnmmko1Error(status);

        return status;
    }
    inline ViStatus unmbaseCheck(ViStatus status)
    {
        if (status == 0 || status > 0)
        {
            std::cout << __FILE__ << __LINE__ << __FUNCTION__ << '\n';
        }
        else processUnmbaseError(status);

        return status;
    }

    static void printMessage(ViUInt32 messages_count, unmmko1_message* messages) ;
};















