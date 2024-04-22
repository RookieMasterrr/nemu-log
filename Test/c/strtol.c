#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
    char s[] = "0x10";
    long d = strtol(s,NULL,16);
    printf("%ld\n",d);
    return 0;
}
