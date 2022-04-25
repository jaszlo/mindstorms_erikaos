extern void puts(char *s);

int main(char *args[], int argc)
{
    int i = 62 % argc;
    puts(args[0]);
    return i;
}