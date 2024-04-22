/***************************************************************************************
 * Copyright (c) 2014-2022 Zihao Yu, Nanjing University
 *
 * NEMU is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 *
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 *
 * See the Mulan PSL v2 for more details.
 ***************************************************************************************/

#include <isa.h>

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>
#include "sdb.h"
// for stack
typedef struct cstack
{
  int ptr;
  int array[32];
} Stack;
void initStack(Stack *s);
void push(Stack *s, int x);
int pop(Stack *s);
// for stack

enum
{
  TK_NOTYPE = 256,
  TK_EQ,
  TK_NUMBER,
  TK_NEGTIVE,
  TK_DEREF,
  TK_HEX,
  TK_REG,
  TK_NEQ,

  /* TODO: Add more token types */

};

static struct rule
{
  const char *regex;
  int token_type;
} rules[] = {

    /* TODO: Add more rules.
     * Pay attention to the precedence level of different rules.
     */

    {" +", TK_NOTYPE}, // spaces
    {"\\+", '+'},      // plus
    {"==", TK_EQ},     // equal
    {"!=", TK_NEQ},    // equal
    {"-", '-'},        // minus
    {"/", '/'},        // divide
    {"\\*", '*'},      // mutil or defer
    {"\\(", '('},      //(
    {"\\)", ')'},      //)
    {"\\$0|\\$ra|\\$sp|\\$gp|\\$tp|\\$t0|\\$t1|\\$t2|\\$s0|\\$s1|\\$a0|\\$a1|\\$a2|\\$a3|\\$a4|\\$a5|\\$a6|\\$a7|\\$s2|\\$s3|\\$s4|\\$s5|\\$s6|\\$s7|\\$s8|\\$s9|\\$s10|\\$s11|\\$t3|\\$t4|\\$t5|\\$t6|\\$pc", TK_REG},
    // reg
    {"0x[0-9a-fA-F]+", TK_HEX}, // HEX
    {"[0-9]", TK_NUMBER},       // number

};

// (\\$0|ra|sp|gp|tp|t0|t1|t2|s0|s1|a0|a1|a2|a3|a4|a5|a6|a7|s2|s3|s4|s5|s6|s7|s8|s9|s10|s11|t3|t4|t5|t6)

// const char *regs[] = {
//     "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
//     "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
//     "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
//     "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"};

#define NR_REGEX ARRLEN(rules)

static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex()
{
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i++)
  {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0)
    {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}

typedef struct token
{
  int type;
  char str[32];
} Token;

static Token tokens[32] __attribute__((used)) = {};
static int nr_token __attribute__((used)) = 0;

static word_t eval(int, int);
static bool check_parentheses(int p, int q);
static int get_main_token_position(int p, int q);
static bool if_calculate_token(Token t);
static bool if_in_paranthese(int p, int q, int position);
static int token_degree(Token t);

static bool make_token(char *e)
{
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;
  while (e[position] != '\0')
  {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i++)
    {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0)
      {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        // Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
        //     i, rules[i].regex, position, substr_len, substr_len, substr_start);

        position += substr_len;

        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */

        switch (rules[i].token_type)
        {
        default:
          // TODO();

          // loss the space
          if (rules[i].token_type != TK_NOTYPE)
          {
            Token t;
            t.type = rules[i].token_type;
            char str_token[32];
            sprintf(str_token, "%.*s", substr_len, substr_start);
            strcpy(t.str, str_token);

            tokens[nr_token] = t;
            nr_token++;
          }
        }

        break;
      }
    }

    if (i == NR_REGEX)
    {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      exit(-1);
      return false;
    }
  }

  return true;
}

word_t expr(char *e, bool *success)
{
  if (!make_token(e))
  {
    *success = false;
    return 0;
  }

  /* TODO: Insert codes to evaluate the expression. */
  // TODO();

  // turn * to DEFER:
  for (int i = 0; i < nr_token; i++)
  {
    // if (tokens[i].type == '*' && (i == 0 || tokens[i - 1].type == certain type) ) {
    if (tokens[i].type == '*' && (i == 0 || if_calculate_token(tokens[i - 1])))
    {
      tokens[i].type = TK_DEREF;
    }
  }

  word_t ret = eval(0, nr_token - 1);
  *success = true;
  return ret;
}

