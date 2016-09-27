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
#ifndef _GDYSHI_INCLUDES_H_
#define _GDYSHI_INCLUDES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "proj_comm_config.h"
#include "gdyshi_comm_include.h"

#ifdef GDYSHI_MODULE_LOG
#include "gdyshi_log.h"
#endif

#ifdef GDYSHI_MODULE_STACK
#include "gdyshi_stack.h"
#endif

#ifdef GDYSHI_MODULE_RING_BUFFER
#include "gdyshi_ring_buffer.h"
#endif

#ifdef GDYSHI_MODULE_HEAP
#include "gdyshi_heap.h"
#endif

#ifdef GDYSHI_MODULE_LIST
#include "gdyshi_list.h"
#endif

#ifdef GDYSHI_MODULE_TIMER
#include "gdyshi_timer.h"
#endif

#ifdef __cplusplus
}
#endif

#endif /* _GDYSHI_INCLUDES_H_ */
/*----------------------------------END OF FILE includes.h-------------------------------*/
