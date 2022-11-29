#include "unmmko1_mon_utilities.h"
#include <stdio.h>

static const ViUInt16 MANCHESTER_SEQUENCE_ERROR = 0x0001;       //!< Ошибка манчестера в одном из слов последовательности
static const ViUInt16 CONTINUITY_SEQUENCE_ERROR = 0x0002;       //!< Ошибка непрерывности последовательности слов
static const ViUInt16 WORD_COUNT_SEQUENCE_ERROR = 0x0004;       //!< Ошибка количества непрерывно передаваемых слов (передача дольше 800 мкс)

void update_gap_for_sequences(accumulator_t* accumulator, milstd1553_word_s* word);
void append_word_to_sequences(accumulator_t* accumulator, milstd1553_word_s* word);
void update_gap_using_current_time(accumulator_t* accumulator);

sequence_s* get_last_sequence(sequence_s* s) {
    if (0 != s[2].count)
        return &s[2];
    else if (0 != s[1].count)
        return &s[1];
    else if (0 != s[0].count)
        return &s[0];
    else
        return NULL;
}

size_t get_sequence_count(sequence_s* s) {
    if (s[2].count > 0 && s[2].gap > 0)
        return 3;
    if (s[1].count > 0 && s[1].gap > 0)
        return 2;
    if (s[0].count > 0 && s[0].gap > 0)
        return 1;
    else
        return 0;
}

message_format_enum detect_format(sequence_s* sequence) {
    if (0 == (sequence->types & 1)) {
        return f_rubbish;
    }
    if (1 == (sequence->types & 3)) {
        // Разбираем слово по частям
        int terminal_address = (sequence->values[0] & 0xf800) >> 11;         //!< Поле "Адрес ОУ"
        int transmit_receive = (sequence->values[0] & 0x0400) ? 1 : 0;       //!< Разряд "Приём/Передача" (0/1)
        int terminal_subaddress = (sequence->values[0] & 0x03e0) >> 5;       //!< Поле "Подадрес/Режим управления"
        int data_count = sequence->values[0] & 0x001f;                       //!< Поле "Число слов данных/Код команды"

        // Если адрес ОУ групповой, то это возможно форматы 7-10
        if (31 == terminal_address) {
            // Если подадрес 0b00000 или 0b11111, то это возможно форматы 9-10
            if (0 == terminal_subaddress || 31 == terminal_subaddress) {
                // Если команда приёма, то это возможно формат 10
                if (0 == transmit_receive) {
                    // Если код команды управления совпадает с разрешёнными к использованию, то точно формат 10
                    if (17 == data_count || 20 == data_count || 21 == data_count)
                        return f10;
                }
                // Если команда передачи, то это возможно формат 9
                else if (1 == transmit_receive) {
                    // Если код команды управления совпадает с разрешёнными к использованию, то точно формат 9
                    if (1 == data_count || (3 <= data_count && 8 >= data_count))
                        return f9;
                }
            }
            // Иначе, если это не команда управления, то возможно форматы 7-8
            else {
                // Если команда приёма и второго командного слова нет, то это формат 7
                if (0 == transmit_receive) {
                    return f7;
                }
            }
        }
        // Иначе - адрес негрупповой команды, то есть возможно форматы 1-6
        else {
            // Если подадрес 0b00000 или 0b11111, то это возможно форматы 4-6
            if (0 == terminal_subaddress || 31 == terminal_subaddress) {
                // Если команда приёма, то это возможно формат 6
                if (0 == transmit_receive) {
                    // Если код команды управления совпадает с разрешёнными к использованию, то точно формат 6
                    if (17 == data_count || 20 == data_count || 21 == data_count)
                        return f6;
                }
                // Если команда передачи, то это возможно форматы 4-5
                else if (1 == transmit_receive) {
                    // Если код команды управления от 0 до 8, то точно формат 4
                    if (0 <= data_count && 8 >= data_count)
                        return f4;
                    // Если код команды управления 16, 18 или 19, то точно формат 5
                    else if (16 == data_count || 18 == data_count || 19 == data_count)
                        return f5;
                }
            }
            // Иначе, если это не команда управления, то возможно форматы 1-3
            else {
                // Если команда передачи, то это формат 2
                if (1 == transmit_receive)
                    return f2;
                // Если команда приёма и второго командного слова нет, то это формат 1
                else
                    return f1;
            }
        }
        return f_unknown;
    }
    else {
        // Разбираем слова по частям
        int terminal_address_1 = (sequence->values[0] & 0xf800) >> 11;       //!< Поле "Адрес ОУ"
        int transmit_receive_1 = (sequence->values[0] & 0x0400) ? 1 : 0;     //!< Разряд "Приём/Передача" (0/1)
        int terminal_subaddress_1 = (sequence->values[0] & 0x03e0) >> 5;     //!< Поле "Подадрес/Режим управления"
        int data_count = sequence->values[0] & 0x001f;                       //!< Поле "Число слов данных/Код команды"

        int terminal_address_2 = (sequence->values[1] & 0xf800) >> 11;       //!< Поле "Адрес ОУ"
        int transmit_receive_2 = (sequence->values[1] & 0x0400) ? 1 : 0;     //!< Разряд "Приём/Передача" (0/1)
        int terminal_subaddress_2 = (sequence->values[1] & 0x03e0) >> 5;     //!< Поле "Подадрес/Режим управления"
        int data_count_2 = sequence->values[1] & 0x001f;                     //!< Поле "Число слов данных/Код команды"

        // Выбираем между форматами 3 и 8
        if (31 == terminal_address_1 && 0 == transmit_receive_1 && 0 != terminal_subaddress_1 && 31 != terminal_subaddress_1 &&
            31 != terminal_address_2 && 1 == transmit_receive_2 && 0 != terminal_subaddress_2 && 31 != terminal_subaddress_2 && data_count == data_count_2)
            return f8;

        if (31 != terminal_address_1 && 0 == transmit_receive_1 && 0 != terminal_subaddress_1 && 31 != terminal_subaddress_1 &&
            31 != terminal_address_2 && 1 == transmit_receive_2 && 0 != terminal_subaddress_2 && 31 != terminal_subaddress_2 && data_count == data_count_2)
            return f3;

        return f_unknown;
    }
}

