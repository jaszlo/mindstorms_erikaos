#include "cpu/arm9/inc/internal/debug_io.h"

unsigned int base = 10;
unsigned int *base_ptr = &base;

int set_base(unsigned int new_base)
{
    if (new_base != 2 && new_base != 10 && new_base != 16)
    {
        return -1;
    }
    unsigned int old = *base_ptr;
    *base_ptr = new_base;
    return old;
}

void print_mem(void *addr, unsigned int len)
{
    int old_base = set_base(HEX);
    for (int i = 0; i < len; i += 4)
    {
        put_ptr(addr + i);
        put_string(" : ");
        for (int j = 0; j < 4; j++)
        {
            long *l = (long *)addr;
            put_num(*(l + i + j));
            put_char('\t');
        }
        put_char('\n');
    }
    set_base(old_base);
}

int put_char(int c)
{
    if (c == '\n')
        put_char('\r');

    while (!(*UART_LSR & (1 << 5)))
        ;
    *UART_THR = c;
    return c;
}

int put_string(const char *s)
{
    for (; *s != 0; s++)
    {
        put_char(*s);
    }

    return 0;
}

int put_bool(int b)
{
    return put_string(b ? "true\n" : "false\n");
}

int put_int(int i)
{
    if (i < 0)
    {
        put_char('-');
        i = -i;
    }

    put_num((unsigned long long)i);
    return put_char('\n');
}

int put_num(unsigned int i)
{
    // Add prefix
    switch (base)
    {
    case 2:
        put_string("0b");
        break;
    case 10:
        put_string("");
        break;
    case 16:
        put_string("0x");
        break;
    }

    if (i == 0)
    {
        return put_char('0');
    }

    // Reverse number
    unsigned long long reversed = 0;
    unsigned int zeros = 0;
    while (i / base > 0)
    {
        reversed *= base;
        reversed += i % base;
        if (reversed == 0)
        {
            zeros++;
        }
        i /= base;
    }

    put_char((char)(i < 10 ? '0' + i : 'a' + i - 10));

    // Convert numbers to chars
    for (char digit = 0; reversed > 0; reversed /= base)
    {
        char value = reversed % base;
        digit = value < 10 ? '0' + value : 'a' + value - 10;

        put_char(digit);
    }
    for (unsigned int i = 0; i < zeros; i++)
    {
        put_char('0');
    }
}


void print_tos() {
  asm("ldr r0, [sp]");
  asm("bl put_ptr");
}

int put_ptr(const void *ptr)
{
    unsigned int old_base = base;
    set_base(HEX);
    put_num((int)ptr);
    set_base(old_base);
    put_char('\n');
    return 0;
}
