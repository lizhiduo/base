/*************************************************************************
	> File Name: src/sal_thread.c
	> Author: 
	> Mail: 
	> Created Time: 2018年08月17日 星期五 21时22分39秒
 ************************************************************************/
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/prctl.h>

#include "sal_thread.h"
#include "sal_macro.h"

#define MAX_THRD_NAME_CNT (32)


typedef struct tag_SAL_THREAD_S
{
    pthread_t        hndl;
    INT8             thrdName[MAX_THRD_NAME_CNT + 1];
    SAL_THREAD_SET_S set;
} SAL_THREAD_S, *PSAL_THRD_S;

/**
 * @brief 线程回调函数
 * 
 * @param[in] argv 输入参数指针
 *
 * @return
 *     @retval NULL
 */
static PVOID SAL_thrdCb(PVOID argv)
{
    PVOID       ret      = NULL;
    PSAL_THRD_S pthrdObj = NULL;
    
    if (SAL_isNull(argv))
    {
        SAL_ERROR("argv is null\n");
        return NULL;
    }
    
    pthrdObj = (PSAL_THRD_S)argv;

    prctl(PR_SET_NAME, pthrdObj->thrdName);
    
    ret = pthrdObj->set.cb(pthrdObj->set.cbArgv);
    
    return ret;
}

/*****************************************************************************
*   Prototype    : SAL_getThrdPolicy
*   Description  :  
*   Input        : UINT8 usrPolicy   
*                  UINT8 *sysPolicy  
*   Output       : None
*   Return Value : static INT32
*****************************************************************************/
static INT32 SAL_getThrdPolicy(UINT8 usrPolicy, UINT8 *sysPolicy)
{
    if (SAL_isNull(sysPolicy))
    {
        SAL_ERROR("sysPolicy is NULL\n");
        return SAL_FAIL;
    }

    switch ( usrPolicy )
    {
        case SAL_SCHED_OTHER :
            *sysPolicy = SCHED_OTHER;
            break;
        case SAL_SCHED_FIFO :
            *sysPolicy = SCHED_FIFO;
            break;
        case SAL_SCHED_RR :
            *sysPolicy = SCHED_RR;
            break;
        default:
            SAL_ERROR("err policy[%d]\n", usrPolicy);
            break;
    }
    
    return SAL_OK;
}