void initialize_message(unmmko1_message* message) {
    size_t data_index = 0;

    message->timestamp_low = 0;
    message->timestamp_high = 0;
    message->activity = 0;
    message->error = UNMMKO1_MSG_ERR_OK;

    message->command.activity = 0;
    message->command.command_word_1 = 0;
    message->command.command_word_2 = 0;
    message->command.data_words_count = 0;
    for (data_index = 0; data_index < 32; ++data_index)
        message->command.data_words[data_index] = 0;

    message->response_1.status_word = 0;
    message->response_1.data_words_count = 0;
    for (data_index = 0; data_index < 32; ++data_index)
        message->response_1.data_words[data_index] = 0;

    message->response_2.status_word = 0;
    message->response_2.data_words_count = 0;
    for (data_index = 0; data_index < 32; ++data_index)
        message->response_2.data_words[data_index] = 0;
}

void init_sequence_data(sequence_s* s) {
    size_t i = 0;
    s->timestamp = 0;
    s->count = 0;
    s->types = 0;
    for (; i < 40; ++i)
        s->values[i] = 0;
    s->errors = 0;
    s->gap = 0;
}

void remove_sequences(sequence_s* sequences, size_t count) {
    switch (count) {
        case 1:
            sequences[0] = sequences[1];
            sequences[1] = sequences[2];
            init_sequence_data(&sequences[2]);
            break;
        case 2:
            sequences[0] = sequences[2];
            init_sequence_data(&sequences[1]);
            init_sequence_data(&sequences[2]);
            break;
        case 3:
            init_sequence_data(&sequences[0]);
            init_sequence_data(&sequences[1]);
            init_sequence_data(&sequences[2]);
            break;
    }
}

