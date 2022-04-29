#ifndef __INCLUDE_ARM9_IO_H__
#define __INCLUDE_ARM9_IO_H__

// UART serial port interface to put a char on the screen
#define UART_THR (volatile char *)(0x01D0C000)
#define UART_LSR (volatile char *)(0x01D0C014)
#define EOF -1

// Base constants
#define HEX 16
#define DEC 10
#define BIN 2

#define _put_char __asm__ __volatile__("mov r0, #88\nldr r1, =0x01D0C000\nstr r0, [r1]\n");
#define _put_pc __asm__ __volatile__("mov r0, pc\nb put_ptr\n");
#define _put_reg(reg) __asm__ __volatile__("mov r0, " reg "put_ptr\n")

/**
 * Sets the base in which integers are printed
 * Returns 0 on success and -1 if invalid base was choosen.
 */
int set_base(unsigned int new_base);
int put_char(int c);
int put_string(const char *s);
int put_bool(int b);
int put_int(int i);
int put_num(unsigned long long i);
int put_ptr(const void *ptr);
void print_mem(void *addr, unsigned int len);
#endif