static word_t eval(int p, int q)
{
  if (p > q)
  {
    // An elgent way to quit cmd_q
    printf("%s\n", "p > q");
    exit(1);
  }
  else if (p == q)
  {
    if (tokens[q].type == TK_REG) // reg
    {
      bool success = false;
      char *search_str = (char *)malloc(5 * sizeof(char));
      if (strcmp(tokens[q].str, "$0") == 0)
      {
        search_str = "$0";
      }
      else if (strcmp(tokens[q].str, "$pc") == 0)
      {
        search_str = "pc";
      }
      else
      {
        search_str = tokens[q].str + 1;
      }

      word_t t = isa_reg_str2val(search_str, &success);
      if (success)
      {
        return t;
      }
      else
      {
        printf("token type is reg, error happened\n");
        exit(0);
      }
    }

    if (tokens[q].type == TK_HEX)
    {
      word_t num = strtol(tokens[q].str, NULL, 16);
      return num;
    }

    return atoi(tokens[q].str); // dec number
  }
  else if (check_parentheses(p, q))
  {
    return eval(p + 1, q - 1);
  }
  else
  {

    int main_token_position = get_main_token_position(p, q);
    // printf("main_token_position = %d\n", main_token_position);
    Token t = tokens[main_token_position];
    // if token t is DEFER we just need right side, which is val2
    word_t val1;
    word_t val2;
    if (t.type == TK_DEREF)
    {
      val1 = 0;
      val2 = eval(main_token_position + 1, q);
    }
    else
    {
      val1 = eval(p, main_token_position - 1);
      val2 = eval(main_token_position + 1, q);
    }

    switch (t.type)
    {
    case '+':
      return val1 + val2;
    case '-':
      return val1 - val2;
    case '*':
      return val1 * val2;
    case '/':
      return val1 / val2;
    case TK_DEREF:
      return GET4Byte(val2);
    case TK_EQ:
      return val1 == val2;
    case TK_NEQ:
      return val1 != val2;
    }

    return 0;
  }
}

static bool check_parentheses(int p, int q) // if the expression is surrounded by parenthese
{
  if ((tokens[p].type != '(') || (tokens[q].type != ')'))
  {
    return false;
  }
  else
  {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    initStack(s);
    for (int i = p; i <= q; i++)
    {
      if (tokens[i].type == '(')
      {
        push(s, '(');
      }
      else if (tokens[i].type == ')')
      {
        // int right_type = tokens[i].type;
        int left_type = pop(s);
        if (left_type == -1) // empty stack
        {
          return false;
        }

        if (left_type == '(') // match
        {
          if ((s->ptr == -1) && (i != q)) // if the first if ( is not matched by the last )
          {
            return false;
          }
        } // does not match
        else
        {
          return false;
        }
      }
    }
    if (s->ptr == -1) // end of expression, empty stack
    {
      return true;
    }
    else
    {
      return false;
    }
  }
}

static int get_main_token_position(int p, int q)
{
  /**
   * '+' '-' in 1 degree
   * '*' '/' in 2 degree
   * 'DEFER' in 3 degree
   * 1+2*3-1 + - both main operation
   */
  int mindegree = 1000;
  int min_degree_position = -1;
  int degree;
  for (int i = p; i <= q; i++)
  {
    if ((!if_calculate_token(tokens[i])) || (if_in_paranthese(p, q, i)))
    {
      continue;
    }
    // not in paranthese
    degree = token_degree(tokens[i]);
    if (degree < mindegree)
    {
      mindegree = degree;
      min_degree_position = i;
    }
  }
  return min_degree_position;
}

static int token_degree(Token t)
{
  if (t.type == TK_EQ || t.type == TK_NEQ)
  {
    return 1;
  }
  else if (t.type == '+' || t.type == '-')
  {
    return 2;
  }
  else if (t.type == '*' || t.type == '/')
  {
    return 3;
  }
  else if (t.type == TK_DEREF)
  {
    return 4;
  }
  else
  {
    return 0;
  }
}

static bool if_calculate_token(Token t)
{
  return (t.type == '+') || (t.type == '-') || (t.type == '*') || (t.type == '/') || (t.type == TK_DEREF) || (t.type == TK_EQ) || (t.type == TK_NEQ);
}

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
    if (tokens[i].type == '(')
    {
      in_paranthess = true;
      left_paranthese_num++;
    }
    else if (tokens[i].type == ')')
    {
      left_paranthese_num--;
      if (left_paranthese_num == 0)
      {
        in_paranthess = false;
      }
    }
  }
  return false;
}