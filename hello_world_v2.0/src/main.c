extern void put_string(char *s);

int main(char *args[], int argc)
{
    int i = 62 % argc;
    put_string(args[0]);
    return i;
}