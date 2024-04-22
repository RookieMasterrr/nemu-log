#include<stdio.h>
#include <stdarg.h>

void my_printf(char *s,...);
void print_str(char *s);
int static digit_num_int(int num);
int static append_int(int from, int num, char buf[]);
int static append_str(int from, char *str, char buf[]);


int main()
{
    // int d = 2147483648;
    // char* str = "nihao,nihao";
    // my_printf("Hello, World d = %d s = %s asdsa\n",d,str);
    // my_printf("%d + %d = %d\n", 2, 10, 12);
    my_printf("ten = %d\n",10);    
}


void my_printf(char *s,...) {
    va_list valist;
    va_start(valist,s);
    char buf[128] = {0};
    int index = 0;
    int c;
    while (c=*(s++))
    {
        if (c=='%') {
            switch (*(s++))
            {
            case 's':
                char* s_t = va_arg(valist,char*);
                index = append_str(index,s_t,buf);
            break;
            case 'd':
                int int_t = va_arg(valist,int);
                index = append_int(index,int_t,buf);
            break;
            default:
                printf("NOT IMPLEMENTED");
            }
        } else{
            buf[index++]=c;
        }       
    }
    va_end(valist);
    buf[index++]=0;
    print_str(buf);
}

int static append_str(int from, char *str, char buf[]) {
    int c;
    while (c=*(str++)) {
        buf[from++] = c;
    }
    return from;
}



int static append_int(int from, int num, char buf[]) {
    if (num<0)
    {
        if (num==-2147483648)
        {
            buf[from++]='-';
            buf[from++]='2';
            num = 147483648;
        }else{
            buf[from++]='-';
            num = -num;
        }
    }
    
    int count = digit_num_int(num);
    int store[count];
    int p = 0;
    int one_ten_hund = 1;
    for(int i=0; i<count; i++){
        store[i] = (num/one_ten_hund)%10;
        one_ten_hund = one_ten_hund*10;
    }
    for(int i=count-1; i>=0; i--){
        buf[from++]=store[i]+48;
    }
    return from;
}

int static digit_num_int(int num) {
    if (num<0) {
        num = -num;
    }
    
    long ten_hundred = 10;
    int digit = 1;
    while (num>=ten_hundred)
    {
        ten_hundred = ten_hundred * 10;
        digit+=1;
    }
    return digit;
}

void print_str(char *s) {
    int c;
    while (c=*(s++))
    {
        putchar(c);
    }
}