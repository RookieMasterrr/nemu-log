#include <stdio.h>
typedef unsigned char uint8;

union bittest
{
    struct
    {
        uint8 a1 : 4;
        uint8 a2 : 2;
        uint8 a3 : 2;
    } bf;
    uint8 a;
} ub;

int main()
{
    ub.a = 0b11110000;
    printf("a1=%u\n", ub.bf.a1);
    printf("a2=%u\n", ub.bf.a2);
    printf("a3=%u\n", ub.bf.a3);
}