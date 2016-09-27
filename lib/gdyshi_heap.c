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
#include "gdyshi_heap.h"
     
#undef __MODULE_NAME__
#define __MODULE_NAME__     "HEAP"
#undef LOG_VALUE
#define LOG_VALUE   (GDYSHI_LOG_LEVEL_INFO | GDYSHI_LOG_LITE_MODULE | GDYSHI_LOG_LITE_FUNC | GDYSHI_LOG_LITE_LINE | GDYSHI_LOG_LITE_TIME)

#ifdef GDYSHI_CRITICAL_USE_INT
#define GDYSHI_ENTER_HEAP_CRITICAL() GDYSHI_DISABLE_GLOBAL_INT()
#define GDYSHI_LEAVE_HEAP_CRITICAL() GDYSHI_ENABLE_GLOBAL_INT()
#else
static volatile gdyshi_smcu heap_critical = 1;
#define GDYSHI_ENTER_HEAP_CRITICAL() \
    do { \
        while (0 >= ring_buffer_critical); \
        heap_critical--; \
    }while(0)
#define GDYSHI_LEAVE_HEAP_CRITICAL() \
    do { \
        heap_critical++; \
    }while(0)
#endif /* GDYSHI_CRITICAL_USE_INT */
typedef struct
{
    gdyshi_umcu use_num;/* 使用次数 */
}heap_blk_statu_t;

gdyshi_smcu gdyshi_heap_init(void *addr, gdyshi_u8 nblks, gdyshi_u8 blksize, gdyshi_heap_t *heap)
{
    gdyshi_smcu ret = 0;
    
    GDYSHI_DEBUG_INFO("%d * %d\n", nblks, blksize);
    GDYSHI_CHECK_POINTER(addr);
    GDYSHI_CHECK_POINTER(heap);
    GDYSHI_CHECK_SIZE(nblks);
    GDYSHI_CHECK_SIZE(blksize);

    if(sizeof(heap_blk_statu_t) >= blksize)
    {
        return GDYSHI_ENOMEM;
    }
    GDYSHI_ENTER_HEAP_CRITICAL();
    heap->addr = addr;
    heap->blksize = blksize;
    heap->nblks = nblks;
    heap->nfree = nblks;
	memset(heap->addr, 0, heap->nblks*heap->blksize);
    GDYSHI_LEAVE_HEAP_CRITICAL();
    return ret;
}

void * gdyshi_heap_alloc(gdyshi_heap_t *heap, gdyshi_u8 size)    
{
    gdyshi_u8 i = 0;
    heap_blk_statu_t * blk_statu = NULL;
	gdyshi_u8 * add = NULL;
    GDYSHI_DEBUG_INFO("size:%d\n",size);

#ifdef GDYSHI_CHECK_PARM
    if(NULL == heap)
    {
        return add;
    }
    if(0 == size)
    {
        return add;
    }
    if((heap->blksize - sizeof(heap_blk_statu_t)) < size)
    {
        return add;
    }
#endif /* GDYSHI_CHECK_PARM */
    if(0 == heap->nfree)
    {
        return add;
    }

    for(i=0; i<heap->nblks; i++)
    {
        blk_statu = (heap_blk_statu_t *)(heap->addr + i*heap->blksize);
        if(0 == blk_statu->use_num) 
        {
			add = (gdyshi_u8 *)blk_statu;
            GDYSHI_ENTER_HEAP_CRITICAL();
            blk_statu->use_num++;
            heap->nfree--;
            add += sizeof(heap_blk_statu_t);
            GDYSHI_LEAVE_HEAP_CRITICAL();
            return add;            
        }
    }
    return add;
}


gdyshi_smcu gdyshi_heap_free(gdyshi_heap_t *heap, gdyshi_u8 * add)
{
    gdyshi_smcu ret = 0;
    heap_blk_statu_t * blk_statu = NULL;
    GDYSHI_DEBUG_INFO("add:0x%x\n",add);
    GDYSHI_CHECK_POINTER(heap);
    GDYSHI_CHECK_POINTER(add);
    GDYSHI_CHECK_RANGE(add, heap->addr, (heap->addr+heap->nblks*heap->blksize));

	blk_statu = (heap_blk_statu_t *)(add - sizeof(heap_blk_statu_t));
    if(0 == blk_statu->use_num)
    {
        ret = GDYSHI_ENOMEM;
    }
    else
    {
        GDYSHI_ENTER_HEAP_CRITICAL();
        blk_statu->use_num--;
        if(0 == blk_statu->use_num)
        {
            heap->nfree++;
        }
        else
        {
            ret = GDYSHI_EBUSY;
        }
        GDYSHI_LEAVE_HEAP_CRITICAL();
    }
    
    return ret;
}


gdyshi_smcu gdyshi_heap_is_full(gdyshi_heap_t const * heap)
{
    gdyshi_smcu ret = 0;

    GDYSHI_DEBUG_POS();
    GDYSHI_CHECK_POINTER(heap);

    ret = (0 == heap->nfree);
    
    return ret;
}


gdyshi_smcu gdyshi_heap_is_empty(gdyshi_heap_t const * heap)
{
    gdyshi_smcu ret = 0;

    GDYSHI_DEBUG_POS();
    GDYSHI_CHECK_POINTER(heap);

    ret = (heap->nblks == heap->nfree);
    
    return ret;
}