void fill_command_in_message(sequence_s* sequence, unmmko1_bus bus, unmmko1_message* message) {
    size_t index = 1;

    message->timestamp_low = sequence->timestamp & 0xffffffff;
    message->timestamp_high = (sequence->timestamp >> 32);
    message->activity = (UNMMKO1_BUS_A == bus) ? UNMMKO1_MSG_ACT_BUS_A : UNMMKO1_MSG_ACT_BUS_B;

    if (1 == (sequence->types & 3)) {
        message->activity |= UNMMKO1_MSG_ACT_CWD_1;
        message->command.command_word_1 = sequence->values[0];
        if (sequence->count > 1) {
            message->command.data_words_count = (ViUInt16)(sequence->count - 1);
            for (index = 1; index < sequence->count; ++index)
                message->command.data_words[index - 1] = sequence->values[index];
        }
    }
    if (3 == (sequence->types & 3)) {
        message->activity |= UNMMKO1_MSG_ACT_CWD_1;
        message->command.command_word_1 = sequence->values[0];
        message->activity |= UNMMKO1_MSG_ACT_CWD_2;
        message->command.command_word_2 = sequence->values[1];
        if (sequence->count > 2) {
            message->command.data_words_count = (ViUInt16)(sequence->count - 2);
            for (index = 2; index < sequence->count; ++index)
                message->command.data_words[index - 2] = sequence->values[index];
        }
    }

    if (sequence->errors & MANCHESTER_SEQUENCE_ERROR)
        message->error |= UNMMKO1_MSG_ERR_MANCHECTER;
    if (sequence->errors & CONTINUITY_SEQUENCE_ERROR)
        message->error |= UNMMKO1_MSG_ERR_PROTOCOL;
    if (sequence->errors & WORD_COUNT_SEQUENCE_ERROR)
        message->error |= UNMMKO1_MSG_ERR_DATA_COUNT;

    message->command.activity = message->activity;
}

size_t get_data_count(ViUInt16 word_value) {
    size_t data_count = word_value & 0x001f;
    return (0 != data_count) ? data_count : 32;
}

size_t get_rt_address(ViUInt16 word_value) {
    return word_value & 0xf800;
}

bool has_any_error_bit(ViUInt16 word_value) {
    return word_value & 0x0505;
}

void fill_response_1_in_message(sequence_s* sequence, unmmko1_message* message) {
    size_t index = 1;

    message->activity |= UNMMKO1_MSG_ACT_SWD_1;
    message->response_1.status_word = sequence->values[0];

    if (sequence->count > 1) {
        message->response_1.data_words_count = (ViUInt16)(sequence->count - 1);
        for (index = 1; index < sequence->count; ++index)
            message->response_1.data_words[index - 1] = sequence->values[index];
    }

    if (1 != sequence->types)
        message->error |= UNMMKO1_MSG_ERR_MANCHECTER;
    if (sequence->errors & MANCHESTER_SEQUENCE_ERROR)
        message->error |= UNMMKO1_MSG_ERR_MANCHECTER;
    if (sequence->errors & CONTINUITY_SEQUENCE_ERROR)
        message->error |= UNMMKO1_MSG_ERR_PROTOCOL;
    if (sequence->errors & WORD_COUNT_SEQUENCE_ERROR)
        message->error |= UNMMKO1_MSG_ERR_DATA_COUNT;
}

void fill_response_2_in_message(sequence_s* sequence, unmmko1_message* message) {
    size_t index = 1;

    message->activity |= UNMMKO1_MSG_ACT_SWD_2;
    message->response_2.status_word = sequence->values[0];

    if (sequence->count > 1) {
        message->response_2.data_words_count = (ViUInt16)(sequence->count - 1);
        for (index = 1; index < sequence->count; ++index)
            message->response_2.data_words[index - 1] = sequence->values[index];
    }

    if (1 != sequence->types)
        message->error |= UNMMKO1_MSG_ERR_MANCHECTER;
    if (sequence->errors & MANCHESTER_SEQUENCE_ERROR)
        message->error |= UNMMKO1_MSG_ERR_MANCHECTER;
    if (sequence->errors & CONTINUITY_SEQUENCE_ERROR)
        message->error |= UNMMKO1_MSG_ERR_PROTOCOL;
    if (sequence->errors & WORD_COUNT_SEQUENCE_ERROR)
        message->error |= UNMMKO1_MSG_ERR_DATA_COUNT;
}

