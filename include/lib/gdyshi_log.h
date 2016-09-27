/******************************************************************************
 * Copyright: 2012, gdyshi,Ltd.
 * 
 * File name: debug.h
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
#ifndef _GDYSHI_LOG_H_
#define _GDYSHI_LOG_H_

#ifdef __cplusplus
extern "C" {
#endif

/* ----------------------------可修改的配置-------------------------------------------- */

/* ----------------------------不可修改的配置-------------------------------------------- */
#define GDYSHI_LOG_STR_FATAL    "FTL"
#define GDYSHI_LOG_STR_PERROR   "PER"
#define GDYSHI_LOG_STR_ASSERT    "AST"
#define GDYSHI_LOG_STR_ERROR   "ERR"
#define GDYSHI_LOG_STR_WARNING    "WAR"
#define GDYSHI_LOG_STR_INFO    "INF"
#define GDYSHI_LOG_STR_POS    "POS"

#define GDYSHI_LOG_LEVEL_MASK   ((gdyshi_u8)0xff)/* 打印级别掩码 */
#define GDYSHI_LOG_LEVEL_FATAL   ((gdyshi_u8)0)/* 只打印致命错误 */
#define GDYSHI_LOG_LEVEL_ERROR   ((gdyshi_u8)1)/* 打印错误以上级别 */
#define GDYSHI_LOG_LEVEL_WARNING   ((gdyshi_u8)2)/* 打印警告以上级别 */
#define GDYSHI_LOG_LEVEL_INFO   ((gdyshi_u8)3)/* 打印调试信息以上级别 */

#define GDYSHI_LOG_LITE_MASK   (0xff00)/* 精简打印开关掩码 */
#define GDYSHI_LOG_LITE_MODULE   (0x100)/* 模块打印开关 */
#define GDYSHI_LOG_LITE_TIME   (0x200)/* 时间打印开关 */
#define GDYSHI_LOG_LITE_FILE   (0x400)/* 文件打印开关 */
#define GDYSHI_LOG_LITE_LINE   (0x800)/* 行号打印开关 */
#define GDYSHI_LOG_LITE_FUNC   (0x1000)/* 函数打印开关 */

#define __MODULE_NAME__     "default"
#ifdef GDYSHI_DEBUG
#define LOG_VALUE   GDYSHI_LOG_LEVEL_INFO | GDYSHI_LOG_LITE_MODULE | GDYSHI_LOG_LITE_FUNC | GDYSHI_LOG_LITE_LINE | GDYSHI_LOG_LITE_TIME
#else
#define LOG_VALUE   GDYSHI_LOG_LEVEL_ERROR | GDYSHI_LOG_LITE_MODULE | GDYSHI_LOG_LITE_LINE
#endif /* _DEBUG */

extern void gdyshi_print_out(const char *fmt1, gdyshi_u32 log_value, const char *fmt2, const char *module_name, const char *file, int line, const char *func, ...);

#undef GDYSHI_DEBUG_POS
#define GDYSHI_DEBUG_POS() gdyshi_print_out(GDYSHI_LOG_STR_POS, LOG_VALUE, "\n", __MODULE_NAME__, __FILE__, __LINE__, __FUNCTION__)
#undef GDYSHI_DEBUG_INFO
#define GDYSHI_DEBUG_INFO(___fmt, ...) gdyshi_print_out(GDYSHI_LOG_STR_INFO, LOG_VALUE, ___fmt, __MODULE_NAME__, __FILE__, __LINE__, __FUNCTION__,##__VA_ARGS__)
#undef GDYSHI_DEBUG_WARNING
#define GDYSHI_DEBUG_WARNING(___fmt, ...)  gdyshi_print_out(GDYSHI_LOG_STR_WARNING, LOG_VALUE, ___fmt, __MODULE_NAME__, __FILE__, __LINE__, __FUNCTION__,##__VA_ARGS__)
#undef GDYSHI_DEBUG_ERROR
#define GDYSHI_DEBUG_ERROR(___fmt, ...) gdyshi_print_out(GDYSHI_LOG_STR_ERROR, LOG_VALUE, ___fmt, __MODULE_NAME__, __FILE__, __LINE__, __FUNCTION__,##__VA_ARGS__)
#undef GDYSHI_DEBUG_FATAL
#define GDYSHI_DEBUG_FATAL(___fmt, ...) gdyshi_print_out(GDYSHI_LOG_STR_FATAL, LOG_VALUE, ___fmt, __MODULE_NAME__, __FILE__, __LINE__, __FUNCTION__,##__VA_ARGS__)
#undef GDYSHI_PERROR
#ifdef GDYSHI_USE_STD_LIBC
#include <errno.h>
#define GDYSHI_PERROR(___fmt) gdyshi_print_out(GDYSHI_LOG_STR_PERROR, LOG_VALUE, ___fmt, __MODULE_NAME__, __FILE__, __LINE__, __FUNCTION__,":%s\n", strerror(errno))
#else
#define GDYSHI_PERROR(___fmt) gdyshi_print_out(GDYSHI_LOG_STR_PERROR, LOG_VALUE, ___fmt, __MODULE_NAME__, __FILE__, __LINE__, __FUNCTION__)
#endif /* GDYSHI_USE_STD_LIBC */

#ifdef GDYSHI_LOG_FILE
extern gdyshi_smcu gdyshi_log_init(const char *file_name);
#undef GDYSHI_LOG_INIT
#define GDYSHI_LOG_INIT(__filename) gdyshi_log_init(__filename)
#endif /* GDYSHI_LOG_FILE */

#ifdef __cplusplus
}
#endif

#endif /* _GDYSHI_DEBUG_H_ */
/*----------------------------------END OF FILE debug.h-------------------------------*/
