#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 32
typedef struct cstack
{
    int ptr;
    int array[MAXSIZE];
} Stack;

void initStack(Stack *s)
{
    s->ptr = -1;
    for (int i = 0; i < MAXSIZE; i++)
    {
        s->array[i] = 0;
    }
}

void push(Stack *s, int x)
{
    if (s->ptr == MAXSIZE - 1)
    {
        printf("Overflow\n");
        exit(-1);
    }

    s->array[++(s->ptr)] = x;
}

int pop(Stack *s)
{
    if (s->ptr == -1)
    {
        printf("stack empty");
        return -1;
    }

    return (s->array)[(s->ptr)--];
}

int main()
{
    Stack *s = (Stack *)malloc(sizeof(Stack));
    initStack(s);

    push(s, '(');
    push(s, ')');
    push(s, '(');

    printf("%c\n", pop(s));
    printf("%c\n", pop(s));
    printf("%c\n", pop(s));
    return 0;
}