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
#include "gdyshi_ring_buffer.h"

#undef __MODULE_NAME__
#define __MODULE_NAME__     "ring_buffer_example"
#undef LOG_VALUE
#define LOG_VALUE   GDYSHI_LOG_LEVEL_INFO | GDYSHI_LOG_LITE_MODULE | GDYSHI_LOG_LITE_FUNC | GDYSHI_LOG_LITE_LINE | GDYSHI_LOG_LITE_TIME

typedef struct
{
    char ch;
    short sh;
    int it;
}buffer_t;
buffer_t buffer[10] = {0};
gdyshi_ring_buffer_t ring_buffer = {0};

int main(void)
{
    gdyshi_smcu ret = 0;
    gdyshi_smcu i = 0;
    buffer_t data = { 0 };
    
    GDYSHI_LOG_INIT("log.log");
    DO_FUNC(gdyshi_ring_buffer_init(&ring_buffer, buffer, ARRAY_SIZE(buffer), sizeof(buffer_t)));
    
    for (i=0; i<5; i++)
    {
        data.ch = i;
        data.it = i+1;
        data.sh = i+2;
        DO_FUNC(gdyshi_ring_buffer_write(&ring_buffer, &data));
    }
    
    DO_FUNC_2ERR(gdyshi_ring_buffer_get_count(&ring_buffer));

    GDYSHI_DEBUG_INFO("ring buffer count:%d\n",ret);

    
    for (i=0; i<5; i++)
    {
        DO_FUNC(gdyshi_ring_buffer_read(&ring_buffer, &data));
        GDYSHI_DEBUG_INFO("read ring buffer data:%d,%d,%d\n",data.ch,data.it,data.sh);
    }
err:
    return ret;
}

/*----------------------------------END OF FILE example.c-------------------------------*/
