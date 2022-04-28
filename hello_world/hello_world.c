#define UART_THR (volatile char *)(0x01D0C000)
#define UART_LSR (volatile char *)(0x01D0C014)
#define EOF -1

int putchar(int c)
{
    if (c == '\n')
        putchar('\r');

    while (!(*UART_LSR & (1 << 5)))
        ;
    *UART_THR = c;
    return c;
}

int puts(const char *s)
{
    const char *c = s;
    while (*c)
    {
        int res = putchar(*c);
        if (__builtin_expect(res == EOF, 0))
            return EOF;
        ++c;
    }

    int res = putchar('\n');
    if (__builtin_expect(res == EOF, 0))
        return EOF;

    return 0;
}

// entry point
int hello_world(void)
{
    puts("Hello World!\n");
    return 1;
}
