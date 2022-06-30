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
  // Is required to be called at the end of every Task or it goes into undefined behaviour
  // @Source: https://download.tuxfamily.org/erika/webdownload/manuals_pdf/ee_refman_1_4_5.pdf#page=25
  TerminateTask(); 
}

int main(void)
{
  // Task 1 should Autostart
  put_string("\t\tSuccess!\n");
  return 0;
}