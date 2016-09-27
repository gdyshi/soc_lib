/******************************************************************************
 * Copyright: 2012, gdyshi,Ltd.
 * 
 * File name: includes.h
 * 
 * Description:  
 * - This file implements the follow functions:
 * - 
 * 
 * Author: gdyshi 
 * Date:  13:28pm, 26.Jun.2012
 * Modification History
 * --------------------
 * Date              Modifier    Problem N.O.                 Description
 * --------------------
 ******************************************************************************/
#ifndef _GDYSHI_COMM_INCLUDE_H_
#define _GDYSHI_COMM_INCLUDE_H_

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------- 系统通用头文件 -------------------------------*/
//#include <sys/types.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#ifdef GDYSHI_USE_STD_LIBC
#include <stdlib.h>
#endif /* GDYSHI_USE_STD_LIBC */

/*---------------------------------- 自定义头文件 -------------------------------*/

#include "gdyshi_comm_config.h"/* 自定义数据类型 */
#include "gdyshi_comm_types.h"/* 自定义数据类型 */
#include "gdyshi_comm_errno.h"/* 错误号、返回值头文件 */
#include "gdyshi_comm_debug.h"/* 调试定义头文件 */
#include "gdyshi_comm_lib.h"/* 通用库定义 */

#ifdef __cplusplus
}
#endif

#endif /* _GDYSHI_COMM_INCLUDE_H_ */
/*----------------------------------END OF FILE includes.h-------------------------------*/
