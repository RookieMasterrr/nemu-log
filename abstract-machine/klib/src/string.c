#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>
#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int print_char(char a);


size_t strlen(const char *s) {
  panic("Not implemented");
}

char *strcpy(char *dst, const char *src) {
  int c;
  int index = 0;
  while ((c= *(src++))!=0)
  {
    dst[index++] = c;
  }
  dst[index]=0;
  return dst;
}


char *strncpy(char *dst, const char *src, size_t n) {
  panic("Not implemented");
}

char *strcat(char *dst, const char *src) {
  // get dst's '0's position
  char *p = dst;
  while (1)
  {
    if ((*p)==0)
    {
      break;
    }
    p++;
  }
  int c;
  while (1)
  {
    c = *src;
    if (c==0) {
      *p = '\0';
      return dst;
    } else{
      *p = c;
      src++;
      p++;
    }
    
  }
  
}

int strcmp(const char *s1, const char *s2) {
  int c_s1 = *s1;
  int c_s2 = *s2;

  while (c_s1)
  {
    c_s1 = *s1;
    c_s2 = *s2;

    if (c_s1 > c_s2) {
      return 1;
    }else if (c_s1 < c_s2){
      return -1;
    }
    s1++;
    s2++;
  }
  return 0;
}

int strncmp(const char *s1, const char *s2, size_t n) {
  panic("Not implemented");
}

void *memset(void *s, int c, size_t n) {
  char *t = (char *)s;
  for(int i=0; i<c; i++){
    t[i]=c;
  }
  return s;
}

void *memmove(void *dst, const void *src, size_t n) {
  panic("Not implemented");
}

void *memcpy(void *out, const void *in, size_t n) {
  panic("Not implemented");
}

int memcmp(const void *s1, const void *s2, size_t n) {
  char *t1 = (char*)s1;
  char *t2 = (char*)s2;
  for(int i=0; i<n; i++){
    if (t1[i]>t2[i])
    {
      return 1;
    }else if (t1[i]<t2[i])
    {
      return -1;
    }
  }
  return 0;
}

#endif
