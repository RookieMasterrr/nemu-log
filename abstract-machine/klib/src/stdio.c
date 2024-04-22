#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int static digit_num_int(int num);
int static append_int(int from, int num, char buf[]);
int static append_str(int from, char *str, char buf[]);

void print_str(char *s) {
    int c;
    while ((c=*(s++))!=0)
    {
        putch(c);
    }
}

//from now on, the printf is not from gnu/linux 
int printf(const char *s, ...) {
    putch('Y');
    // print_str("111");
    char out[128];//buffer size
    va_list valist;
    va_start(valist,s);
    int index = 0;
    int c;
    while ((c=*(s++))!=0)
    {
        if (c=='%') {
            switch (*(s++))
            {
            case 's':
                char* s_t = va_arg(valist,char*);
                index = append_str(index,s_t,out);
            break;
            case 'd':
                int int_t = va_arg(valist,int);
                index = append_int(index,int_t,out);
            break;
            default:
                printf("NOT IMPLEMENTED");
            }
        } else{
            out[index++]=c;
        }       
    }
    va_end(valist);
    out[index++]=0;
    print_str(out);
    return 0;
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  panic("Not implemented");
}

int sprintf(char *out, const char *s, ...) {
    va_list valist;
    va_start(valist,s);
    int index = 0;
    int c;
    while ((c=*(s++))!=0)
    {
        if (c=='%') {
            switch (*(s++))
            {
            case 's':
                char* s_t = va_arg(valist,char*);
                index = append_str(index,s_t,out);
            break;
            case 'd':
                int int_t = va_arg(valist,int);
                index = append_int(index,int_t,out);
            break;
            default:
                printf("NOT IMPLEMENTED");
            }
        } else{
            out[index++]=c;
        }       
    }
    va_end(valist);
    out[index++]=0;
    // print_str(out);
    return 0;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}



int static append_str(int from, char *str, char buf[]) {
    int c;
    while ((c=*(str++))!=0) {
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


#endif
