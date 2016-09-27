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
#include "gdyshi_ring_buffer.h"
     
#undef __MODULE_NAME__
#define __MODULE_NAME__     "RING"
#undef LOG_VALUE
#define LOG_VALUE   (GDYSHI_LOG_LEVEL_INFO | GDYSHI_LOG_LITE_MODULE | GDYSHI_LOG_LITE_FUNC | GDYSHI_LOG_LITE_LINE | GDYSHI_LOG_LITE_TIME)

#ifdef GDYSHI_CRITICAL_USE_INT
#define GDYSHI_ENTER_RING_BUFFER_CRITICAL() GDYSHI_DISABLE_GLOBAL_INT()
#define GDYSHI_LEAVE_RING_BUFFER_CRITICAL() GDYSHI_ENABLE_GLOBAL_INT()
#else
static volatile gdyshi_smcu ring_buffer_critical = 1;
#define GDYSHI_ENTER_RING_BUFFER_CRITICAL() \
    do { \
        while (0 >= ring_buffer_critical); \
        ring_buffer_critical--; \
    }while(0)
#define GDYSHI_LEAVE_RING_BUFFER_CRITICAL() \
    do { \
        ring_buffer_critical++; \
    }while(0)
#endif /* GDYSHI_CRITICAL_USE_INT */

/**
 * \brief Function to get the next offset in a ring buffer.
 *
 * \param cur_offset the current offset in the ring buffer
 * \param buffer_num       the buffer_num of the ring buffer in bytes
 *
 * \returns next offset or 0 if we are wrapping
 */
static gdyshi_u8 get_next(volatile gdyshi_u8 cur_offset, gdyshi_u8 buffer_num)
{
    GDYSHI_DEBUG_POS();
    return (cur_offset == (buffer_num - 1) ? 0 : cur_offset + 1);
}

/**
 * \brief Function for initializing a ring buffer
 *
 * \param buffer pointer to the buffer to use as a ring buffer
 * \param buffer_num   the buffer_num of the ring buffer
 *
 * \retval struct ring_buffer a struct containing the ring buffer
 */
gdyshi_smcu gdyshi_ring_buffer_init(gdyshi_ring_buffer_t * ring, void * buffer_p,
                                                gdyshi_u8 buffer_num, gdyshi_u8 buffer_ele_len)
{
    gdyshi_smcu ret = 0;
    
    GDYSHI_DEBUG_POS();
    GDYSHI_CHECK_POINTER(ring);
    GDYSHI_CHECK_POINTER(buffer_p);
    GDYSHI_CHECK_SIZE(buffer_num);
    GDYSHI_CHECK_SIZE(buffer_ele_len);
    
    GDYSHI_ENTER_RING_BUFFER_CRITICAL();
    ring->write_offset = 0;
    ring->read_offset = 0;
    ring->count = 0;
    ring->buffer_num = buffer_num;
    ring->buffer_ele_len = buffer_ele_len;
    ring->buffer = buffer_p;
    GDYSHI_ENTER_RING_BUFFER_CRITICAL();
    return ret;
}

/**
 * \brief Function to get the next write offset in a ring buffer.
 *
 * \param ring pointer to a struct of type ring_buffer
 *
 * \returns the next write offset in the ring buffer
 */
gdyshi_smcu gdyshi_ring_buffer_get_next_write(const gdyshi_ring_buffer_t *ring)
{
    gdyshi_smcu ret = 0;
    GDYSHI_DEBUG_POS();
    GDYSHI_CHECK_POINTER(ring);
    ret = get_next(ring->write_offset, ring->buffer_num);
    return ret;
}

/**
 * \brief Function to get the next read offset in a ring buffer.
 *
 * \param ring pointer to a struct of type ring_buffer
 *
 * \returns the next read offset in the ring buffer
 */
gdyshi_smcu gdyshi_ring_buffer_get_next_read(gdyshi_ring_buffer_t const * const ring)
{
    gdyshi_smcu ret = 0;
    GDYSHI_DEBUG_POS();
    GDYSHI_CHECK_POINTER(ring);
    ret = get_next(ring->read_offset, ring->buffer_num);
    return ret;
}

/**
 * \brief Function for checking if the ring buffer is full
 *
  * \param ring pointer to a struct of type ring_buffer
 *
 * \retval true  if the buffer is full
 * \retval false if there is space available in the ring buffer
 */
gdyshi_smcu gdyshi_ring_buffer_is_full(const gdyshi_ring_buffer_t *ring)
{
    gdyshi_smcu ret = 0;
    GDYSHI_DEBUG_POS();
    GDYSHI_CHECK_POINTER(ring);
    ret = (ring->count == ring->buffer_num);
//err:
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
gdyshi_smcu gdyshi_ring_buffer_is_empty(const gdyshi_ring_buffer_t *ring)
{
    gdyshi_smcu ret = 0;
    GDYSHI_DEBUG_POS();
    GDYSHI_CHECK_POINTER(ring);
    ret = (0 == ring->count);
    return ret;
}

gdyshi_smcu gdyshi_ring_buffer_get_count(const gdyshi_ring_buffer_t *ring)
{
    gdyshi_smcu ret = 0;
    GDYSHI_DEBUG_POS();
    GDYSHI_CHECK_POINTER(ring);
    ret = ring->count;
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
gdyshi_smcu gdyshi_ring_buffer_read(gdyshi_ring_buffer_t * const ring, void * const data)
{
    gdyshi_smcu ret = 0;
    GDYSHI_DEBUG_POS();
    GDYSHI_CHECK_POINTER(ring);
    GDYSHI_CHECK_POINTER(data);
    DO_FUNC_2ERR(gdyshi_ring_buffer_is_empty(ring));
    GDYSHI_ASSERT((1 != ret), GDYSHI_ENOMEM, "ring buffer empty\n");
    GDYSHI_ENTER_RING_BUFFER_CRITICAL();
    memcpy(data, ring->buffer+ring->buffer_ele_len*ring->read_offset, ring->buffer_ele_len);
    ring->read_offset = (gdyshi_u8)gdyshi_ring_buffer_get_next_read(ring);
    ring->count--;
    GDYSHI_LEAVE_RING_BUFFER_CRITICAL();
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
gdyshi_smcu gdyshi_ring_buffer_write(gdyshi_ring_buffer_t *ring, void const * const data)
{
    gdyshi_smcu ret = 0;
    GDYSHI_DEBUG_POS();
    GDYSHI_CHECK_POINTER(ring);
    GDYSHI_CHECK_POINTER(data);
	DO_FUNC_2ERR(gdyshi_ring_buffer_is_full(ring));
    GDYSHI_ASSERT((1 != ret), GDYSHI_ENOMEM, "ring buffer full\n");
    GDYSHI_ENTER_RING_BUFFER_CRITICAL();
    memcpy(ring->buffer+ring->buffer_ele_len*ring->write_offset, data, ring->buffer_ele_len);
    ring->write_offset = (gdyshi_u8)gdyshi_ring_buffer_get_next_write(ring);
    ring->count++;
    GDYSHI_LEAVE_RING_BUFFER_CRITICAL();
err:
    return ret;
}
