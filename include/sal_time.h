/******************************************************************************
*
*  Copyright (C), 2001-2022
*
*******************************************************************************
*  File Name     : sal_time.h
*  Version       : Initial Draft
*  Author        : lizhiduo
*  Created       : 2018/12/3
*  Last Modified :
*  Description   : sal_time.h header file
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
#ifndef __SAL_TIME_H__
#define __SAL_TIME_H__

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


/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/
UINT64 SAL_getTimeOfJiffies();
INT32 SAL_msleep(INT32 mSec);
INT32 SAL_usleep(INT32 uSec);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __SAL_TIME_H__ */