void analyze_1_sequence(sequence_s* sequences, unmmko1_bus bus, accumulator_t* accumulator, un_queue* messages) {
    // В разборе одной последовательности выделяются два случая:
    //  1. Временная задержка любая
    //        В этом случае мы можем сформировать законченные сообщения для форматов 7, 9 и 10
    sequence_s sequence_1 = sequences[0];
    switch (detect_format(&sequence_1)) {
        case f_rubbish: {
            remove_sequences(sequences, 1);
            return;
        }
        case f7: {
            unmmko1_message message;
            initialize_message(&message);
            fill_command_in_message(&sequence_1, bus, &message);

            if (sequence_1.count != get_data_count(sequence_1.values[0]) + 1)
                message.error |= (UNMMKO1_MSG_ERR_PROTOCOL | UNMMKO1_MSG_ERR_DATA_COUNT);

            remove_sequences(sequences, 1);
            un_queue_push_back(messages, &message);
            return;
        }
        case f9: {
            unmmko1_message message;
            initialize_message(&message);
            fill_command_in_message(&sequence_1, bus, &message);

            if (sequence_1.count != 1)
                message.error |= (UNMMKO1_MSG_ERR_PROTOCOL | UNMMKO1_MSG_ERR_DATA_COUNT);

            remove_sequences(sequences, 1);
            un_queue_push_back(messages, &message);
            return;
        }
        case f10: {
            unmmko1_message message;
            initialize_message(&message);
            fill_command_in_message(&sequence_1, bus, &message);

            if (sequence_1.count != 2)
                message.error |= (UNMMKO1_MSG_ERR_PROTOCOL | UNMMKO1_MSG_ERR_DATA_COUNT);

            remove_sequences(sequences, 1);
            un_queue_push_back(messages, &message);
            return;
        }
        case f_unknown: {
            unmmko1_message message;
            initialize_message(&message);
            fill_command_in_message(&sequence_1, bus, &message);

            message.error |= UNMMKO1_MSG_ERR_PROTOCOL;

            remove_sequences(sequences, 1);
            un_queue_push_back(messages, &message);
            return;
        }
        default:
            break;
    }

    //  2. Временная задержка превышает таймаут
    //        Здесь мы можем сформировать законченные сообщения для всех форматов, но с состоянием ОО
    if (sequence_1.gap >= accumulator->timeout_value_in_us) {
        unmmko1_message message;
        initialize_message(&message);
        fill_command_in_message(&sequence_1, bus, &message);

        message.error |= UNMMKO1_MSG_ERR_PROTOCOL;
        message.error |= UNMMKO1_MSG_ERR_NO_RESPONSE;

        remove_sequences(sequences, 1);
        un_queue_push_back(messages, &message);
    }
}

