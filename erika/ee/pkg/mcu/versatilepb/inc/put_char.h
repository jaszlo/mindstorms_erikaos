#ifndef __INCLUDE_VERSATILEPB_PUT_CHAR_H__
#define __INCLUDE_VERSATILEPB_PUT_CHAR_H__

// UART serial port interface to put a in output buffer
#define UART0DR (volatile unsigned int*)(0x101f1000)

void put_char(int c);

#define __nl put_char('\n');
#endif /* __INCLUDE_VERSATILEPB_PUT_CHAR_H__ */