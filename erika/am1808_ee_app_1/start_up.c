extern int main();
#include "ee.h"
// entry point

int __attribute__((section("start"))) start_up(void)
{
    main();
}