void analyze_2_sequences(sequence_s* sequences, unmmko1_bus bus, accumulator_t* accumulator, un_queue* messages) {
    sequence_s sequence_1 = sequences[0];
    sequence_s sequence_2 = sequences[1];

    // Варианты разбора двух последовательностей:
    //  1. Если вторая последовательность мусорная, то обрабатываем только первую последователь с состоянием ОО
    //  2. Для каждого из форматов 1, 2, 4, 5, 6 и 8 составляем сообщения
    //  3. Для формата 3 можем сформировать сообщение с ОО, если превышен таймаут

    //  1. Если вторая последовательность мусорная, то обрабатываем только первую последователь с состоянием ОО
    if (f_rubbish == detect_format(&sequence_2)) {
        unmmko1_message message;
        initialize_message(&message);
        fill_command_in_message(&sequence_1, bus, &message);

        message.error |= UNMMKO1_MSG_ERR_PROTOCOL;
        message.error |= UNMMKO1_MSG_ERR_NO_RESPONSE;

        remove_sequences(sequences, 2);
        un_queue_push_back(messages, &message);
    }

    //  2. Для каждого из форматов 1, 2, 4, 5, 6 и 8 составляем сообщения
    //  3. Для формата 3 можем сформировать сообщение с ОО, если превышен таймаут
    switch (detect_format(&sequence_1)) {
        case f1: {
            unmmko1_message message;
            initialize_message(&message);
            fill_command_in_message(&sequence_1, bus, &message);
            fill_response_1_in_message(&sequence_2, &message);

            if (sequence_1.count != get_data_count(sequence_1.values[0]) + 1 || sequence_2.count != 1)
                message.error |= (UNMMKO1_MSG_ERR_PROTOCOL | UNMMKO1_MSG_ERR_DATA_COUNT);
            if (get_rt_address(sequence_1.values[0]) != get_rt_address(sequence_2.values[0]))
                message.error |= UNMMKO1_MSG_ERR_PROTOCOL;
            if (has_any_error_bit(sequence_2.values[0]))
                message.error |= UNMMKO1_MSG_ERR_ANY_ERROR_BIT;

            remove_sequences(sequences, 2);
            un_queue_push_back(messages, &message);
            return;
        }
        case f2: {
            unmmko1_message message;
            initialize_message(&message);
            fill_command_in_message(&sequence_1, bus, &message);
            fill_response_1_in_message(&sequence_2, &message);

            if (sequence_2.count != get_data_count(sequence_1.values[0]) + 1 || sequence_1.count != 1)
                message.error |= (UNMMKO1_MSG_ERR_PROTOCOL | UNMMKO1_MSG_ERR_DATA_COUNT);
            if (get_rt_address(sequence_1.values[0]) != get_rt_address(sequence_2.values[0]))
                message.error |= UNMMKO1_MSG_ERR_PROTOCOL;
            if (has_any_error_bit(sequence_2.values[0]))
                message.error |= UNMMKO1_MSG_ERR_ANY_ERROR_BIT;

            remove_sequences(sequences, 2);
            un_queue_push_back(messages, &message);
            return;
        }
        case f3: {
            if (sequence_2.gap >= accumulator->timeout_value_in_us) {
                unmmko1_message message;
                initialize_message(&message);
                fill_command_in_message(&sequence_1, bus, &message);
                fill_response_1_in_message(&sequence_2, &message);

                message.error |= UNMMKO1_MSG_ERR_PROTOCOL;
                message.error |= UNMMKO1_MSG_ERR_NO_RESPONSE;
                if (has_any_error_bit(sequence_2.values[0]))
                    message.error |= UNMMKO1_MSG_ERR_ANY_ERROR_BIT;

                remove_sequences(sequences, 2);
                un_queue_push_back(messages, &message);
            }
            return;
        }
        case f4: {
            unmmko1_message message;
            initialize_message(&message);
            fill_command_in_message(&sequence_1, bus, &message);
            fill_response_1_in_message(&sequence_2, &message);

            if (sequence_1.count != 1 || sequence_2.count != 1)
                message.error |= (UNMMKO1_MSG_ERR_PROTOCOL | UNMMKO1_MSG_ERR_DATA_COUNT);
            if (get_rt_address(sequence_1.values[0]) != get_rt_address(sequence_2.values[0]))
                message.error |= UNMMKO1_MSG_ERR_PROTOCOL;
            if (has_any_error_bit(sequence_2.values[0]))
                message.error |= UNMMKO1_MSG_ERR_ANY_ERROR_BIT;

            remove_sequences(sequences, 2);
            un_queue_push_back(messages, &message);
            return;
        }
        case f5: {
            unmmko1_message message;
            initialize_message(&message);
            fill_command_in_message(&sequence_1, bus, &message);
            fill_response_1_in_message(&sequence_2, &message);

            if (sequence_1.count != 1 || sequence_2.count != 2)
                message.error |= (UNMMKO1_MSG_ERR_PROTOCOL | UNMMKO1_MSG_ERR_DATA_COUNT);
            if (get_rt_address(sequence_1.values[0]) != get_rt_address(sequence_2.values[0]))
                message.error |= UNMMKO1_MSG_ERR_PROTOCOL;
            if (has_any_error_bit(sequence_2.values[0]))
                message.error |= UNMMKO1_MSG_ERR_ANY_ERROR_BIT;

            remove_sequences(sequences, 2);
            un_queue_push_back(messages, &message);
            return;
        }
        case f6: {
            unmmko1_message message;
            initialize_message(&message);
            fill_command_in_message(&sequence_1, bus, &message);
            fill_response_1_in_message(&sequence_2, &message);

            if (sequence_1.count != 2 || sequence_2.count != 1)
                message.error |= (UNMMKO1_MSG_ERR_PROTOCOL | UNMMKO1_MSG_ERR_DATA_COUNT);
            if (get_rt_address(sequence_1.values[0]) != get_rt_address(sequence_2.values[0]))
                message.error |= UNMMKO1_MSG_ERR_PROTOCOL;
            if (has_any_error_bit(sequence_2.values[0]))
                message.error |= UNMMKO1_MSG_ERR_ANY_ERROR_BIT;

            remove_sequences(sequences, 2);
            un_queue_push_back(messages, &message);
            return;
        }
        case f8: {
            unmmko1_message message;
            initialize_message(&message);
            fill_command_in_message(&sequence_1, bus, &message);
            fill_response_1_in_message(&sequence_2, &message);

            if (sequence_2.count != get_data_count(sequence_1.values[0]) + 1)
                message.error |= (UNMMKO1_MSG_ERR_PROTOCOL | UNMMKO1_MSG_ERR_DATA_COUNT);
            if (sequence_2.count != get_data_count(sequence_1.values[1]) + 1)
                message.error |= (UNMMKO1_MSG_ERR_PROTOCOL | UNMMKO1_MSG_ERR_DATA_COUNT);
            if (sequence_1.count != 2)
                message.error |= (UNMMKO1_MSG_ERR_PROTOCOL | UNMMKO1_MSG_ERR_DATA_COUNT);
            if (get_rt_address(sequence_1.values[1]) != get_rt_address(sequence_2.values[0]))
                message.error |= UNMMKO1_MSG_ERR_PROTOCOL;
            if (has_any_error_bit(sequence_2.values[0]))
                message.error |= UNMMKO1_MSG_ERR_ANY_ERROR_BIT;

            remove_sequences(sequences, 2);
            un_queue_push_back(messages, &message);
            return;
        }
        default:
            break;
    }
}

