#define UART_THR (volatile char *)(0x01D0C000)
#define UART_LSR (volatile char *)(0x01D0C014)

int put_char(int c)
{
    if (c == '\n')
        put_char('\r');

    while (!(*UART_LSR & (1 << 5)))
        ;
    *UART_THR = c;
    return c;
}

void put_string(const char *s)
{
    for (; *s != 0; s++)
    {
        put_char(*s);
    }
}