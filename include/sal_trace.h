/*************************************************************************
	> File Name: sal_print.h
	> Author: 
	> Mail: 
	> Created Time: 2018年06月02日 星期六 20时44分18秒
 ************************************************************************/

#ifndef _SAL_PRINT_H
#define _SAL_PRINT_H

#ifdef __KERNEL__
#include <linux/kernel.h>

#define SAL_print printk

#else
#include <stdio.h>

#define SAL_print printf
#endif

/* Define Terminal display Colors */
#define NONE        "\033[m"
#define RED         "\033[0;31m"
#define GREEN       "\033[0;32m"
#define BLUE        "\033[0;33m"
#define PURPLE      "\033[0;34m"
#define CYAN        "\033[0;35m"
#define GRAY        "\033[1;30m"
#define YELLOW      "\033[1;33m"
#define WHITE       "\033[1;37m"


#define SAL_printf(fmt, args ...) \
        do \
        { \
            SAL_print(fmt, ## args); \
        } \
        while(0)

#define SAL_ERROR(fmt, args ...) \
        do \
        { \
            SAL_print(RED "ERROR|%s|%s|%d: " fmt NONE, \
                      __FILE__, __func__, __LINE__,  ## args); \
        } \
        while(0)

#define SAL_WARN(fmt, args ...) \
        do \
        { \
            SAL_print(YELLOW "WARN|%s|%s|%d: " fmt NONE, \
                      __FILE__, __func__, __LINE__,  ## args); \
        } \
        while(0)


#define SAL_INFO(fmt, args ...) \
        do \
        { \
            SAL_print(GREEN "INFO|%s|%s|%d: " fmt NONE, \
                      __FILE__, __func__, __LINE__,  ## args); \
        } \
        while(0)
#ifdef DEBUG
#define SAL_DEBUG(fmt, args ...) \
        do \
        { \
            SAL_print(CYAN "DEBUG|%s|%s|%d: " fmt NONE, \
                      __FILE__, __func__, __LINE__,  ## args); \
        } \
        while(0)
#else

#define SAL_DEBUG(fmt, args ...)

#endif

#endif

