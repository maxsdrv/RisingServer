#ifndef UNMMKO1_REQUEST_H
#define UNMMKO1_REQUEST_H

#include "unmmko1.h"

//! Адрес запроса
#define REQUEST_ADDRESS 4
//! Размер запроса
#define REQUEST_SIZE 30
//! Размер блока данных в запросе
#define REQUEST_DATA_SIZE 27
//! Значение флага инкремента в запросе
#define REQUEST_INCREMENT 1

//! Одиночный запрос
typedef struct _unmmko1_request {
    ViUInt16 new_data;
    ViUInt16 data[REQUEST_DATA_SIZE];
    ViUInt16 command;
    ViUInt16 counter;
} unmmko1_request_data;

//! Адрес ответа
#define RESPONSE_ADDRESS 4
//! Размер ответа на запрос
#define RESPONSE_SIZE REQUEST_SIZE

//! Одиночный ответ
typedef ViUInt16 unmmko1_response_data[RESPONSE_SIZE];

//! Выполнение запроса request и получение ответа response
ViStatus execute_request(ViSession session, unmmko1_request_data* request, unmmko1_response_data* response);

//! Обнуление запроса
void clear_request(unmmko1_request_data* request);

//! Обнуление ответа
void clear_response(unmmko1_response_data* response);

#endif // UNMMKO1_REQUEST_H
