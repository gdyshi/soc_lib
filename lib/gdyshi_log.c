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
#include "gdyshi_includes.h"
#include "gdyshi_log.h"
#ifdef GDYSHI_USE_STD_TIME
#include <time.h>
#endif /* GDYSHI_USE_STD_TIME */


#ifdef GDYSHI_LOG_FILE
static FILE *log_fd;
#define __GDYSHI_PRINT_OUT(__string__) \
    do { \
        GDYSHI_PRINT_OUT(__string__); \
        if (NULL != log_fd) \
        { \
            fprintf(log_fd, __string__); \
            (void)fflush(log_fd); \
        } \
    }while(0)
#else
#define __GDYSHI_PRINT_OUT(__string__) \
    do { \
        GDYSHI_PRINT_OUT(__string__); \
    }while(0)
#endif /* GDYSHI_LOG_FILE */

void gdyshi_print_out(const char *fmt1, gdyshi_u32 log_value, const char *fmt2, const char *module_name, const char *file, int line, const char *func, ...)
{
    gdyshi_u8 in_level = 0;
    gdyshi_smcu buffer_len = 0;
    gdyshi_u32 value = 0;
    char buffer[GDYSHI_MAX_PRINT_BUFFER_LEN] = {0};
#ifdef GDYSHI_USE_STD_TIME
    time_t timep;
#endif /* GDYSHI_USE_STD_TIME */
    va_list argptr;

    value = log_value;
    if ((0 == strncmp(fmt1, GDYSHI_LOG_STR_FATAL, sizeof(GDYSHI_LOG_STR_FATAL))) ||
        (0 == strncmp(fmt1, GDYSHI_LOG_STR_PERROR, sizeof(GDYSHI_LOG_STR_PERROR))) ||
        (0 == strncmp(fmt1, GDYSHI_LOG_STR_ASSERT, sizeof(GDYSHI_LOG_STR_ASSERT))))
    {
        in_level = GDYSHI_LOG_LEVEL_FATAL;
    }
    else if (0 == strncmp(fmt1, GDYSHI_LOG_STR_ERROR, sizeof(GDYSHI_LOG_STR_ERROR)))
    {
        in_level = GDYSHI_LOG_LEVEL_ERROR;
    }
    else if (0 == strncmp(fmt1, GDYSHI_LOG_STR_WARNING, sizeof(GDYSHI_LOG_STR_WARNING)))
    {
        in_level = GDYSHI_LOG_LEVEL_WARNING;
    }
    else
    {
        in_level = GDYSHI_LOG_LEVEL_INFO;
    }
    if (in_level > (value & GDYSHI_LOG_LEVEL_MASK))
    {
        return;/* 级别不够，不打印 */
    }

    value &= GDYSHI_LOG_LITE_MASK;
#ifdef GDYSHI_USE_STD_TIME
    if (value & GDYSHI_LOG_LITE_TIME)
    {
        (void)time(&timep);
        buffer_len = (gdyshi_smcu)SNPRINTF(buffer,GDYSHI_MAX_PRINT_BUFFER_LEN,ctime(&timep));
        //buffer[strlen(buffer)-1] = 0;
        __GDYSHI_PRINT_OUT(buffer);
        buffer_len = 0;
    }
#endif /* GDYSHI_USE_STD_TIME */
    if (value & GDYSHI_LOG_LITE_MODULE)	
        buffer_len += (gdyshi_smcu)SNPRINTF(buffer+buffer_len,(GDYSHI_MAX_PRINT_BUFFER_LEN-buffer_len),"{%s}",module_name);
    buffer_len += (gdyshi_smcu)SNPRINTF(buffer+buffer_len,(GDYSHI_MAX_PRINT_BUFFER_LEN-buffer_len),"[%s]",fmt1);
    if (value & GDYSHI_LOG_LITE_FILE) 
        buffer_len += (gdyshi_smcu)SNPRINTF(buffer+buffer_len,(GDYSHI_MAX_PRINT_BUFFER_LEN-buffer_len),"<%s>",file);
    if (value & GDYSHI_LOG_LITE_LINE)
        buffer_len += (gdyshi_smcu)SNPRINTF(buffer+buffer_len,(GDYSHI_MAX_PRINT_BUFFER_LEN-buffer_len),"L%d:",line);
    if (value & GDYSHI_LOG_LITE_FUNC)
        buffer_len += (gdyshi_smcu)SNPRINTF(buffer+buffer_len,(GDYSHI_MAX_PRINT_BUFFER_LEN-buffer_len),"%s()",func);
    buffer_len += (gdyshi_smcu)SNPRINTF(buffer+buffer_len,(GDYSHI_MAX_PRINT_BUFFER_LEN-buffer_len),"%s","<->");
    va_start(argptr, func);
    buffer_len += (gdyshi_smcu)vsnprintf(buffer+buffer_len, (GDYSHI_MAX_PRINT_BUFFER_LEN-buffer_len), fmt2, argptr);
    va_end(argptr);
    __GDYSHI_PRINT_OUT(buffer);
}

#ifdef GDYSHI_LOG_FILE
gdyshi_smcu gdyshi_log_init(const char *file_name)
{
    gdyshi_smcu ret = 0;
    log_fd= fopen(file_name,"w");
    if (NULL == log_fd)
    {
        GDYSHI_PERROR("open file error");
        return GDYSHI_ENOENT;
    }
    return ret;
}
#endif /* GDYSHI_LOG_FILE */
/*----------------------------------END OF FILE debug.h-------------------------------*/
