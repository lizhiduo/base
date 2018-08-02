/*************************************************************************
	> File Name: main.c
	> Author: 
	> Mail: 
	> Created Time: 2018年06月02日 星期六 21时03分28秒
 ************************************************************************/

#include <stdio.h>
#include "sal_trace.h"
#include "sal_types.h"
#include "sal_macro.h"

struct numbers {
        int one;
        int two;
        int three;

} n;



INT32 main(INT32 argc, PINT8 argv[])
{
    int *ptr = &n.two;
    struct numbers *n_ptr = SAL_NULL;
    
    n.one = 1;
    n.three = 3;

    n_ptr = SAL_CONTAINER_OF(ptr, struct numbers, two);
    
    SAL_INFO("%d %d\n", n_ptr->one, n_ptr->three);
    SAL_INFO("hello world\n");
    SAL_WARN("hello world\n");
    SAL_ERROR("hello world\n");
    SAL_DEBUG("hello world\n");
    

    return SUCCESS;
}

