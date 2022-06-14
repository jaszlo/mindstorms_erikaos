#include "ee.h"

TASK(Task1)
{
  char stuff[1];
  put_string("\t\tHello world!\n");
  put_string("\t\tIam printing stuff!\n");
  put_string("\t\tHere is an integer in decimal: ");
  short i = -1337;
  put_int(i);
  __nl;
  put_string("\t\tHere is that number in binary: ");
  set_base(BIN);
  put_int(i);
  set_base(DEC);
 __nl;
  put_string("\t\tAnd here is a pointer: ");
  char *ptr = stuff;
  put_ptr(ptr);
 __nl;
  put_string("\t\tHere is the bool evaluation of that pointer == NULL: ");
  put_bool(ptr == NULL);
 __nl;
  put_string("\t\tProgram is finished!\n");
  // Is required to be called at the end of every Task or it goes into undefined behaviour
  // @Source: https://download.tuxfamily.org/erika/webdownload/manuals_pdf/ee_refman_1_4_5.pdf#page=25
  TerminateTask(); 
}
#include "mcu/am1808/inc/uart.h"

void isr() {
  // Determine cause of this IRQ
  unsigned char rx_data;
  unsigned int stat = uart_irq_status();
  if (stat == UART_IRQID_RX_DATA) {
    rx_data = uart_get_char();
    put_char(rx_data + 1);
  }
}
int main(void)
{
  // Task 1 should Autostart
  
  unsigned int config = 0x00000003u; // 8 bit mode
  unsigned int sample_rate = 16;
  uart_enable();
  uart_configure(CLK_SPEED, BAUD_115200, config, sample_rate);

  irq_set_channel(IRQ_NUM_UART2_INT, 2);
  irq_register(IRQ_NUM_UART2_INT, isr);
  irq_enable();
  unsigned int irq_flgs = UART_INT_RXDATA_CTI;
  uart_irq_enable(irq_flgs);

  while(1);
  return 0;
}