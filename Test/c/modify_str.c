#include <stdio.h>
#include <stdlib.h>
int main()
{
    char *s = malloc(5 * sizeof(char));
    printf("%s\n", s);
    s = "4567";
    printf("%s\n", s);
}