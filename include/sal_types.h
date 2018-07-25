/*************************************************************************
	> File Name: sal_types.h
    > describe: 
    > Author: 
	> Mail: 
	> Created Time: 2018年07月14日 星期六 17时14分03秒
 ************************************************************************/

#ifndef _SAL_TYPES_H
#define _SAL_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void        VOID, *PVOID, **PPVOID;
typedef char        INT8, *PINT8, **PPINT8;
typedef short       INT16, *PINT16, **PPINT16;
typedef int         INT32, *PINT32, **PPINT32;
typedef long long   INT64, *PINT64, **PPINT64;

typedef unsigned char       UINT8, *PUINT8, **PPUINT8;
typedef unsigned char       UINT16, *PUINT16, **PPUINT16;
typedef unsigned int        UINT32, *PUINT32, **PPUINT32;
typedef unsigned long long  UINT64, *PUINT64, **PPUINT64;

//typedef int BOOL;
#ifndef TRUE
#define TRUE (1)
#endif
#ifndef FALSE
#define FALSE (0)
#endif

#ifndef OK
#define OK (0)
#endif

#ifndef FAIL
#define FAIL (-1)
#endif

#ifdef __cplusplus
}
#endif

#endif

