/*************************************************************************
	> File Name: include/sal_thread.h
	> Author: 
	> Mail: 
	> Created Time: 2018年08月17日 星期五 21时13分45秒
 ************************************************************************/

#ifndef _SAL_THREAD_H
#define _SAL_THREAD_H

#include "sal_types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CALLBACK
#define SAL_THRD_STACK_DEF_SIZE (0)
#define SAL_THRD_PRI_MIN(policy) sched_get_priority_min(policy)
#define SAL_THRD_PRI_MAX(policy) sched_get_priority_max(policy)

#define SAL_THRD_PRI_DEF(policy) \
    (SAL_THRD_PRI_MIN(policy) \
     + SAL_THRD_PRI_MAX(policy)) / 2

typedef PVOID (CALLBACK *SAL_THRD_CB)(PVOID);

typedef Handl SAL_thrdHndl;

typedef enum
{
    SAL_SCHED_OTHER = 0,
    SAL_SCHED_FIFO,
    SAL_SCHED_RR,
}SAL_SCHED_POLICY_E;

typedef struct tag_SAL_THREAD_SET_S
{
    SAL_THRD_CB cb;
    PVOID       cbArgv;
    UINT32      stackSize;
    UINT8       policy;//调度策略
    UINT8       priority;//优先级
    PINT8       name;  
}SAL_THREAD_SET_S;

/**
 * Brief : 创建线程
 *
 * Input :
 *   @hndl :
 *   @set :
 *
 * Output :
 *
 * Return :
 *   
 */
INT32 SAL_thrdCreate(SAL_thrdHndl *hndl, SAL_THREAD_SET_S *set);

/**
 * Brief : 杀掉创建的线程
 *
 */
INT32 SAL_thrdKill(SAL_thrdHndl hndl);

#ifdef __cplusplus
}
#endif

#endif
