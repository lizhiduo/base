/*************************************************************************
	> File Name: main.c
	> Author: 
	> Mail: 
	> Created Time: 2018年06月02日 星期六 21时03分28秒
 ************************************************************************/

#include <stdio.h>
#include "sal_trace.h"
#include "sal_types.h"

INT32 main(INT32 argc, PINT8 argv[])
{
    
    SAL_INFO("hello world\n");
    SAL_WARN("hello world\n");
    SAL_ERROR("hello world\n");
    SAL_DEBUG("hello world\n");
    

    return OK;
}

