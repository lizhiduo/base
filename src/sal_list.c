/*************************************************************************
	> File Name: sal_list.c
	> Author: 
	> Mail: 
	> Created Time: 2018年08月05日 星期日 09时56分47秒
 ************************************************************************/

#include "sal_list.h"

VOID SAL_listHeadInit(SAL_LIST_HEAD_S *list)
{
    list->next = list;
    list->prev = list;
}

static VOID __SAL_listAdd(SAL_LIST_HEAD_S *new, SAL_LIST_HEAD_S *prev, SAL_LIST_HEAD_S *next)
{
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}

VOID SAL_listAdd(SAL_LIST_HEAD_S *new, SAL_LIST_HEAD_S *head)
{
    __SAL_listAdd(new, head, head->next);
}

VOID SAL_listAddTail(SAL_LIST_HEAD_S *new, SAL_LIST_HEAD_S *head)
{
    __SAL_listAdd(new, head->prev, head);
}

static VOID __SAL_listDel(SAL_LIST_HEAD_S *prev, SAL_LIST_HEAD_S *next)
{
    next->prev = prev;
    prev->next = next;
}

VOID SAL_listDel(SAL_LIST_HEAD_S *entry)
{
   __SAL_listDel(entry->prev, entry->next);
}

VOID SAL_listMove(SAL_LIST_HEAD_S *list, SAL_LIST_HEAD_S *    head)
{
    SAL_listDel(list);
    SAL_listAdd(list, head);
}

VOID SAL_listMoveTail(SAL_LIST_HEAD_S *list,                  SAL_LIST_HEAD_S *head)
{
    SAL_listDel(list);
    SAL_listAddTail(list, head);
}

INT32 SAL_listIsLast(const SAL_LIST_HEAD_S *list, const       SAL_LIST_HEAD_S *head)
{
    return list->next == head;
}

INT32 SAL_listIsEmpty(const SAL_LIST_HEAD_S *head)
{
    return head->next == head;
}