/*****************************************************************************
*   Prototype    : SAL_initThrdAttr
*   Description  :  
*   Input        : SAL_THREAD_S *pObj  
*   Output       : None
*   Return Value : static INT32
*****************************************************************************/
static INT32 SAL_initThrdAttr(SAL_THREAD_S *pObj)
{
    INT32 ret = SAL_OK;
    UINT8 thrdPolicy = 0;
    pthread_attr_t thrdAttr = {0};
    struct sched_param schedprm = {0};

    if (SAL_isNull(pObj))
    {
        SAL_ERROR("pObj is NULL\n");
        return SAL_FAIL;
    }

    ret = pthread_attr_init(&thrdAttr);
    if (SAL_isFail(ret))
    {
        SAL_ERROR("init thrdAttr fail\n");
        return SAL_FAIL;
    }

    if (SAL_THRD_STACK_DEF_SIZE != pObj->set.stackSize)
    {
        ret = pthread_attr_setstacksize(&thrdAttr, pObj->set.stackSize);
        if (SAL_isFail(ret))
        {
            SAL_ERROR("setstacksize err\n");
            goto attrErr;
        }
    }

    ret = SAL_getThrdPolicy(pObj->set.policy, &thrdPolicy);
    if (SAL_isFail(ret))
    {
        goto attrErr;
    }

    /* 创建线程默认继承父线程的调度优先级，需要设置 inheritsched为
        PTHREAD_EXPLICIT_SCHED，自己设置的才能生效。
    */
    ret |= pthread_attr_setinheritsched(&thrdAttr, PTHREAD_EXPLICIT_SCHED);
    ret |= pthread_attr_setschedpolicy(&thrdAttr, thrdPolicy);
    if (SAL_isFail(ret))
    {
        SAL_ERROR("setschedpolicy err\n");
        goto attrErr;
    }

    schedprm.sched_priority = (pObj->set.priority < SAL_THRD_PRI_MIN(thrdPolicy))
                            ? SAL_THRD_PRI_MIN(thrdPolicy) : pObj->set.priority;
    schedprm.sched_priority= (pObj->set.priority > SAL_THRD_PRI_MAX(thrdPolicy))
                            ? SAL_THRD_PRI_MAX(thrdPolicy) : pObj->set.priority;

   ret = pthread_attr_setschedparam(&thrdAttr, &schedprm);
   if (SAL_isFail(ret))
   {
       SAL_ERROR("setschedparam err\n");
        goto attrErr;
   }

   /*
    @see pthread_create Notes
    A thread may either be joinable or detached.  If a thread is joinable, then another thread can call  pthread_join(3) to  wait  
    for  the  thread  to terminate and fetch its exit status.    
    @see pthread_attr_setdetachstate
    The default setting of the detach state attribute in a newly initialized thread attributes  object  is  PTHREAD_CREATE_JOINABLE.
   */
    ret = pthread_attr_setdetachstate(&thrdAttr, PTHREAD_CREATE_DETACHED);
    if (SAL_isFail(ret))
    {
        SAL_ERROR("setdetachstate err\n");
        goto attrErr;
    }

    ret = pthread_create(&pObj->hndl, &thrdAttr, SAL_thrdCb, pObj);
    if (SAL_isFail(ret))
    {
        SAL_ERROR("create err:%x\n", ret);
        goto attrErr;
    }

//    ret = pthread_setname_np(pObj->hndl, pObj->thrdName);
//    CHECK_RET_ERR(ret);
    
    return ret;
    
attrErr:
    pthread_attr_destroy(&thrdAttr);
    
    return ret;
}


INT32 SAL_thrdCreate(SAL_thrdHndl *hndl, SAL_THREAD_SET_S *set)
{
    INT32        ret = SAL_OK;
    UINT32       nameLen = 0;
    SAL_THREAD_S *pObj = SAL_NULL;

    SAL_ASSERT_NULL(set);
    SAL_ASSERT_NULL(hndl);
    
    if (SAL_isNull(set) || SAL_isNull(hndl))
    {
        SAL_ERROR("set or hndl is null\n");
        return SAL_FAIL;
    }
    
    pObj = (SAL_THREAD_S *)malloc(sizeof(*pObj));
    if (SAL_isNull(pObj))
    {
        SAL_ERROR("malloc err\n");
        return SAL_FAIL;
    }


    memcpy(&pObj->set, set, sizeof(*set));
    nameLen = SAL_MIN(MAX_THRD_NAME_CNT, strlen(pObj->set.name));
    strncpy(pObj->thrdName, pObj->set.name, nameLen);
    SAL_INFO("thrdName:%s\n", pObj->thrdName);
    
    ret = SAL_initThrdAttr(pObj);
    if (SAL_isFail(ret))
    {
        SAL_ERROR("init thread err\n");
        goto thrdErr;
    }

    *hndl = pObj;
    return ret;
    
thrdErr:
    free(pObj);
    
    return ret;
}

INT32 SAL_thrdKill(SAL_thrdHndl hndl)
{   
    INT32 ret = SAL_OK;
    SAL_THREAD_S *pObj = SAL_NULL;

    
    if (SAL_isNull(hndl))
    {
        SAL_ERROR("hndl is Null\n");
        return SAL_FAIL;
    }

    pObj = (SAL_THREAD_S *)hndl;
    
    
    ret = pthread_cancel(pObj->hndl);
    if (SAL_isFail(ret))
    {
        SAL_ERROR("cancel err:%x\n", ret);
    }

    return ret;
}

