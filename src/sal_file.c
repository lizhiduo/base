/******************************************************************************
*  Copyright (C), 2001-2022
*
*******************************************************************************
*  File Name     : sal_file.c
*  Version       : Initial Draft
*  Author        : lizhiduo
*
*
*  History:
* 
*       1.  Date         : 2018/9/2
*           Author       : lizhiduo
*           Modification : Created file
******************************************************************************/

/*==============================================*
 *      include header files                    *
 *----------------------------------------------*/
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>

#include "sal_file.h"
#include "sal_trace.h"
#include "sal_macro.h"

/*==============================================*
 *      constants or macros define              *
 *----------------------------------------------*/
#define SAL_FILE_MODE_SIZE (8)
#define FILE_NAME_SIZE (64)

typedef struct tagSAL_FILE
{
    FILE *fd;
    INT8 name[FILE_NAME_SIZE];
    UINT32 size;
    UINT32 curPos;
    UINT8 mode;
}SAL_FILE, *PSAL_FILE;

/*==============================================*
 *      project-wide global variables           *
 *----------------------------------------------*/



/*==============================================*
 *      routines' or functions' implementations *
 *----------------------------------------------*/
/*****************************************************************************
*   Prototype    : SAL_getFileStat
*   Description  :  
*   Input        : const PINT8 fileName  
*   Output       : None
*   Return Value : static INT32
*   Calls        : 
*   Called By    : 
*
*
*****************************************************************************/
static INT32 SAL_getFileStat(const PINT8 fileName)
{
    INT32 size = 0;
    struct stat st = {0};

    stat(fileName, &st);
    size = st.st_size;

    return size;
}

/*****************************************************************************
*   Prototype    : SAL_getSysFileMode
*   Description  :  
*   Input        : None
*   Output       : None
*   Return Value : static INT32
*   Calls        : 
*   Called By    : 
*
*
*****************************************************************************/
static INT32 SAL_getSysFileMode(UINT8 fileMode, INT8 *pSysFileMode)
{
    if (SAL_isNull(pSysFileMode))
    {
        SAL_ERROR("pSysFileMode is null\n");
        return SAL_FAIL;
    }

    switch (fileMode)
    {
        case SAL_FILEMODE_RDONLY :
            memcpy(pSysFileMode, "r", sizeof("r"));
            break;

        case SAL_FILEMODE_WRONLY :
            memcpy(pSysFileMode, "w", sizeof("w"));
            break;
        
        case SAL_FILEMODE_APPEND :
            memcpy(pSysFileMode, "a+", sizeof("a+"));
            break;
        
        case SAL_FILEMODE_TRUNC :
            memcpy(pSysFileMode, "w+", sizeof("w+"));
            break;
            
        default :
            SAL_ERROR("fileMode:%d err..\n", fileMode);
            return SAL_FAIL;
    }
    return SAL_OK;
}

INT32 SAL_fileOpen(const PINT8 fileName, UINT8 fileMode, SAL_fileHndl *hndl)
{
    INT32 ret = SAL_OK;
    PSAL_FILE pObj = NULL;
    INT8 mode[SAL_FILE_MODE_SIZE] = {0};

    if (SAL_isNull(fileName) || SAL_isNull(hndl))
    {
        SAL_ERROR("fileName or hndl is null..\n");
        return SAL_FAIL;
    }

    pObj = (PSAL_FILE)malloc(sizeof(SAL_FILE));
    if (SAL_isNull(pObj))
    {
        SAL_ERROR("malloc err..\n");
        return SAL_FAIL;
    }

    ret = SAL_getSysFileMode(fileMode, mode);
    if (SAL_isFail(ret))
    {
        SAL_ERROR("getSysFileMode err..\n");
        return SAL_FAIL;
    }

    pObj->fd = fopen(fileName, mode);
    if (SAL_isNull(pObj->fd))
    {
        SAL_ERROR("open [%s] err..\n", fileName);
        goto memErr;
    }

    memcpy(pObj->name, fileName, strlen(fileName));
    pObj->curPos = 0;
    pObj->size = SAL_getFileStat(fileName);
    pObj->mode = fileMode;

    *hndl = (SAL_fileHndl)pObj;

    return SAL_OK;
    
memErr:
    free(pObj);
    return SAL_FAIL;
}

