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

/*
* 编译器相关宏
*
* */
#if defined (__GNUC__)
/* use gcc special extension: #warning , __attribute__, etc.  */
#else
#error sample for gcc compiler
#endif

typedef void        VOID, *PVOID, **PPVOID;
typedef char        INT8, *PINT8, **PPINT8;
typedef short       INT16, *PINT16, **PPINT16;
typedef int         INT32, *PINT32, **PPINT32;
typedef long long   INT64, *PINT64, **PPINT64;

typedef unsigned char       UINT8, *PUINT8, **PPUINT8;
typedef unsigned short       UINT16, *PUINT16, **PPUINT16;
typedef unsigned int        UINT32, *PUINT32, **PPUINT32;
typedef unsigned long long  UINT64, *PUINT64, **PPUINT64;

typedef void * Handle;
typedef enum { SAL_FALSE, SAL_TRUE} BOOL;


#ifndef SAL_NULL
#define SAL_NULL ((void *) 0)
#endif

#ifndef SUCCESS
#define SUCCESS (0)
#endif

#ifndef FAILURE
#define FAILURE (-1)
#endif

/*
* 编译期间 检查 类型 占用空间
* */
#define ASSERT_CHECK_TYPE(type, result) typedef char result[(type) ? SUCCESS : FAILURE]

ASSERT_CHECK_TYPE(sizeof(UINT8)==1, typeUINT8WrongSize);
ASSERT_CHECK_TYPE(sizeof(UINT16)==2, typeUINT16WrongSize);
ASSERT_CHECK_TYPE(sizeof(UINT32)==4, typeUINT32WrongSize);
ASSERT_CHECK_TYPE(sizeof(UINT64)==8, typeUINT64WrongSize);
ASSERT_CHECK_TYPE(sizeof(INT8)==1, typeINT8WrongSize);
ASSERT_CHECK_TYPE(sizeof(INT16)==2, typeINT16WrongSize);
ASSERT_CHECK_TYPE(sizeof(INT32)==4, typeINT32WrongSize);
ASSERT_CHECK_TYPE(sizeof(INT64)==8, typeINT64WrongSize);

#ifdef __cplusplus
}
#endif

#endif