void analyze_3_sequences(sequence_s* sequences, unmmko1_bus bus, accumulator_t* accumulator, un_queue* messages) {
    unmmko1_message message;
    sequence_s sequence_1 = sequences[0];
    sequence_s sequence_2 = sequences[1];
    sequence_s sequence_3 = sequences[2];
    (void)accumulator;

    // Разбор формата 3:
    //  1. Если третья последовательность мусорная, то обрабатываем только первые две последователи с состоянием ОО
    //  2. Иначе это формат 3

    //  1. Если третья последовательность мусорная, то обрабатываем только первые две последователи с состоянием ОО
    if (f_rubbish == detect_format(&sequence_3)) {
        initialize_message(&message);
        fill_command_in_message(&sequence_1, bus, &message);
        fill_response_1_in_message(&sequence_2, &message);

        message.error |= UNMMKO1_MSG_ERR_PROTOCOL;
        message.error |= UNMMKO1_MSG_ERR_NO_RESPONSE;
        if (has_any_error_bit(sequence_2.values[0]))
            message.error |= UNMMKO1_MSG_ERR_ANY_ERROR_BIT;

        remove_sequences(sequences, 3);
        un_queue_push_back(messages, &message);
        return;
    }

    //  2. Иначе это формат 3
    initialize_message(&message);
    fill_command_in_message(&sequence_1, bus, &message);
    fill_response_1_in_message(&sequence_2, &message);
    fill_response_2_in_message(&sequence_3, &message);

    if (sequence_2.count != get_data_count(sequence_1.values[0]) + 1)
        message.error |= (UNMMKO1_MSG_ERR_PROTOCOL | UNMMKO1_MSG_ERR_DATA_COUNT);
    if (sequence_2.count != get_data_count(sequence_1.values[1]) + 1)
        message.error |= (UNMMKO1_MSG_ERR_PROTOCOL | UNMMKO1_MSG_ERR_DATA_COUNT);
    if (sequence_1.count != 2)
        message.error |= (UNMMKO1_MSG_ERR_PROTOCOL | UNMMKO1_MSG_ERR_DATA_COUNT);
    if (sequence_3.count != 1)
        message.error |= (UNMMKO1_MSG_ERR_PROTOCOL | UNMMKO1_MSG_ERR_DATA_COUNT);
    if (get_rt_address(sequence_1.values[0]) != get_rt_address(sequence_3.values[0]))
        message.error |= UNMMKO1_MSG_ERR_PROTOCOL;
    if (get_rt_address(sequence_1.values[1]) != get_rt_address(sequence_2.values[0]))
        message.error |= UNMMKO1_MSG_ERR_PROTOCOL;
    if (has_any_error_bit(sequence_2.values[0]) || has_any_error_bit(sequence_3.values[0]))
        message.error |= UNMMKO1_MSG_ERR_ANY_ERROR_BIT;

    remove_sequences(sequences, 3);
    un_queue_push_back(messages, &message);
}