INT32 SAL_fileClose(SAL_fileHndl hndl)
{
    INT32 ret = SAL_OK;
    PSAL_FILE pObj = NULL;

    if (SAL_isNull(hndl))
    {
        SAL_ERROR("hndl is null..\n");
        return SAL_FAIL;
    }

    pObj = (PSAL_FILE)hndl;

    ret = fclose(pObj->fd);
    if (SAL_isFail(ret))
    {
        SAL_ERROR("close err:[%x]..\n", ret);
        return SAL_FAIL;
    }

    free(pObj);

    return ret;
}

INT32 SAL_fileRead(SAL_fileHndl hndl, INT8 * buffer, UINT32 size, UINT32 * numBytes)
{
    PSAL_FILE pObj = NULL;
    UINT32    bytesRead = 0;

    if (SAL_isNull(hndl) || SAL_isNull(buffer) || SAL_isNull(numBytes))
    {
        SAL_ERROR("hndl or buffer or numBytes is null..\n");
        return SAL_FAIL;
    }

    pObj = (PSAL_FILE)hndl;
    if (SAL_FILEMODE_WRONLY == pObj->mode)
    {
        SAL_ERROR("file write only..\n");
        return SAL_FAIL;
    }

    bytesRead = fread(buffer, 1, size, pObj->fd);
    if (bytesRead > 0)
    {
        pObj->curPos += bytesRead;
        *numBytes = bytesRead;
    }
    else
    {
        SAL_ERROR("read err:[%x]..\n", errno);
        return SAL_FAIL;
    }

    return SAL_OK;
}

INT32 SAL_fileWrite(SAL_fileHndl hndl, INT8 * buffer, UINT32 size, UINT32 * numBytes)
{
    PSAL_FILE pObj = NULL;
    UINT32    bytesWrite = 0;

    if (SAL_isNull(hndl) || SAL_isNull(buffer) || SAL_isNull(numBytes))
    {
        SAL_ERROR("hndl or buffer or numBytes is null..\n");
        return SAL_FAIL;   
    }

    pObj = (PSAL_FILE)hndl;
    if (SAL_FILEMODE_RDONLY == pObj->mode)
    {
        SAL_ERROR("file read only..\n");
        return SAL_FAIL;
    }

    bytesWrite = fwrite(buffer, 1, size, pObj->fd);
    if (bytesWrite > 0)
    {
        pObj->curPos += bytesWrite;
        pObj->size += bytesWrite;
        *numBytes = bytesWrite;
    }
    else
    {
        SAL_ERROR("write err:[%x]..\n", errno);
        return SAL_FAIL;
    }

    return SAL_OK;
}

UINT32 SAL_fileGetSize(SAL_fileHndl hndl)
{
    PSAL_FILE pObj = NULL;

    if (SAL_isNull(hndl))
    {
        SAL_ERROR("hndl is null..\n");
        return SAL_FAIL;
    }

    pObj = (PSAL_FILE)hndl;

    return pObj->size;
}
INT32 SAL_fileFlush(SAL_fileHndl hndl)
{
    INT32 ret = SAL_OK;
    PSAL_FILE pObj = NULL;
    
    if (SAL_isNotNull(hndl))
    {
        SAL_ERROR("hndl is null..\n");
        return SAL_FAIL;
    }

    pObj = (PSAL_FILE)hndl;

    ret = fflush(pObj->fd);
    if (SAL_isFail(ret))
    {
        SAL_ERROR("fflush err..\n");
        return SAL_FAIL;
    }

    return ret;
}

