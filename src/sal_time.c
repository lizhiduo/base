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
#include <time.h>

#include "sal_time.h"
#include "sal_trace.h"
#include "sal_macro.h"

/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/
typedef struct tagTIME_INTERVAL
{
    clock_t begin; 
    clock_t end;
}TIME_INTERVAL;

/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/
static TIME_INTERVAL g_TimeInterval;


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
*   Prototype    : SAL_getTimeStr
*   Description  :  
*   Input        : void *buf  
*   Output       : None
*   Return Value : INT32
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
INT32 SAL_getTimeStr(void *buf, UINT32 bufLen)
{
    time_t rawtime = 0;
    struct tm * timeinfo = NULL;

    // 时间格式化字符串长度不能小于16
    if (SAL_isNull(buf) || bufLen < 16)
    {
        SAL_ERROR("buf is NULL\n");
        return SAL_FAIL;
    }
    
    time(&rawtime);

    timeinfo = localtime(&rawtime);

    timeinfo->tm_year += 1900;
    timeinfo->tm_mon += 1;

    SAL_INFO("%04d%02d%02d-%02d%02d%02d\n", timeinfo->tm_year, 
        timeinfo->tm_mon, timeinfo->tm_mday, timeinfo->tm_hour, 
        timeinfo->tm_min, timeinfo->tm_sec);

   sprintf(buf, "%04d%02d%02d-%02d%02d%02d", timeinfo->tm_year, 
        timeinfo->tm_mon, timeinfo->tm_mday, timeinfo->tm_hour, 
        timeinfo->tm_min, timeinfo->tm_sec);
   
    return SAL_OK;
}

INT32 SAL_getStartTime()
{
    g_TimeInterval.begin = clock();

    return SAL_OK;
}

INT32 SAL_getEndTime()
{
    g_TimeInterval.end = clock();

    return SAL_OK;
}

INT32 SAL_calcTimeInterval()
{
    double tmp = 0;

    tmp = (double)(g_TimeInterval.end - g_TimeInterval.begin)
                    / CLOCKS_PER_SEC;

     SAL_INFO("time is: %lf ms\n", tmp * 1000);

     return SAL_OK;
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

