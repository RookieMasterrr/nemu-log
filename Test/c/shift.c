#include<stdio.h>
int main()
{
    // int a = 0b1111111110101;
    // printf("%d",a&31);

    //bit wise
    // unsigned int a = 0b11111111111111111111111111111111;
    // printf("%u\n",a);
    // printf("%d\n",(int)a);


    //load the high bit(20) fill low bit(12) with zero
    // unsigned rd;
    // unsigned beLoad=0b11011110111111110111;//max 20bit
    // rd = beLoad;
    // rd = rd<<12;
    // printf("rd = %B",rd);
// 0b11111111111111111111000000000000

    //sign-extend
    // unsigned short i16 = 0b1000000000000000;
    // unsigned int   i32 = i16+0b11111111111111110000000000000000;

    // printf("binary = %hd\n",i16);
    // printf("binary = %d\n",i32);


    //high mul
    //8bit times 8bit
    //11111111 * 11111111 255*255
    //11111110   00000001 8bit * 8bit get 16bit
    //how to get upper we use right shift!!

    // unsigned char x1 = 0b11111111;
    // unsigned char x2 = 0b11111111;
    // unsigned short r = x1 * x2;
    // unsigned char h_r = r>>8;
    // printf("h_r = %d\n",h_r);
    // printf("r = %d\n",(char)r);




    //sign-extend
    // unsigned short x = 0b1000000000000000;
    // printf("x=%hd\n",x);


    // mullonglongtest

    // unsigned int x1 = 0xaeb1c2aa;
    // unsigned int x2 = 0xaeb1c2aa;

    // int xx1 = x1;
    // int xx2 = x2;

    // long long r_whole = (signed long long)xx1 * (signed long long)xx2;

    // printf("r_whole = %lld\n",r_whole);


//x1
//

//x2

//r_whole
// 0b 00011001110100101001101010111001 n    11011011000110100001100011100100 y
// 
//r_l

//r_h






// sign and unsign:
    // unsigned short x = 0b1000000000000000;
    // short y = x;
    // printf("%d\n",(short)x);
    // printf("%d\n",y);

    // unsigned long long x = 0b1000000000000000000000000000000000000000000000000000000000000000;
    // long long y = x;
    // printf("%lld\n",x);
    // printf("%lld\n",y);


    unsigned int x1 = 0xaeb1c2aa;
    printf("x1 forced convsersion = %ld\n",(long)x1);


    int x2 = x1;
    printf("x2 forced convsersion = %ld\n",(long)x2);


}