/******************************************************************************
 * Copyright: 2012, gdyshi,Ltd.
 * 
 * File name: types.h
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
#ifndef _PROJ_COMM_CONFIG_H_
#define _PROJ_COMM_CONFIG_H_

typedef signed int gdyshi_smcu;
typedef unsigned int gdyshi_umcu;

/* ********************************* 功能开关 **************************************** */
#define GDYSHI_CHECK_PARM
#define GDYSHI_ENTER_CRITICAL()
#define GDYSHI_LEAVE_CRITICAL()
#define GDYSHI_USE_STD_LIBC /* 使用标准C库 */
#define GDYSHI_DEBUG

/* ********************************* 模块开关 **************************************** */
#define GDYSHI_MODULE_LOG
#define GDYSHI_MODULE_STACK
#define GDYSHI_MODULE_RING_BUFFER
#define GDYSHI_MODULE_HEAP
#define GDYSHI_MODULE_LIST
#define GDYSHI_MODULE_TIMER

/* ********************************* cunit **************************************** */

/* ********************************* encrypt **************************************** */

/* ********************************* filter **************************************** */

/* ********************************* heap **************************************** */

/* ********************************* list **************************************** */

/* ********************************* log **************************************** */
#ifdef  GDYSHI_MODULE_LOG
#define GDYSHI_MAX_PRINT_BUFFER_LEN   ((gdyshi_umcu)100)/* 打印缓冲区最大长度 */
#define GDYSHI_PRINT_OUT   printf   /* 打印函数 */
#ifdef GDYSHI_USE_STD_LIBC
/* 输出log到文件 */
#define GDYSHI_LOG_FILE
/* 使用标准时间函数 */
#define GDYSHI_USE_STD_TIME
#endif
/* 使用标准字符串格式错误输出 */
#define GDYSHI_USE_STRERROR
#endif /* #if GDYSHI_MODULE_LOG */

/* ********************************* queue **************************************** */

/* ********************************* stack **************************************** */

/* ********************************* timer **************************************** */
#ifdef GDYSHI_MODULE_TIMER
#define MS_PER_TICK (10)
#define GDYSHI_MAX_TIMER (10)
#endif /* GDYSHI_MODULE_TIMER */


#endif /* _PROJ_COMM_CONFIG_H_ */
/*----------------------------------END OF FILE types.h-------------------------------*/
