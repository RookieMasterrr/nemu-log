#include <stdio.h>
int main()
{
#ifdef _WIN32
    printf("WIN\n");
#elif __Linux__
    printf("LINUX\n");
#elif __APPLE__
    printf("MACOS\n");
#endif
}