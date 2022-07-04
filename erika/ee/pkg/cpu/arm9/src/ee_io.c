#include "cpu/arm9/inc/ee_io.h"

#include "test/assert/inc/ee_assert.h"

#ifdef __AM1808__
#include "mcu/am1808/inc/put_char.h"
#endif
#ifdef __VERSATILEPB__
#include "mcu/versatilepb/inc/put_char.h"
#endif

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
            put_uint(*(l + i + j));
            put_char('\t');
        }
        put_char('\n');
    }
    set_base(old_base);
}

void put_string(const char *s)
{
    for (; *s != 0; s++)
    {
        put_char(*s);
    }
}

void put_bool(int b)
{
    put_string(b ? "true\n" : "false\n");
}

void put_int(int i)
{
    if (i < 0)
    {
        put_char('-');
        i = -i;
    }

    put_uint((unsigned long long)i);
}

void put_uint(unsigned int i)
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
        put_char('0');
        return;
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

void put_ptr(const void *ptr)
{
    unsigned int old_base = base;
    set_base(HEX);
    put_uint((int)ptr);
    set_base(old_base);
}

#ifdef __ASSERT__
extern EE_TYPEASSERTVALUE EE_expectations[];

void put_assertion(EE_TYPEASSERTVALUE assertion)
{

    switch (assertion)
    {
        case -1:
            put_string("EE_ASSERT_NIL");
            break;
        case 0:
            put_string("EE_ASSERT_INITVALUE");
            break;
        case 1:
            put_string("EE_ASSERT_YES");
            break;
        case 2:
            put_string("EE_ASSERT_NO");
            break;
        case 3:
            put_string("EE_ASSERT_ALREADYUSED");
            break;

    }
}

void EE_assert_summarize(const char *test_name, unsigned int result, unsigned int size)
{
    if (result == EE_ASSERT_YES)
    {   
        put_string("\t\t\t\t\t\t\t");
        put_string(test_name); put_string(" passed! ✓"); __nl;
    } else
    {
        put_string("\t\t\t\t\t\t\t");
        put_string(test_name); put_string(" failed! ✗"); __nl;
    
        for (int i = 0; i < size; i++)
        {
            if (EE_assertions[i] != EE_ASSERT_YES) 
            {
                put_string("\t\t\t\t\t\t\t\tAssertion "); put_uint(i); put_string (" failed!\n");
            }
        }
    }
}
#endif /* __ASSERT__ */