void analyze_sequences(sequence_s* sequences, unmmko1_bus bus, accumulator_t* accumulator, un_queue* messages) {
    size_t sequence_count = 0;
    sequence_s* sequence = get_last_sequence(sequences);
    if (NULL == sequence || 0 == sequence->gap)
        return;

    sequence_count = get_sequence_count(sequences);
    if (1 == sequence_count)
        analyze_1_sequence(sequences, bus, accumulator, messages);
    else if (2 == sequence_count)
        analyze_2_sequences(sequences, bus, accumulator, messages);
    else if (3 == sequence_count)
        analyze_3_sequences(sequences, bus, accumulator, messages);
}

void analyze_all_sequences(accumulator_t* accumulator, un_queue* messages) {
    analyze_sequences(accumulator->sequence_a, UNMMKO1_BUS_A, accumulator, messages);
    analyze_sequences(accumulator->sequence_b, UNMMKO1_BUS_B, accumulator, messages);
}

void unmmko1_parse_words(un_queue* words, accumulator_t* accumulator, un_queue* messages) {
    size_t word_index = 0;
    size_t word_count = un_queue_size(words);
    for (word_index = 0; word_index < word_count; ++word_index) {
        milstd1553_word_s word;
        un_queue_get(words, word_index, &word);

        update_gap_for_sequences(accumulator, &word);
        analyze_all_sequences(accumulator, messages);
        append_word_to_sequences(accumulator, &word);
    }

    update_gap_using_current_time(accumulator);
    analyze_all_sequences(accumulator, messages);
}

unmmko1_bus get_bus(milstd1553_word_s* word) {
    return (word->state & 0x0004) ? UNMMKO1_BUS_B : UNMMKO1_BUS_A;
}

bool is_sequences_empty(sequence_s* s) {
    return 0 == s[0].count;
}

sequence_s* get_current_sequence(sequence_s* s) {
    if (s[1].gap > 0)
        return &s[2];
    else if (s[0].gap > 0)
        return &s[1];
    else
        return &s[0];
}

ViUInt64 gap_between_words(ViUInt64 start_time_word_1, ViUInt64 start_time_word_2) {
    // Временная пауза между словами вычисляется между
    // последним пересечением нуля первого слова (start_time_word_1 + 19.5 мкс)
    // и первым пересечением нуля второго слова (start_time_word_2 + 1.5 мкс)
    if (start_time_word_2 >= start_time_word_1 + 18)
        return start_time_word_2 - start_time_word_1 - 18;
    return 0;
}

void update_gap_for_sequences(accumulator_t* accumulator, milstd1553_word_s* word) {
    if (!is_sequences_empty(accumulator->sequence_a)) {
        ViUInt64 time_gap = 0;
        if (UNMMKO1_BUS_A == get_bus(word))
            time_gap = gap_between_words(accumulator->last_a_timestamp, word->timestamp);
        else
            // Компенасация задержки получения слов данных с мезонина = 20 мкс на слово и 2 мкс на срабатывание прерывания
            time_gap = gap_between_words(accumulator->last_a_timestamp + 22, word->timestamp);

        if (time_gap >= 4)
            get_last_sequence(accumulator->sequence_a)->gap = time_gap;
    }

    if (!is_sequences_empty(accumulator->sequence_b)) {
        ViUInt64 time_gap = 0;
        if (UNMMKO1_BUS_B == get_bus(word))
            time_gap = gap_between_words(accumulator->last_b_timestamp, word->timestamp);
        else
            // Компенасация задержки получения слов данных с мезонина = 20 мкс на слово и 2 мкс на срабатывание прерывания
            time_gap = gap_between_words(accumulator->last_b_timestamp + 22, word->timestamp);

        if (time_gap >= 4)
            get_last_sequence(accumulator->sequence_b)->gap = time_gap;
    }
}

