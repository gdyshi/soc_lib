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
#ifndef __GDYSHI_HEAP_H_
#define __GDYSHI_HEAP_H_

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

typedef struct {                   /* MEMORY CONTROL BLOCK                                      */
    gdyshi_u8  blksize;                 /* Size (in bytes) of each block of memory                   */
    gdyshi_u8  nblks;                   /* Total number of blocks in this partition                  */
    gdyshi_u8  nfree;                   /* Number of memory blocks remaining in this partition       */
	gdyshi_u8  *addr;                    /* Pointer to beginning of memory partition                  */
} gdyshi_heap_t;

gdyshi_smcu gdyshi_heap_init(void *addr, gdyshi_u8 nblks, gdyshi_u8 blksize, gdyshi_heap_t *heap);

void * gdyshi_heap_alloc(gdyshi_heap_t *heap, gdyshi_u8 size);

gdyshi_smcu gdyshi_heap_free(gdyshi_heap_t *heap, gdyshi_u8 * add);

gdyshi_smcu gdyshi_heap_is_full(gdyshi_heap_t const * heap);

gdyshi_smcu gdyshi_heap_is_empty(gdyshi_heap_t const * heap);

#ifdef __cplusplus
}
#endif

#endif /* __GDYSHI_HEAP_H_ */
