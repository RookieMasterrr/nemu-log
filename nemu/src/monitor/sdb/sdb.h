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

#ifndef __SDB_H__
#define __SDB_H__

#include <common.h>

typedef struct watchpoint
{
    int NO;
    struct watchpoint *next;
    char expression[32];
    word_t old_value;
    /* TODO: Add more members if necessary */

} WP;
word_t vaddr_read(vaddr_t addr, int len);
void free_wp(WP *wp);
WP *new_wp(char *express);

#define GET4Byte(address) vaddr_read(address, 4)

word_t expr(char *e, bool *success);

#endif
