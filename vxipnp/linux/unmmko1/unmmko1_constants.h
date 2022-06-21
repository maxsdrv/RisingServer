#ifndef UNMMKO1_CONSTANTS_H
#define UNMMKO1_CONSTANTS_H

#define REGISTER_FIFO       (0x0)                       //!< Регистр управления FIFO
#define REGISTER_IDN_QUERY  (0x2)                       //!< Регистр запроса идентификации (IDN)
#define M_FIRST_DELAY       10                          //!< Задержка первых данных
#define M_CLOCK             20                          //!< 125 нс
#define M_SAMPLE_WORDS      1                           //!< Ширина кадра в словах
#define M_SAMPLE_BYTES      4                           //!< Ширина кадра в байтах

#endif // UNMMKO1_CONSTANTS_H
