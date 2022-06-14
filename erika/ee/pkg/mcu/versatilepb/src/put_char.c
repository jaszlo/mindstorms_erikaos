#include "mcu/versatilepb/inc/put_char.h"

// The QEMU model of the PL011 serial port ignores the transmit FIFO capabilities;
// in a real SOC the “Transmit FIFO Full” flag must be checked in the UARTFR register
// before writing on the UARTDR register.
void put_char (int c)
{
  if (c == '\n')
    put_char('\r');

  *UART0DR = c;
}