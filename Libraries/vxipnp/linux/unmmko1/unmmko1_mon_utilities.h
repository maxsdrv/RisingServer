#ifndef UNMMKO1_MON_UTILITIES_H
#define UNMMKO1_MON_UTILITIES_H

#include "unmmko1_internal.h"

//! Разбор слов монитора.
//! \param[in] words Очередь с новыми словами с монитора.
//! \param[in] accumulator Аккумулятор слов, который используется для накопления слов в процессе разбора.
//! \param[out] messages Очередь, в которую помещаются разобранные сообщения.
void unmmko1_parse_words(un_queue* words, accumulator_t* accumulator, un_queue* messages);

//! Фильтрация сообщений по заданным правилам.
//! \param[in] messages Очередь сообщений.
//! \param[in] filter_rules Правила фильтрации сообщений.
//! \param[out] filtered_messages Отфильтрованная очередь сообщений.
void unmmko1_filter_messages(un_queue* messages, filter_rules_t* filter_rules, un_queue* filtered_messages);

#endif // UNMMKO1_MON_UTILITIES_H
