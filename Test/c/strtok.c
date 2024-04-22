//read command and parameters
#include<stdio.h>
#include<string.h>
int main()
{
    char src[] = "hello world fuck you";
    //char* res = strtok(src," ");
    //printf("%s \n",res);

    char *p = src;

    char *res;

    while(res=strtok(p," "))
    {
	printf("%s\n",res);
	p = p + strlen(res) + 1;
    }
}