void append_word_to_sequences(accumulator_t* accumulator, milstd1553_word_s* word) {
    sequence_s* current_sequence = NULL;
    ViUInt64 time_gap = 0;

    if (UNMMKO1_BUS_A == get_bus(word)) {
        current_sequence = get_current_sequence(accumulator->sequence_a);
        time_gap = gap_between_words(accumulator->last_a_timestamp, word->timestamp);
        accumulator->last_a_timestamp = word->timestamp;
    }
    else if (UNMMKO1_BUS_B == get_bus(word)) {
        current_sequence = get_current_sequence(accumulator->sequence_b);
        time_gap = gap_between_words(accumulator->last_b_timestamp, word->timestamp);
        accumulator->last_b_timestamp = word->timestamp;
    }
    else
        return;

    if (0 == current_sequence->count) {
        current_sequence->timestamp = word->timestamp;
        current_sequence->count = 1;
        if (word->state & 0x0001)
            current_sequence->types |= (1 << (current_sequence->count - 1));
        current_sequence->values[current_sequence->count - 1] = word->value;
        if (word->state & 0x0002)
            current_sequence->errors |= MANCHESTER_SEQUENCE_ERROR;
    }
    else if (40 == current_sequence->count) {
        current_sequence->errors |= WORD_COUNT_SEQUENCE_ERROR;
    }
    else {
        current_sequence->count = current_sequence->count + 1;
        if (word->state & 0x0001)
            current_sequence->types |= (1 << (current_sequence->count - 1));
        current_sequence->values[current_sequence->count - 1] = word->value;
        if (word->state & 0x0002)
            current_sequence->errors |= MANCHESTER_SEQUENCE_ERROR;
        if (time_gap > 3)
            current_sequence->errors |= CONTINUITY_SEQUENCE_ERROR;
    }
}

void update_gap_using_current_time(accumulator_t* accumulator) {
    ViUInt64 time_gap = gap_between_words(accumulator->last_a_timestamp + 22, accumulator->current_timestamp);
    if (0 != time_gap) {
        sequence_s* sequence = get_last_sequence(accumulator->sequence_a);
        if (NULL != sequence)
            sequence->gap = time_gap;
    }

    time_gap = gap_between_words(accumulator->last_b_timestamp + 22, accumulator->current_timestamp);
    if (0 != time_gap) {
        sequence_s* sequence = get_last_sequence(accumulator->sequence_b);
        if (NULL != sequence)
            sequence->gap = time_gap;
    }
}

bool is_match(ViUInt16 command_word, filter_rules_t* filter_rules) {
    ViUInt32 address = (command_word & 0xf800) >> 11;
    if ((1 << address) & filter_rules->addresses_mask) {
        ViUInt32 receive = (command_word & 0x0400) ? 1 : 0;
        ViUInt32 subaddress = (command_word & 0x03e0) >> 5;
        ViUInt32 modecode = command_word & 0x001f;

        if (0 == subaddress || 31 == subaddress) {
            if (1 == receive)
                return (1 << modecode) & filter_rules->transmit_modecodes[address];
            else
                return (1 << modecode) & filter_rules->receive_modecodes[address];
        }
        else {
            if (1 == receive)
                return (1 << subaddress) & filter_rules->transmit_subaddresses[address];
            else
                return (1 << subaddress) & filter_rules->receive_subaddresses[address];
        }

        return true;
    }

    return false;
}

void unmmko1_filter_messages(un_queue* messages, filter_rules_t* filter_rules, un_queue* filtered_messages) {
    unmmko1_message message;
    size_t message_index = 0;
    const size_t message_count = un_queue_size(messages);

    for (message_index = 0; message_index < message_count; ++message_index) {
        if (un_queue_get(messages, message_index, &message)) {
            bool match_in_command_word_1 = (message.activity & UNMMKO1_MSG_ACT_CWD_1) && is_match(message.command.command_word_1, filter_rules);
            bool match_in_command_word_2 = (message.activity & UNMMKO1_MSG_ACT_CWD_2) && is_match(message.command.command_word_2, filter_rules);
            if (match_in_command_word_1 || match_in_command_word_2) {
                un_queue_push_back(filtered_messages, &message);
            }
        }
    }
}
