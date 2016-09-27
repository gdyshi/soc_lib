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
#include "gdyshi_stack.h"

#undef __MODULE_NAME__
#define __MODULE_NAME__     "stack_example"
#undef LOG_VALUE
#define LOG_VALUE   GDYSHI_LOG_LEVEL_INFO | GDYSHI_LOG_LITE_MODULE | GDYSHI_LOG_LITE_FUNC | GDYSHI_LOG_LITE_LINE | GDYSHI_LOG_LITE_TIME

typedef struct
{
    char ch;
    short sh;
    int it;
}buffer_t;
buffer_t buffer[10] = {0};
gdyshi_stack_t stack = {0};

int main(void)
{
    gdyshi_bool result = 0;
    gdyshi_smcu ret = 0;
    gdyshi_smcu i = 0;
    buffer_t data = { 0 };
    
    GDYSHI_LOG_INIT("log.log");
    DO_FUNC(gdyshi_stack_init(&stack, buffer, ARRAY_SIZE(buffer), sizeof(buffer_t)));
    
    for (i=0; i<10; i++)
    {
        data.ch = i;
        data.it = i+1;
        data.sh = i+2;
		DO_FUNC(gdyshi_stack_push(&stack, &data));
        GDYSHI_DEBUG_INFO("push data:%d,%d,%d\n",data.ch,data.it,data.sh);
    }
    
	DO_FUNC_2ERR(gdyshi_is_stack_full(&stack));

    GDYSHI_DEBUG_INFO("stack %s\n",ret? "full": "not full");

    
    for (i=0; i<10; i++)
    {
		DO_FUNC(gdyshi_stack_pop(&stack, &data));
        GDYSHI_DEBUG_INFO("pop data:%d,%d,%d\n",data.ch,data.it,data.sh);
    }
	DO_FUNC_2ERR(gdyshi_is_stack_empty(&stack));

    GDYSHI_DEBUG_INFO("stack %s\n",ret? "empty": "not empty");
err:
    return ret;
}

/*----------------------------------END OF FILE example.c-------------------------------*/
