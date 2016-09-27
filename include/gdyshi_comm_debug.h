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
#ifndef _GDYSHI_COMM_DEBUG_H_
#define _GDYSHI_COMM_DEBUG_H_

#define GDYSHI_LOG_INIT(__filename) 
#define GDYSHI_DEBUG_POS()
#define GDYSHI_DEBUG_INFO(___fmt, ...)
#define GDYSHI_DEBUG_WARNING(___fmt, ...)
#define GDYSHI_DEBUG_ERROR(___fmt, ...)
#define GDYSHI_DEBUG_FATAL(___fmt, ...)
#define GDYSHI_PERROR(___fmt)
#ifdef GDYSHI_DEBUG
#define GDYSHI_ASSERT(___condition, retval, ___fmt, ...)    \
        do \
        {   \
            if (!(___condition))   \
            {   \
                GDYSHI_DEBUG_FATAL(___fmt, ##__VA_ARGS__);    \
                for(;;){;} \
            }   \
        }while(0)
#else
#define GDYSHI_ASSERT(___condition, retval, ___fmt, ...)    \
        do \
        {   \
            if (!(___condition))   \
            {   \
                GDYSHI_DEBUG_FATAL(___fmt, ##__VA_ARGS__);    \
                ret = retval; \
                return ret; \
            }   \
        }while(0)
#endif /* GDYSHI_DEBUG */


#endif /* _GDYSHI_COMM_DEBUG_H_ */
/*----------------------------------END OF FILE debug.h-------------------------------*/
