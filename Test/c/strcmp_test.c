#include<string.h>
#include<stdio.h>
int my_cmp(const char *s1, const char *s2);


int main()
{
    printf("%d",my_cmp("aa","a"));
}

int my_cmp(const char *s1, const char *s2) {
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