extern int main();

// entry point
int __attribute__((section("start"))) start_up(void)
{
    return main();
}
