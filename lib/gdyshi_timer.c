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
#include "gdyshi_timer.h"
     
#undef __MODULE_NAME__
#define __MODULE_NAME__     "TIMER"
#undef LOG_VALUE
#define LOG_VALUE   (GDYSHI_LOG_LEVEL_INFO | GDYSHI_LOG_LITE_MODULE | GDYSHI_LOG_LITE_FUNC | GDYSHI_LOG_LITE_LINE | GDYSHI_LOG_LITE_TIME)

#ifdef GDYSHI_CRITICAL_USE_INT
#define GDYSHI_ENTER_TIMER_CRITICAL() GDYSHI_DISABLE_GLOBAL_INT()
#define GDYSHI_LEAVE_TIMER_CRITICAL() GDYSHI_ENABLE_GLOBAL_INT()
#else
static volatile gdyshi_smcu timer_critical = 1;
#define GDYSHI_ENTER_TIMER_CRITICAL() \
    do { \
        while (0 > timer_critical); \
        timer_critical--; \
    }while(0)
#define GDYSHI_LEAVE_TIMER_CRITICAL() \
    do { \
        timer_critical++; \
    }while(0)
#endif /* GDYSHI_CRITICAL_USE_INT */

#define MS_2_TICKS(__ms)    ((__ms/MS_PER_TICK)?(__ms/MS_PER_TICK):1)

static gdyshi_timer_t gdyshi_timer[GDYSHI_MAX_TIMER] = {0};

gdyshi_u32 gdyshi_curr_ticks = 0;

gdyshi_smcu gdyshi_init_timer()
{
    gdyshi_smcu ret = 0;

    memset(gdyshi_timer, 0, sizeof(gdyshi_timer));
    return ret;
}

gdyshi_timer_t * gdyshi_new_timer(gdyshi_u16 time_ms, timer_callback fun, void * arg)
{
    gdyshi_timer_t * timer = NULL;
    gdyshi_u8 i = 0;

    GDYSHI_DEBUG_INFO(":%d ms\n",time_ms);
#ifdef GDYSHI_CHECK_PARM
    if(NULL == fun)
    {
        return timer;
    }
    if(0 == time_ms)
    {
        return timer;
    }
#endif /* GDYSHI_CHECK_PARM */

    for(i=0; i<GDYSHI_MAX_TIMER; i++)
    {
        timer = &gdyshi_timer[i];
        if(0 == timer->statu.is_busy)
        {
            GDYSHI_ENTER_TIMER_CRITICAL();
            timer->statu.is_busy = 1;
            timer->time_ms = time_ms;
            timer->fun = fun;
            timer->arg = arg;
            GDYSHI_LEAVE_TIMER_CRITICAL();
            return timer;
        }
    }
    if(GDYSHI_MAX_TIMER == i)
    {
        timer = NULL;
    }
    return timer;
}

gdyshi_smcu gdyshi_del_timer(gdyshi_timer_t * timer)
{
    gdyshi_smcu ret = 0;

    GDYSHI_DEBUG_INFO("0x%x\n",timer);
    GDYSHI_CHECK_POINTER(timer);
	GDYSHI_CHECK_RANGE_EQUAL(timer, &gdyshi_timer[0], &gdyshi_timer[GDYSHI_MAX_TIMER-1]);
    
    GDYSHI_ENTER_TIMER_CRITICAL();
    timer->statu.is_busy = 0;
    GDYSHI_LEAVE_TIMER_CRITICAL();

    return ret;
}

gdyshi_smcu gdyshi_start_timer(gdyshi_timer_t * timer)
{
    gdyshi_smcu ret = 0;

    GDYSHI_DEBUG_INFO("0x%x\n",timer);
    GDYSHI_CHECK_POINTER(timer);
    GDYSHI_CHECK_RANGE_EQUAL(timer, &gdyshi_timer[0], &gdyshi_timer[GDYSHI_MAX_TIMER-1]);

    if(timer->statu.is_in_timing)
    {
        return GDYSHI_EAGAIN;
    }
    GDYSHI_ENTER_TIMER_CRITICAL();
    timer->statu.is_in_timing = 1;
	timer->aim_tics = gdyshi_curr_ticks + MS_2_TICKS(timer->time_ms);
    GDYSHI_LEAVE_TIMER_CRITICAL();

    return ret;
}

gdyshi_smcu gdyshi_restart_timer(gdyshi_timer_t * timer)
{
    gdyshi_smcu ret = 0;

    GDYSHI_DEBUG_INFO("0x%x\n",timer);
    GDYSHI_CHECK_POINTER(timer);
	GDYSHI_CHECK_RANGE_EQUAL(timer, &gdyshi_timer[0], &gdyshi_timer[GDYSHI_MAX_TIMER-1]);

    GDYSHI_ENTER_TIMER_CRITICAL();
    timer->statu.is_in_timing = 1;
	timer->aim_tics = gdyshi_curr_ticks + MS_2_TICKS(timer->time_ms);
    GDYSHI_LEAVE_TIMER_CRITICAL();

    return ret;
}

gdyshi_smcu gdyshi_stop_timer(gdyshi_timer_t * timer)
{
    gdyshi_smcu ret = 0;

    GDYSHI_DEBUG_INFO("0x%x\n",timer);
    GDYSHI_CHECK_POINTER(timer);
    GDYSHI_CHECK_RANGE_EQUAL(timer, &gdyshi_timer[0], &gdyshi_timer[GDYSHI_MAX_TIMER-1]);

    GDYSHI_ENTER_TIMER_CRITICAL();
    timer->statu.is_in_timing = 0;
    GDYSHI_LEAVE_TIMER_CRITICAL();

    return ret;
}
gdyshi_smcu gdyshi_tick_process(void)
{
    gdyshi_u8 i = 0;
    gdyshi_smcu ret = 0;
    gdyshi_timer_t * timer = NULL;

    GDYSHI_DEBUG_POS();

    gdyshi_curr_ticks++;
    for(i=0; i<GDYSHI_MAX_TIMER; i++)
    {
        timer = &gdyshi_timer[i];
        if((timer->statu.is_busy) && (timer->statu.is_in_timing))
        {            
            if (gdyshi_curr_ticks == timer->aim_tics)
            {
                GDYSHI_DEBUG_INFO("timer 0x%x up\n",timer);
                GDYSHI_ENTER_TIMER_CRITICAL();
                timer->statu.is_in_timing = 0;
                GDYSHI_LEAVE_TIMER_CRITICAL();
                if(NULL != timer->fun)
                {
                    ret = timer->fun(timer, timer->arg);
                }
                continue;
            }
        }
    }

    return ret;
}

