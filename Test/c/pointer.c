#include <stdio.h>

void changeA(int *a)
{
    *a = 9;
}

int main()
{
    int a = 1;
    int *p = &a;
    changeA(p);
    printf("a = %d\n", a);
}