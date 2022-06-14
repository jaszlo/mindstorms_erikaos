#ifndef __INCLUDE_ARM9_PUT_CHAR_H__
#define __INCLUDE_ARM9_PUT_CHAR_H__

void put_char(int c);

// Debugging Macros
#define __nl put_char('\n');

#define _put_char(c)                                                             \
    __asm__ __volatile__("mov r0, #" c "\nldr r1, =0x01D0C000\nstr r0, [r1]\n"); \
    put_char('\n');
#define _put_pc                                       \
    __asm__ __volatile__("mov r0, pc\nbl put_ptr\n"); \
    put_char('\n');
#define _put_reg(reg)                                      \
    __asm__ __volatile__("mov r0, " reg "\nbl put_ptr\n"); \
    put_char('\n');

#define _print_macro(s) \
    put_string(str(s)); \
    put_char('\n')
#define str(s) #s

#endif /* __INCLUDE_ARM9_PUT_CHAR_H__ */