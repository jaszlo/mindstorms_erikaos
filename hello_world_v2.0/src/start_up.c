extern int main(char *args[], int argc);

// entry point
int __attribute__((section("start"))) start_up(void) {
    char *args[] = {"\nHallo Welt!\n"};
    return main(args, 1);
}
