#include "ee.h"

TASK(Task1)
{
  char stuff[1];
  put_string("Hello world!\n");
  put_string("Iam printing stuff!\n");
  put_string("Here is an integer in decimal: ");
  short i = -1337;
  put_int(i);
  put_char('\n');
  put_string("Here is that number in binary: ");
  set_base(BIN);
  put_int(i);
  set_base(DEC);
  put_char('\n');
  put_string("And here is a pointer: ");
  char *ptr = stuff;
  put_ptr(ptr);
  put_char('\n');
  put_string("Here is the bool evaluation of that pointer == NULL: ");
  put_bool(ptr == NULL);
  put_char('\n');
  // Is required to be called at the end of every Task or it goes into undefined behaviour
  // @Source: https://download.tuxfamily.org/erika/webdownload/manuals_pdf/ee_refman_1_4_5.pdf#page=25
  TerminateTask(); 
}

int main(void)
{
  // Task 1 should Autostart
  // This function needs to be implemented for linkig to work
  // After main we go into infinit loop
  return 0;
}