/**
 * \file
 *
 * \brief Ring buffer
 *
 * Copyright (c) 2011 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
#include "gdyshi_includes.h"
#include "gdyshi_stack.h"
     
#undef __MODULE_NAME__
#define __MODULE_NAME__     "STACK"
#undef LOG_VALUE
#define LOG_VALUE   (GDYSHI_LOG_LEVEL_INFO | GDYSHI_LOG_LITE_MODULE | GDYSHI_LOG_LITE_FUNC | GDYSHI_LOG_LITE_LINE | GDYSHI_LOG_LITE_TIME)

#ifdef GDYSHI_CRITICAL_USE_INT
#define GDYSHI_ENTER_STACK_CRITICAL() GDYSHI_DISABLE_GLOBAL_INT()
#define GDYSHI_LEAVE_STACK_CRITICAL() GDYSHI_ENABLE_GLOBAL_INT()
#else
static volatile gdyshi_smcu stack_critical = 1;
#define GDYSHI_ENTER_STACK_CRITICAL() \
    do { \
        while (0 >= stack_critical); \
        stack_critical--; \
    }while(0)
#define GDYSHI_LEAVE_STACK_CRITICAL() \
    do { \
        stack_critical++; \
    }while(0)
#endif /* GDYSHI_CRITICAL_USE_INT */

/**
 * \brief Function for initializing a ring buffer
 *
 * \param buffer pointer to the buffer to use as a ring buffer
 * \param buffer_num   the buffer_num of the ring buffer
 *
 * \retval struct ring_buffer a struct containing the ring buffer
 */
gdyshi_smcu gdyshi_stack_init(gdyshi_stack_t * stack, void * buffer_p,
                                                gdyshi_u8 nblks, gdyshi_u8 blksize)
{
    gdyshi_smcu ret = 0;
    
    GDYSHI_DEBUG_INFO("%d * %d\n", nblks, blksize);
    GDYSHI_CHECK_POINTER(buffer_p);
    GDYSHI_CHECK_POINTER(stack);
    GDYSHI_CHECK_SIZE(nblks);
    GDYSHI_CHECK_SIZE(blksize);

    GDYSHI_ENTER_STACK_CRITICAL();
    stack->stack_offset = 0;
    stack->buffer = buffer_p;
    stack->blksize = blksize;
    stack->nblks = nblks;
	memset(stack->buffer, 0, stack->nblks*stack->blksize);
    GDYSHI_LEAVE_STACK_CRITICAL();
    return ret;
}

gdyshi_smcu gdyshi_is_stack_full(gdyshi_stack_t const * stack)
{
    gdyshi_smcu ret = 0;

    GDYSHI_DEBUG_POS();
    GDYSHI_CHECK_POINTER(stack);
    ret = (stack->stack_offset == stack->nblks);

    return ret;
}

/**
 * \brief Function for checking if the ring buffer is empty
 *
 * \param ring pointer to a struct of type ring_buffer
 *
 * \retval true   if the buffer is empty
 * \retval false  if there is still data in the buffer
 */
gdyshi_smcu gdyshi_is_stack_empty(gdyshi_stack_t const * stack)
{
    gdyshi_smcu ret = 0;
    GDYSHI_DEBUG_POS();
    GDYSHI_CHECK_POINTER(stack);

    ret = (0 == stack->stack_offset);

    return ret;
}


/**
 * \brief Function for getting one byte from the ring buffer
 *
 * Call this function to get a byte of data from the ring buffer.
 * Make sure buffer is not empty (using \ref ring_buffer_is_empty)
 * before calling this function.
 *
 * \param ring pointer to a struct of type ring_buffer
 *
 * \returns next data byte in buffer
 */
gdyshi_smcu gdyshi_stack_pop(gdyshi_stack_t * stack, void * data)
{
    gdyshi_smcu ret = 0;
    GDYSHI_DEBUG_POS();
    GDYSHI_CHECK_POINTER(stack);
    GDYSHI_CHECK_POINTER(data);
    DO_FUNC_2ERR(gdyshi_is_stack_empty(stack));
    GDYSHI_ASSERT((0 == ret), GDYSHI_ENOMEM, "stack empty\n");
    GDYSHI_ENTER_STACK_CRITICAL();
    stack->stack_offset--;
    memcpy(data, stack->buffer+stack->blksize*stack->stack_offset, stack->blksize);
    GDYSHI_LEAVE_STACK_CRITICAL();
err:
    return ret;
}
/**
 * \brief Function for putting a data byte in the ring buffer
 *
 * Call this function to put a byte of data in the ring buffer.
 * Make sure buffer is not full (using \ref ring_buffer_is_full)
 * before calling this function.
 *
 * \param ring pointer to a struct of type ring_buffer
 * \param data the byte to put to the buffer
 *
 */
gdyshi_smcu gdyshi_stack_push(gdyshi_stack_t * stack, void const * const data)
{
    gdyshi_smcu ret = 0;
    GDYSHI_DEBUG_POS();
    GDYSHI_CHECK_POINTER(stack);
    GDYSHI_CHECK_POINTER(data);
    DO_FUNC_2ERR(gdyshi_is_stack_full(stack));
    GDYSHI_ASSERT((0 == ret), GDYSHI_ENOMEM, "stack full\n");
    GDYSHI_ENTER_STACK_CRITICAL();
    memcpy(stack->buffer+stack->blksize*stack->stack_offset, data, stack->blksize);
    stack->stack_offset++;
    GDYSHI_LEAVE_STACK_CRITICAL();
err:
    return ret;
}
