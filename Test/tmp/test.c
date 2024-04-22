#include <stdio.h>

int fun(int a, int b)
{
    return a + b;
}

int main()
{
    int a = 1;
    int b = 2;
    int c = fun(a, b);
    printf("c=%d\n", c);
    return 0;
}