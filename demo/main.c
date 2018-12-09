/*************************************************************************
	> File Name: main.c
	> Author: 
	> Mail: 
	> Created Time: 2018年06月02日 星期六 21时03分28秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>

#include "sal_trace.h"
#include "sal_types.h"
#include "sal_macro.h"
#include "sal_list.h"
#include "sal_thread.h"
#include "sal_file.h"
#include "sal_time.h"

static BOOL bExit = SAL_FALSE;

static VOID MAIN_usage(VOID)
{
    SAL_print("press sample command as follows!\n");
    SAL_print("index:\n");
    SAL_print("\t 0) testSalTrace \n");
    SAL_print("\t 1) testSalMacro \n");
    SAL_print("\t 2) testSalList \n");
    SAL_print("\t 3) testSalAssert \n");
    SAL_print("\t 4) testSalThread \n");
    SAL_print("\t 5) testSalThreadStop \n");
    SAL_print("\t 6) testSalFile \n");
    SAL_print("\t 7) testSalTime \n");
    SAL_print("\t q) quit the whole sample \n");
    SAL_print("sample command: ");
    return;
}

static VOID MAIN_testSalTrace(VOID)
{
    SAL_INFO("hello world\n");
    SAL_WARN("hello world\n");
    SAL_ERROR("hello world\n");
    SAL_DEBUG("hello world\n");
    return;
}

static VOID MAIN_testSalMacro(VOID)
{
    struct numbers {
        INT32 one;
        INT32 two;
        INT32 three;
    } n;

    INT32 *ptr = &n.two;
    struct numbers *n_ptr = SAL_NULL;
    
    n.one = 1;
    n.three = 3;

    n_ptr = SAL_CONTAINER_OF(ptr, struct numbers, two);
    
    SAL_INFO("%d %d\n", n_ptr->one, n_ptr->three);
    
    return;
}

static VOID MAIN_testSalList(VOID)
{
    struct score
    {
        INT32 num;
        INT32 english;
        INT32 math;
        SAL_LIST_HEAD_S list;
    }stu1, stu2, stu3;
    
    SAL_LIST_HEAD(stScoreHead);
    SAL_LIST_HEAD_S * pPos = NULL;
    struct score *pTmp = NULL;


    stu1.num = 1;
    stu1.english = 58;
    stu1.math = 99;
    
    SAL_listAdd(&(stu1.list), &stScoreHead);

    stu2.num = 2;
    stu2.english = 58;
    stu2.math = 99;
    
    SAL_listAdd(&(stu2.list), &stScoreHead);
    
    stu3.num = 3;
    stu3.english = 58;
    stu3.math = 99;
    
    SAL_listAdd(&(stu3.list), &stScoreHead);

    SAL_LIST_FOR_EACH(pPos, &stScoreHead)
    {
        pTmp = SAL_LIST_ENTRY(pPos, struct score, list);
        SAL_INFO("num:%d english:%d match:%d\n", pTmp->num, pTmp->english, pTmp->math);
    }

    return;
}

static VOID MAIN_testSalAssert()
{
    PUINT8 pbuf = SAL_NULL;

    SAL_ASSERT_NULL(pbuf);
    
}

PVOID MAIN_threadFun(PVOID args)
{
    UINT16 time = 0;
    
    while (1)
    {
        SAL_INFO("runtime %d\n", time);
        time++;
        sleep(1);
    }
    
    return SAL_NULL;
}

static SAL_thrdHndl hndl =SAL_NULL;
static VOID MAIN_testSalThread()
{
    SAL_THREAD_SET_S set = {0};

    set.name = "thrd1";
    set.policy = SAL_SCHED_RR;
    set.priority = 55;
    set.stackSize = 20480;
    set.cb = MAIN_threadFun;

    SAL_thrdCreate(&hndl, &set);
    
}

static void MAIN_testThrdStop()
{
    SAL_thrdKill(hndl);
    SAL_INFO("thrd is stop\n");
}

static void MAIN_testSalFile()
{
    SAL_fileHndl fileHndl = 0;
    INT8 wBuf[256] = "write test";
    INT8 rBuf[256] = {0};
    UINT32 bytes = 0;
    
    SAL_fileOpen("test", SAL_FILEMODE_WRONLY, &fileHndl);

    SAL_fileWrite(fileHndl, wBuf, 256, &bytes);

    SAL_fileRead(fileHndl, rBuf, 256, &bytes);

    SAL_fileClose(fileHndl);
}

static void MAIN_testSalTime()
{
    UINT64 start = 0, end = 0;
    UINT8 time[16] = {0};

    start = SAL_getTimeOfJiffies();
    SAL_usleep(10*1000);
    end = SAL_getTimeOfJiffies();

    SAL_INFO("%lld\n", end - start);
    SAL_getStartTime();
    SAL_getTimeStr(time, SAL_ARRAY_SIZE(time));
    SAL_getEndTime();
  
    SAL_calcTimeInterval();
    SAL_INFO("%s\n", time);
    
}


INT32 main(INT32 argc, PINT8 argv[])
{
    UINT8 op = 0;
    
    while(1)
    {
        MAIN_usage();
        op = (UINT8)getchar();
        while (getchar() != '\n') { ; }

        switch (op)
        {
            case '0':
            {
                MAIN_testSalTrace();
                break;
            }
            case '1':
            {
                MAIN_testSalMacro();
                break;
            }
            case '2':
            {
                MAIN_testSalList();
                break;
            }
            case '3':
            {
                MAIN_testSalAssert();
                break;
            } 
            case '4':
            {
                MAIN_testSalThread();
                break;
            }
            case '5':
            {
                MAIN_testThrdStop();
                break;
            }
            case '6':
            {
                MAIN_testSalFile();
                break;
            }
            case '7':
            {
                MAIN_testSalTime();
                break;
            } 
            case 'q':
            case 'Q':
            {
                bExit = SAL_TRUE;
                break;
            }
            default :
            {
                SAL_WARN("input invaild! please try again.\n");
                break;            
            }
        }
        if (bExit)
        {
            SAL_INFO("DEMO EXIT...\n");
            break;
        }
    }

    return SAL_OK;
}

