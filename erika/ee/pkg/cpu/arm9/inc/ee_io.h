#ifndef __INCLUDE_ARM9_IO_H__
#define __INCLUDE_ARM9_IO_H__

// Base constants
#define HEX 16
#define DEC 10
#define BIN 2

/**
 * Sets the base in which integers are printed
 * Returns 0 on success and -1 if invalid base was choosen.
 */
int set_base(unsigned int new_base);
void put_string(const char *s);
void put_bool(int b);
void put_int(int i);
void put_num(unsigned int i);
void put_ptr(const void *ptr);
void print_mem(void *addr, unsigned int len);
void print_tos();

#endif /* __INCLUDE_ARM9_IO_H__ */