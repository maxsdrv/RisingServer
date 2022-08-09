#pragma once


/* macro print debug info */
#define MKOTEXT(msg) std::cout << msg << '\n';

//! Макрос для проверки ошибок при работе с UNMKO
#define unmkocheck(f) if ((status = (f)) < 0) { \
    printf("%s %d %s ", __FILE__, __LINE__, __FUNCTION__); \
    process_unmmko1_error(session, status); return status; } \
    else

//! Макрос для проверки ошибок
#define unmbasecheck(f) if ((status = (f)) < 0) { \
    printf("%s %d %s ", __FILE__, __LINE__, __FUNCTION__); \
    process_unmbase_error(carrier_session, status); return status; } \
    else