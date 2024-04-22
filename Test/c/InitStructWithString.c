#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct Type
{
    int id;
    char *str;
};

int main()
{
    char *s = "123";
    struct Type t;
    t.id = 1;
    t.str = malloc(40);
    strcpy(t.str, s);
    printf("id = %d, str = %s\n", t.id, t.str);
    for (int i = 0; i < 40; i++)
    {
        printf("%d ", t.str[i]);
    }
}
