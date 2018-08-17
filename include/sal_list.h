/*************************************************************************
	> File Name: include/sal_list.h
	> Author: 
	> Mail: 
	> Created Time: 2018年08月04日 星期六 22时26分34秒
 ************************************************************************/

#ifndef _SAL_LIST_H
#define _SAL_LIST_H

#include "sal_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * get struct from this entry
 *
 */
#define SAL_LIST_ENTRY(ptr, type, member) \
    SAL_CONTAINER_OF(ptr, type, member)

/**
 * 
 *
 */
#define SAL_LIST_FOR_EACH(pos, head) \
    for ((pos) = (head)->next; (pos) != (head); (pos) = (pos)->next)

typedef struct tag_SAL_LIST_HEAD_S SAL_LIST_HEAD_S;
struct tag_SAL_LIST_HEAD_S
{
    SAL_LIST_HEAD_S *next;
    SAL_LIST_HEAD_S *prev;
};

/*
* 链表头静态初始化
* */
#define SAL_LIST_HEAD(name) \
   SAL_LIST_HEAD_S name = { &(name), &(name)  }

/*
* init the list 
* @list:  
* */
VOID SAL_listHeadInit(SAL_LIST_HEAD_S *list); 

/*
* Insert the new entry after the head
* @new: new entry to be added
* @head: list head to add it before 
* */
VOID SAL_listAdd(SAL_LIST_HEAD_S *new, SAL_LIST_HEAD_S *head);

/*
 * Insert the new entry before the head
 * @new: 
 * @head: 
 **/
VOID SAL_listAddTail(SAL_LIST_HEAD_S *new, SAL_LIST_HEAD_S *head);

/**
 * 
 *
 */
VOID SAL_listDel(SAL_LIST_HEAD_S *entry);

/**
 *
 *
 */
VOID SAL_listMove(SAL_LIST_HEAD_S *list, SAL_LIST_HEAD_S *head);

/**
 *
 *
 */
VOID SAL_listMoveTail(SAL_LIST_HEAD_S *list, SAL_LIST_HEAD_S *head);

/**
 *
 *
 */
INT32 SAL_listIsLast(const SAL_LIST_HEAD_S *list, const SAL_LIST_HEAD_S *head);

/**
 *
 *
 */
INT32 SAL_listIsEmpty(const SAL_LIST_HEAD_S *head);

#ifdef __cplusplus
}
#endif

#endif
