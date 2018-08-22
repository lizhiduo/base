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

static BOOL bExit = SAL_FALSE;

static VOID MAIN_usage(VOID)
{
    SAL_print("press sample command as follows!\n");
    SAL_print("index:\n");
    SAL_print("\t 0) testSalTrace \n");
    SAL_print("\t 1) testSalMacro \n");
    SAL_print("\t 2) testSalList \n");
    SAL_print("\t 3) testSalAssert \n");
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

VOID MAIN_testSalAssert()
{
    PUINT8 pbuf = SAL_NULL;

    SAL_ASSERT_NULL(pbuf);
    
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

