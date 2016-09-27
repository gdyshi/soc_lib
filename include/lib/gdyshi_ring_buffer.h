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
#ifndef __GDYSHI_RING_BUFFER_H_
#define __GDYSHI_RING_BUFFER_H_

#ifdef __cplusplus
extern "C" {
#endif

//#include "compiler.h"

/**
 * \defgroup ring_buffer_group Ring buffer
 *
 * This is a generic ring buffer that can be used for data storage e.g. for
 * communication peripherals like the UART.
 *
 * \section dependencies Dependencies
 * This ring buffer does not depend on other modules.
 * @{
 */

/**
 * \brief Struct for holding the ring buffer
 *
 * This struct is used to hold one ring buffer
 *
 * \note The maximum size of the ring buffer is 256 (0xFF) bytes
 */
typedef struct  {
    volatile gdyshi_u8 write_offset;
    volatile gdyshi_u8 read_offset;
    volatile gdyshi_u8 count;
    gdyshi_u8 buffer_ele_len;
    gdyshi_u8 buffer_num;
    gdyshi_u8 * buffer;
}gdyshi_ring_buffer_t;

/**
 * \brief Function for initializing a ring buffer
 *
 * \param buffer pointer to the buffer to use as a ring buffer
 * \param size   the size of the ring buffer
 *
 * \retval struct ring_buffer a struct containing the ring buffer
 */
gdyshi_smcu gdyshi_ring_buffer_init(gdyshi_ring_buffer_t * ring, void * buffer_p,
                                                gdyshi_u8 buffer_num, gdyshi_u8 buffer_ele_len);

/**
 * \brief Function to get the next write offset in a ring buffer.
 *
 * \param ring pointer to a struct of type ring_buffer
 *
 * \returns the next write offset in the ring buffer
 */
gdyshi_smcu gdyshi_ring_buffer_get_next_write(const gdyshi_ring_buffer_t *ring);

/**
 * \brief Function to get the next read offset in a ring buffer.
 *
 * \param ring pointer to a struct of type ring_buffer
 *
 * \returns the next read offset in the ring buffer
 */
gdyshi_smcu gdyshi_ring_buffer_get_next_read(gdyshi_ring_buffer_t const * const ring);

/**
 * \brief Function to get all the buffer which are not readed.
 *
 * \param ring pointer to a struct of type ring_buffer
 *
 * \returns the next read offset in the ring buffer
 */
gdyshi_smcu gdyshi_ring_buffer_get_buffer(gdyshi_ring_buffer_t const * const ring);

/**
 * \brief Function for checking if the ring buffer is full
 *
  * \param ring pointer to a struct of type ring_buffer
 *
 * \retval true  if the buffer is full
 * \retval false if there is space available in the ring buffer
 */
gdyshi_smcu gdyshi_ring_buffer_is_full(const gdyshi_ring_buffer_t *ring);

/**
 * \brief Function for checking if the ring buffer is empty
 *
 * \param ring pointer to a struct of type ring_buffer
 *
 * \retval true   if the buffer is empty
 * \retval false  if there is still data in the buffer
 */
gdyshi_smcu gdyshi_ring_buffer_is_empty(const gdyshi_ring_buffer_t *ring);

gdyshi_smcu gdyshi_ring_buffer_get_count(const gdyshi_ring_buffer_t *ring);

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
gdyshi_smcu gdyshi_ring_buffer_read(gdyshi_ring_buffer_t * const ring, void * const data);
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
gdyshi_smcu gdyshi_ring_buffer_write(gdyshi_ring_buffer_t *ring, void const * const data);

//! @}

#ifdef __cplusplus
}
#endif

#endif /* __GDYSHI_RING_BUFFER_H_ */
