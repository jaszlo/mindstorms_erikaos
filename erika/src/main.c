extern void puts(char *s);

int main(char *args[], int argc) {
    (void)argc;
    puts(args[0]);
    return 0;
}