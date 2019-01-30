/******************************************************************************
*
*  Copyright (C), 2001-2022
*
*******************************************************************************
*  File Name     : sal_queue.h
*  Version       : Initial Draft
*  Author        : lizhiduo
*  Created       : 2019/1/27
*  Last Modified :
*  Description   : sal_queue.h header file
*  Function List :
*
*
*  History:
* 
*       1.  Date         : 2019/1/27
*           Author       : lizhiduo
*           Modification : Created file
*
******************************************************************************/
#ifndef __SAL_QUEUE_H__
#define __SAL_QUEUE_H__

/*==============================================*
 *      include header files                    *
 *----------------------------------------------*/
#include "sal_types.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/
typedef struct tagQUE_NODE_S
{
    UINT32 idx;                      ///< 节点序号
    struct tagQUE_NODE_S *pNextNode; ///< 下一个节点指针
    PVOID pData;                     ///< 节点数据
} QUE_NODE_S, *PQUE_NODE_S;

typedef struct tagQUE_HNDL_S
{
    PQUE_NODE_S pHeadNode;  ///< 头节点
    PQUE_NODE_S pTailNode;  ///< 尾节点
    UINT32 cnt;             ///< 节点个数
} QUE_HNDL_S, *PQUE_HNDL_S;

/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/
PQUE_NODE_S SAL_quePop(PQUE_HNDL_S pQueHndl);
INT32 SAL_quePush(PQUE_HNDL_S pQueHndl, PQUE_NODE_S pQueNode);
PQUE_NODE_S SAL_quePeep(PQUE_HNDL_S pQueHndl);
UINT32 SAL_queGetNodeNum(PQUE_HNDL_S pQueHndl);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __SAL_QUEUE_H__ */

