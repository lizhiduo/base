/******************************************************************************
*
*  Copyright (C), 2001-2022
*
*******************************************************************************
*  File Name     : sal_file.h
*  Version       : Initial Draft
*  Author        : lizhiduo
*  Created       : 2018/9/2
*  Last Modified :
*  Description   : sal_file.c header file
*
*
*  History:
* 
*       1.  Date         : 2018/9/2
*           Author       : lizhiduo
*           Modification : Created file
*
******************************************************************************/
#ifndef __SAL_FILE_H__
#define __SAL_FILE_H__

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
typedef void* SAL_fileHndl;

typedef enum tagSAL_FILE_POS_EN
{
    SAL_FILEPOS_SEEKSET = 0x0,
    SAL_FILEPOS_SEEKCUR,
    SAL_FILEPOS_SEEKEND,
    SAL_FILEPOS_BUTT,
}SAL_FILE_PSO_EN;

typedef enum tagSAL_FILE_MODE_EN
{
    SAL_FILEMODE_RDONLY = 0,
    SAL_FILEMODE_WRONLY,
    SAL_FILEMODE_APPEND,
    SAL_FILEMODE_TRUNC,
    SAL_FILEMODE_BUTT,
}SAL_FILE_MODE_EN;

/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/
/*****************************************************************************
*   Prototype    : SAL_fileOpen
*   Description  :  
*   Input        : const INT8 *fileName  
*                  UINT8 fileMode        
*                  SAL_fileHndl *hndl    
*   Output       : None
*   Return Value : INT32
*   Calls        : 
*   Called By    : 
*
*
*****************************************************************************/
INT32 SAL_fileOpen(const PINT8 fileName, UINT8 fileMode, SAL_fileHndl *hndl);

/*****************************************************************************
*   Prototype    : SAL_fileRead
*   Description  :  
*   Input        : SAL_fileHndl hndl  
*                  INT8 *buffer       
*                  UINT32 size        
*                  UINT32 *numBytes   
*   Output       : None
*   Return Value : INT32
*   Calls        : 
*   Called By    : 
*
*
*****************************************************************************/
INT32 SAL_fileRead(SAL_fileHndl hndl, INT8 *buffer, UINT32 size, UINT32 *numBytes);

/*****************************************************************************
*   Prototype    : SAL_fileWrite
*   Description  :  
*   Input        : SAL_fileHndl hndl  
*                  INT8 *buffer       
*                  UINT32 size        
*                  UINT32 *numBytes   
*   Output       : None
*   Return Value : INT32
*   Calls        : 
*   Called By    : 
*
*
*****************************************************************************/
INT32 SAL_fileWrite(SAL_fileHndl hndl, INT8 *buffer, UINT32 size, UINT32 *numBytes);

/*****************************************************************************
*   Prototype    : SAL_fileClose
*   Description  :  
*   Input        : SAL_fileHndl hndl  
*   Output       : None
*   Return Value : INT32
*   Calls        : 
*   Called By    : 
*
*
*****************************************************************************/
INT32 SAL_fileClose(SAL_fileHndl hndl);

/*****************************************************************************
*   Prototype    : SAL_fileGetSize
*   Description  :  
*   Input        : SAL_fileHndl hndl  
*   Output       : None
*   Return Value : UINT32
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*
*****************************************************************************/
UINT32 SAL_fileGetSize(SAL_fileHndl hndl);

/*****************************************************************************
*   Prototype    : SAL_fileFlush
*   Description  :  
*   Input        : SAL_fileHndl hndl  
*   Output       : None
*   Return Value : INT32
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*
*****************************************************************************/
INT32 SAL_fileFlush(SAL_fileHndl hndl);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __SAL_FILE_H__ */
