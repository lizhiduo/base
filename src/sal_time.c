/******************************************************************************
*
*  Copyright (C), 2001-2022
*
*******************************************************************************
*  File Name     : sal_time.c
*  Version       : Initial Draft
*  Author        : lizhiduo
*  Created       : 2018/12/3
*  Last Modified :
*  Description   :  
*  Function List :
*
*
*  History:
* 
*       1.  Date         : 2018/12/3
*           Author       : lizhiduo
*           Modification : Created file
*
******************************************************************************/

/*==============================================*
 *      include header files                    *
 *----------------------------------------------*/
#include <sys/select.h>
#include <sys/times.h>
#include <sys/time.h>
#include <errno.h>
#include <unistd.h>

#include "sal_time.h"


/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/


/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/
/*****************************************************************************
*   Prototype    : SAL_sleep
*   Description  : 精准秒延时
*   Input        : INT32 sec  
*   Output       : None
*   Return Value : INT32
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2018/12/3
*           Author       : lizhiduo
*           Modification : Created function
*
*****************************************************************************/
INT32 SAL_sleep(INT32 sec)
{
    INT32 err = 0;
    struct timeval tv = {0};

    tv.tv_sec = sec;
    do
    {
        err = select(0, NULL, NULL, NULL, &tv);
    }
    while (err < 0 && errno == EINTR);

    return SAL_OK;
}

/*****************************************************************************
*   Prototype    : SAL_msleep
*   Description  : 毫妙的精确延时，延时会休眠，不占cpu
*   Input        : INT32 mSec  
*   Output       : None
*   Return Value : INT32
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2018/12/3
*           Author       : lizhiduo
*           Modification : Created function
*
*****************************************************************************/
INT32 SAL_msleep(INT32 mSec)
{
    INT32 err = 0;
    struct timeval tv = {0};

    tv.tv_sec = mSec / 1000;
    tv.tv_usec = (mSec % 1000) * 1000;
    do
    {
        err = select(0, NULL, NULL, NULL, &tv);
    }
    while (err < 0 && errno == EINTR);

    return SAL_OK;
}

/*****************************************************************************
*   Prototype    : SAL_usleep
*   Description  : 微妙延时，延时会休眠，不占cpu
*   Input        : INT32 uSec  
*   Output       : None
*   Return Value : INT32
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2018/12/3
*           Author       : lizhiduo
*           Modification : Created function
*
*****************************************************************************/
INT32 SAL_usleep(INT32 uSec)
{
    INT32 err = 0;
    struct timeval tv = {0};

    tv.tv_usec = uSec;
    do
    {
        err = select(0, NULL, NULL, NULL, &tv);
    }
    while (err < 0 && errno == EINTR);

    return SAL_OK;
}

/*****************************************************************************
*   Prototype    : SAL_getSecTime
*   Description  : 获取系统秒的时间
*   Input        : None
*   Output       : None
*   Return Value : UINT64
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2018/12/3
*           Author       : lizhiduo
*           Modification : Created function
*
*****************************************************************************/
UINT64 SAL_getSecTime()
{
    struct timeval tv = {0};

    gettimeofday(&tv, NULL);

    return tv.tv_sec;
}

/*****************************************************************************
*   Prototype    : SAL_getTimeOfJiffies
*   Description  :  
*   Input        : None
*   Output       : None
*   Return Value : UINT64
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2018/12/9
*           Author       : lizhiduo
*           Modification : Created function
*
*****************************************************************************/
UINT64 SAL_getTimeOfJiffies(void)
{
    struct tms buf = {0};
    static UINT64 curTick = 0x7fffffff;
    UINT64 tmpTick = curTick;

    UINT64 tick = (UINT32)times(&buf);

    if (tick == (UINT32)-1)//溢出
    {
        tick = tmpTick;
    }
    if ((UINT32)tmpTick != (UINT32)tick)
    {
        while (tick < tmpTick)
        {
            tick += 0xffffffff;
            tick += 1;
        }
        if (curTick < tick)
        {
            curTick = tick;
        }
    }

    return curTick * (1000 / sysconf(_SC_CLK_TCK));
}

