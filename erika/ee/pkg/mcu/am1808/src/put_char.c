#include "mcu/am1808/inc/put_char.h"
#include "mcu/am1808/inc/uart.h"

void put_char(int c)
{
    if (c == '\n')
        put_char('\r');

    while (!(*(UART_LSR) & (1 << 5)))
        ;
    *(UART_THR) = c;
}