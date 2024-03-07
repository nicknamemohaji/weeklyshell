#include <stdio.h>
#include <unistd.h>

int main(void)
{
    char buf[100];
    int n;
    write(2, "hello\n", 6);

    while ((n = read(0, buf, 100)) > 0)
    {
        write(2, buf, n);
        dprintf(2, "n = %d\n", n);
    }
}