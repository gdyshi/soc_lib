/******************************************************************************
 * Copyright: 2012, gdyshi,Ltd.
 * 
 * File name: common.h
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
#ifndef _GDYSHI_COMM_LIB_H_
#define _GDYSHI_COMM_LIB_H_

#ifdef GDYSHI_LOG
#include "gdyshi_log.h"
#endif /* GDYSHI_LOG */

#if !defined(ARRAY_SIZE)
#define ARRAY_SIZE(array) (sizeof(array)/sizeof(array[0])) 
#endif

#ifndef offsetof
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif

#ifndef container_of
/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:	the pointer to the member.
 * @type:	the type of the container struct this is embedded in.
 * @member:	the name of the member within the struct.
 *
 */
#define container_of(ptr, type, member) ({			\
    const void * __mptr = (ptr);    \
	(type *)((char *)__mptr - offsetof(type, member)); })
#endif
#ifdef WIN32
#define SNPRINTF  _snprintf
#else
#define SNPRINTF  snprintf
#endif /* GDYSHI_LOG_FILE */

#if 0
#define GDYSHI_MALLOC(__size)\
    malloc(__size);\    
    GDYSHI_DEBUG_INFO("memory alloc:0x%x\n",thisstruct->lan);
    
#define GDYSHI_FREE(__p)\
    {\
        free(__p);\    
        GDYSHI_DEBUG_INFO("memory free:0x%x\n",__p);\
    }
#endif /* if 0 end */

#ifdef GDYSHI_CHECK_PARM
#define GDYSHI_CHECK_POINTER(_p) \
    GDYSHI_ASSERT((NULL != _p), GDYSHI_EFAULT, "NULL pointer!\n")
#define GDYSHI_CHECK_SIZE(_s) \
    GDYSHI_ASSERT((0 < _s), GDYSHI_EINVAL, "invalid size!\n")
#define GDYSHI_CHECK_SIZE_EQUAL(_s) \
    GDYSHI_ASSERT((0 <= _s), GDYSHI_EINVAL, "invalid size!\n")
#define GDYSHI_CHECK_RANGE(_v, _min, _max) \
    GDYSHI_ASSERT(((_min < _v) && (_max > _v)), GDYSHI_EINVAL, "invalid range!\n")
#define GDYSHI_CHECK_RANGE_EQUAL(_v, _min, _max) \
    GDYSHI_ASSERT(((_min <= _v) && (_max >= _v)), GDYSHI_EINVAL, "invalid range!\n")

#else
#define GDYSHI_CHECK_POINTER(_p)
#define GDYSHI_CHECK_SIZE_EQUAL(_s)
#define GDYSHI_CHECK_SIZE(_s)
#define GDYSHI_CHECK_RANGE(_v, _min, max)
#define GDYSHI_CHECK_RANGE_EQUAL(_v, _min, max)
#endif /* GDYSHI_CHECK_PARM */
    
#define DO_FUNC(_fun) \
    ret = _fun; \
    if (0 > ret) \
    { \
       GDYSHI_DEBUG_ERROR("ret:%d\n",ret); \
    }
#define DO_FUNC_2ERR(_fun) \
    ret = _fun; \
    if (0 > ret) \
    { \
        GDYSHI_DEBUG_ERROR("ret:%d\n",ret); \
        goto err; \
    }
#if 0
#define WAIT_FOR_TIMES(_condition, _count) \
    do {
        gdyshi_u8 count = _count;
        while(_condition)
        {
            count--;
            if (0 == count)
            {
                break;
            }
        }
    }while(0)
#endif /* if 0 end */

#endif /* _GDYSHI_COMM_LIB_H_ */
/*----------------------------------END OF FILE common.h-------------------------------*/
