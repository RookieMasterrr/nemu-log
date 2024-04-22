#include <stdio.h>

#define bool int
#define false 0
#define true 1

char tokens[] = "4+3*2+1-1";
//               0123456789

static bool if_in_paranthese(int p, int q, int position)
{
    bool in_paranthess = false;
    int left_paranthese_num = 0;
    for (int i = p; i <= q; i++)
    {
        if (i == position)
        {
            if (in_paranthess)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        if (tokens[i] == '(')
        {
            in_paranthess = true;
            left_paranthese_num++;
        }
        else if (tokens[i] == ')')
        {
            left_paranthese_num--;
            if (left_paranthese_num == 0)
            {
                in_paranthess = false;
            }
        }
    }
}

int main()
{
    int size = sizeof(tokens);
    for (int i = 0; i <= size - 2; i++)
    {
        printf("%d\n", if_in_paranthese(0, sizeof(tokens) - 2, i));
    }
}

// char tokens[] = "4+3*(2-1)";
//                  012345678