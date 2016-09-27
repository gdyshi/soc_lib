/******************************************************************************
 * Copyright: 2012, gdyshi,Ltd.
 * 
 * File name: utest.c
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
#include "utest_include.h"
#include "gdyshi_timer.c"
#include "utest_timer.h"

static gdyshi_smcu timer_handler(void * this_timer, void * arg)
{
    gdyshi_smcu ret = 0;
    GDYSHI_DEBUG_POS();
    gdyshi_stop_timer((gdyshi_timer_t *)this_timer);
    gdyshi_del_timer((gdyshi_timer_t *)this_timer);
    return ret;
}

void new_timer_test(void)
{
    gdyshi_smcu ret = 0,i=0;
    gdyshi_timer_t * timer = NULL;

    gdyshi_init_timer();
    timer = gdyshi_new_timer(0, timer_handler, NULL);
    CU_ASSERT(NULL == timer);
    timer = gdyshi_new_timer(1000, NULL, NULL);
    CU_ASSERT(NULL == timer);
    for(i=0; i<GDYSHI_MAX_TIMER; i++)
    {
        timer = gdyshi_new_timer(100*i+1, timer_handler, (void *)(1000+i));
        CU_ASSERT(&gdyshi_timer[i] == timer);
        CU_ASSERT(1 == timer->statu.is_busy);
        CU_ASSERT(100*i+1 == timer->time_ms);
        CU_ASSERT(timer_handler == timer->fun);
        CU_ASSERT((void *)(1000+i) == timer->arg);
    }
    timer = gdyshi_new_timer(1000, timer_handler, NULL);
    CU_ASSERT(NULL == timer);
}

void del_timer_test(void)
{
    gdyshi_smcu ret = 0,i=0;
    gdyshi_timer_t * timer[GDYSHI_MAX_TIMER] = {0};

    gdyshi_init_timer();
    for(i=0; i<GDYSHI_MAX_TIMER; i++)
    {
        timer[i] = gdyshi_new_timer(100*i+1, timer_handler, (void *)(1000+i));
    }
    
    ret = gdyshi_del_timer(NULL);
    CU_ASSERT(GDYSHI_EFAULT == ret);    
    for(i=0; i<GDYSHI_MAX_TIMER; i++)
    {
        ret = gdyshi_del_timer(timer[i]);
        CU_ASSERT(0 == ret);
        CU_ASSERT(0 == timer[i]->statu.is_busy);
    }    
    ret = gdyshi_del_timer(timer[i]);
	CU_ASSERT(GDYSHI_EINVAL == ret);
}


void start_timer_test(void)
{
    gdyshi_smcu ret = 0,i=0;
    gdyshi_timer_t * timer[GDYSHI_MAX_TIMER] = {0};

    gdyshi_init_timer();
    for(i=0; i<GDYSHI_MAX_TIMER; i++)
    {
        timer[i] = gdyshi_new_timer(100*i+1, timer_handler, (void *)(1000+i));
    }
    
    ret = gdyshi_start_timer(NULL);
    CU_ASSERT(GDYSHI_EFAULT == ret);   
    gdyshi_curr_ticks = 0;
    for(i=0; i<GDYSHI_MAX_TIMER; i++)
    {
        ret = gdyshi_start_timer(timer[i]);
        CU_ASSERT(0 == ret);
        CU_ASSERT(1 == timer[i]->statu.is_in_timing);
        CU_ASSERT((gdyshi_curr_ticks + MS_2_TICKS(100*i)) == 
            timer[i]->aim_tics);
    }    
    gdyshi_curr_ticks = 100;
    for(i=0; i<GDYSHI_MAX_TIMER; i++)
    {
        ret = gdyshi_start_timer(timer[i]);
        CU_ASSERT(GDYSHI_EAGAIN == ret);
        CU_ASSERT(1 == timer[i]->statu.is_in_timing);
        CU_ASSERT((0 + MS_2_TICKS(100*i)) == 
            timer[i]->aim_tics);
    }    
    ret = gdyshi_start_timer(timer[i]);
	CU_ASSERT(GDYSHI_EINVAL == ret);
}
void restart_timer_test(void)
{
    gdyshi_smcu ret = 0,i=0;
    gdyshi_timer_t * timer[GDYSHI_MAX_TIMER] = {0};

    gdyshi_init_timer();
    for(i=0; i<GDYSHI_MAX_TIMER; i++)
    {
        timer[i] = gdyshi_new_timer(100*i+1, timer_handler, (void *)(1000+i));
    }
    
    gdyshi_curr_ticks = 0;
    for(i=0; i<GDYSHI_MAX_TIMER; i++)
    {
        ret = gdyshi_start_timer(timer[i]);
    }    
    
    gdyshi_curr_ticks = 100;    
    ret = gdyshi_restart_timer(NULL);
    CU_ASSERT(GDYSHI_EFAULT == ret);   
    for(i=0; i<GDYSHI_MAX_TIMER; i++)
    {
        ret = gdyshi_restart_timer(timer[i]);
        CU_ASSERT(0 == ret);
        CU_ASSERT(1 == timer[i]->statu.is_in_timing);
        CU_ASSERT((gdyshi_curr_ticks + MS_2_TICKS(100*i)) == 
            timer[i]->aim_tics);
    }    
    ret = gdyshi_start_timer(timer[i]);
	CU_ASSERT(GDYSHI_EINVAL == ret);

}

void stop_timer_test(void)
{
    gdyshi_smcu ret = 0,i=0;
    gdyshi_timer_t * timer[GDYSHI_MAX_TIMER] = {0};

    gdyshi_init_timer();
    for(i=0; i<GDYSHI_MAX_TIMER; i++)
    {
        timer[i] = gdyshi_new_timer(100*i+1, timer_handler, (void *)(1000+i));
    }
    
    gdyshi_curr_ticks = 0;
    for(i=0; i<GDYSHI_MAX_TIMER; i++)
    {
        ret = gdyshi_start_timer(timer[i]);
    }    
    
    ret = gdyshi_stop_timer(NULL);
    CU_ASSERT(GDYSHI_EFAULT == ret);   
    for(i=0; i<GDYSHI_MAX_TIMER; i++)
    {
        ret = gdyshi_stop_timer(timer[i]);
        CU_ASSERT(0 == ret);
        CU_ASSERT(0 == timer[i]->statu.is_in_timing);
    }    
    ret = gdyshi_stop_timer(timer[i]);
	CU_ASSERT(GDYSHI_EINVAL == ret);
}

void tick_process_test(void)
{
    gdyshi_smcu ret = 0,i=0;
    gdyshi_timer_t * timer[GDYSHI_MAX_TIMER] = {0};

    gdyshi_init_timer();
    for(i=0; i<GDYSHI_MAX_TIMER; i++)
    {
        timer[i] = gdyshi_new_timer(i+1, timer_handler, (void *)(1000+i));
    }
    
    gdyshi_curr_ticks = 0;
    for(i=0; i<GDYSHI_MAX_TIMER; i++)
    {
        ret = gdyshi_start_timer(timer[i]);
    }    
    
    ret = gdyshi_tick_process();
    CU_ASSERT(0 == ret);   
    for(i=0; i<GDYSHI_MAX_TIMER; i++)
    {
        CU_ASSERT(0 == timer[i]->statu.is_in_timing);   
    }    
}

CU_TestFunc timer_test_array[] = 
{
    new_timer_test,
    del_timer_test,
    start_timer_test,
    restart_timer_test,
    stop_timer_test,
    tick_process_test,
    NULL,
};

/*----------------------------------END OF FILE utest.c-------------------------------*/
