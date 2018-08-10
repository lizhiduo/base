/*************************************************************************
	> File Name: include/sal_macro.h
	> Author: 
	> Mail: 
	> Created Time: 2018年08月02日 星期四 23时15分21秒
 ************************************************************************/

#ifndef _SAL_MACRO_H
#define _SAL_MACRO_H

//#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
* 计算元素的个数
* */
#define SAL_ARRAY_SIZE(arr) (sizeof(arr)/sizeof((arr)[0]))

/**
 * @ref https://stackoverflow.com/questions/3437404/min-and-max-in-c
 */
#define SAL_MIN(a, b) ((a) < (b) ? (a) : (b))
#define SAL_MAX(a, b) ((a) > (b) ? (a) : (b))

/**
 * 计算结构体中 成员的偏移位置
 */
#define SAL_OFFSETOF(type, member) ((size_t) &((type *)0)->member)

/*
 * @des cast a member of a structure out to the containing structure
 * @usage
 * struct container {
 *     int some_other_data;
 *     int this_data;
 * }c;
 * int *my_ptr = c.this_data;
 * container *ptr = (container *)SAL_CONTAINER_OF(my_ptr, structure container, this_data);
 *
 * @ref: https://stackoverflow.com/questions/15832301/understanding-container-of-macro-in-the-linux-kernel
 * @ref: https://gcc.gnu.org/onlinedocs/gcc/Typeof.html
 * */

#define SAL_CONTAINER_OF(ptr, type, member) ({          \
const typeof( ((type *)0)->member  ) *__mptr = (ptr);    \
                 (type *)( (char *)__mptr - SAL_OFFSETOF(type,member)  );})


#ifdef __cplusplus
}
#endif

#endif

