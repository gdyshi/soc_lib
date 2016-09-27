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
#include "gdyshi_list.h"

#undef __MODULE_NAME__
#define __MODULE_NAME__     "list_example"
#undef LOG_VALUE
#define LOG_VALUE   GDYSHI_LOG_LEVEL_INFO | GDYSHI_LOG_LITE_MODULE | GDYSHI_LOG_LITE_FUNC | GDYSHI_LOG_LITE_LINE | GDYSHI_LOG_LITE_TIME

typedef struct
{
    gdyshi_s32 arg;
    struct gdyshi_list_head list;
}list_t;


int main(void)
{
    gdyshi_smcu ret = 0;
    gdyshi_smcu i = 0;
    list_t gdyshi_list_head;
    list_t * list_body = NULL;
    list_t * list_pos = NULL;    
    list_t * t_list_pos = NULL;
    
    GDYSHI_LOG_INIT("log.log");
    GDYSHI_DEBUG_INFO("init list head\n");
    gdyshi_init_list_node(&(gdyshi_list_head.list));
    
    GDYSHI_DEBUG_INFO("fill list\n");
    for (i=0; i<5; i++)
    {
        list_body = malloc(sizeof(list_t));
        list_body->arg = i;
		DO_FUNC(gdyshi_list_add_tail(&(list_body->list), &(gdyshi_list_head.list)));
    }
    GDYSHI_DEBUG_INFO("view list\n");
    gdyshi_list_for_each_entry_win(list_pos, list_t, &(gdyshi_list_head.list), list)
    {
        GDYSHI_DEBUG_INFO("arg:%d\n",list_pos->arg);
    }

    GDYSHI_DEBUG_INFO("add list\n");
    gdyshi_list_for_each_entry_win(list_pos, list_t, &(gdyshi_list_head.list), list)
    {
        if(3 == list_pos->arg)
        {            
            list_body = malloc(sizeof(list_t));            
            list_body->arg = 13;
            DO_FUNC(gdyshi_list_add(&(list_body->list), &(list_pos->list)));
        }
    }
    GDYSHI_DEBUG_INFO("view list\n");
    gdyshi_list_for_each_entry_win(list_pos, list_t, &(gdyshi_list_head.list), list)
    {
        GDYSHI_DEBUG_INFO("arg:%d\n",list_pos->arg);
    }
    
#if 0
    GDYSHI_DEBUG_INFO("replace list\n");
    gdyshi_list_for_each_entry_safe(list_pos, list_t, t_list_pos, &(gdyshi_list_head.list), list)
    {
        if(3 == list_pos->arg)
        {            
            list_body = malloc(sizeof(list_t));            
            list_body->arg = 53;
            DO_FUNC(gdyshi_list_replace(&(list_pos->list), &(list_body->list)));
            free(list_pos);
        }
    }
    GDYSHI_DEBUG_INFO("view list\n");
    gdyshi_list_for_each_entry(list_pos, list_t, &(gdyshi_list_head.list), list)
    {
        GDYSHI_DEBUG_INFO("arg:%d\n",list_pos->arg);
    }
#endif /* if 0 end */

    GDYSHI_DEBUG_INFO("del list\n");
	gdyshi_list_for_each_entry_safe_win(list_pos, list_t, t_list_pos, &(gdyshi_list_head.list), list)
    {
        {            
            DO_FUNC(gdyshi_list_del(&(list_pos->list)));
            free(list_pos);
            list_pos = NULL;
        }
    }
    GDYSHI_DEBUG_INFO("view list\n");
    gdyshi_list_for_each_entry_win(list_pos, list_t, &(gdyshi_list_head.list), list)
    {
        GDYSHI_DEBUG_INFO("arg:%d\n",list_pos->arg);
    }

    return 0;
}


/*----------------------------------END OF FILE example.c-------------------------------*/
