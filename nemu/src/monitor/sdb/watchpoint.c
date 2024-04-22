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

#include "sdb.h"

#define NR_WP 32

// typedef struct watchpoint
// {
//   int NO;
//   struct watchpoint *next;
//   char expression[32];
//   word_t old_value;
//   /* TODO: Add more members if necessary */

// } WP;

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;

void init_wp_pool()
{
  int i;
  for (i = 0; i < NR_WP; i++)
  {
    wp_pool[i].NO = i;
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
  }

  head = NULL;
  free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */
WP *new_wp(char *express)
{
  strcpy(free_->expression, express);
  bool success = false;
  free_->old_value = expr(express, &success);
  if (success == false)
  {
    panic("error happened in new_wp function\n");
  }
  WP *tmp = free_;
  free_ = free_->next;
  tmp->next = NULL; // 断开链接

  /**
   * append to head
   */
  if (head == NULL)
  {
    head = tmp;
    head->next = NULL;
  }
  else
  { // 尾插法
    WP *p = head;
    while (p->next)
    {
      p = p->next;
    }
    p->next = tmp;
  }

  return tmp;
}

void free_wp(WP *wp)
{
  /**
   * 将head的最后一个连接到free_
   */

  if (head == NULL)
  {
    panic("wp list is empty\n");
  }
  WP *p = head;
  while (p->next)
  {
    p = p->next;
  }
  p->next = free_;

  WP *before_p = head;
  while (before_p->next == p)
  {
    before_p = before_p->next;
  }
  before_p->next = NULL;
}

void iter_wps()
{
  WP *p = head;
  word_t new_value;
  bool success = false;
  while (p)
  {
    success = false;
    new_value = expr(head->expression, &success);
    if (success)
    {
      if (new_value != p->old_value)
      {
        // stop here and replace the value
        nemu_state.state = NEMU_STOP;
        p->old_value = new_value;
        Log("WATCH POINT REACH!\n");
      }
    }
    p = p->next;
  }
}
/**  head free_
 * layout: []->[]->[]->[]->[]->[]->[]->[]->[]->[]->[]
 *        head free_
 * layout: []  []->[]->[]->[]->[]->[]->[]->[]->[]->[]
 *        head    free_
 * layout: []->[]  []->[]->[]->[]->[]->[]->[]->[]->[]
 *        head        free_
 * layout: []->[]->[]  []->[]->[]->[]->[]->[]->[]->[]
 */