#include <stdio.h>
__attribute__((constructor)) void a()
{
    printf("A\n");
}

__attribute__((destructor)) void b()
{
    printf("B\n");
}
int main()
{
    printf("Hello, World\n");
}