/******************************************************************************
 * Copyright: 2012, gdyshi,Ltd.
 * 
 * File name: example.c
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
#include "gdyshi_includes.h"
#include "gdyshi_timer.h"

#undef __MODULE_NAME__
#define __MODULE_NAME__     "timer_example"
#undef LOG_VALUE
#define LOG_VALUE   GDYSHI_LOG_LEVEL_INFO | GDYSHI_LOG_LITE_MODULE | GDYSHI_LOG_LITE_FUNC | GDYSHI_LOG_LITE_LINE | GDYSHI_LOG_LITE_TIME

static gdyshi_smcu timer1_handler(void * this_timer, void * arg)
{
    GDYSHI_DEBUG_POS();
    gdyshi_stop_timer((gdyshi_timer_t *)this_timer);
    gdyshi_del_timer((gdyshi_timer_t *)this_timer);
    return 0;
}

static gdyshi_smcu timer2_handler(void * this_timer, void * arg)
{
    GDYSHI_DEBUG_POS();
    gdyshi_stop_timer((gdyshi_timer_t *)this_timer);
    gdyshi_del_timer((gdyshi_timer_t *)this_timer);
    return 0;
}

static gdyshi_smcu timer3_handler(void * this_timer, void * arg)
{
    GDYSHI_DEBUG_POS();
    gdyshi_restart_timer((gdyshi_timer_t *)this_timer);
    return 0;
}

static gdyshi_smcu timer4_handler(void * this_timer, void * arg)
{
    GDYSHI_DEBUG_POS();
    gdyshi_stop_timer((gdyshi_timer_t *)this_timer);
    gdyshi_del_timer((gdyshi_timer_t *)this_timer);
    return 0;
}
int main(void)
{
    gdyshi_u8 result = 0;
    gdyshi_smcu ret = 0;
    gdyshi_smcu i = 0;
    gdyshi_timer_t * timer_arr[4] = {0};
    
    GDYSHI_LOG_INIT("log.log");
    gdyshi_init_timer();
    timer_arr[0] = gdyshi_new_timer(100,timer1_handler,NULL);
    timer_arr[1] = gdyshi_new_timer(200,timer2_handler,NULL);
    timer_arr[2] = gdyshi_new_timer(300,timer3_handler,NULL);
    timer_arr[3] = gdyshi_new_timer(400,timer4_handler,NULL);
    gdyshi_start_timer(timer_arr[0]);
    gdyshi_start_timer(timer_arr[1]);
    gdyshi_start_timer(timer_arr[2]);
    gdyshi_start_timer(timer_arr[3]);

	while (1)
	{
		gdyshi_tick_process();
	}
    return 0;
}

/*----------------------------------END OF FILE example.c-------------------------------*/
