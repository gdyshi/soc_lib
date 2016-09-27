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
#include "gdyshi_heap.h"

#undef __MODULE_NAME__
#define __MODULE_NAME__     "heap_example"
#undef LOG_VALUE
#define LOG_VALUE   GDYSHI_LOG_LEVEL_INFO | GDYSHI_LOG_LITE_MODULE | GDYSHI_LOG_LITE_FUNC | GDYSHI_LOG_LITE_LINE | GDYSHI_LOG_LITE_TIME

gdyshi_u32 buffer[10][20] = {0};
gdyshi_heap_t heap = {0};
typedef struct
{
    char ch[16];
}string_t;
int main(void)
{
    gdyshi_bool result = 0;
    gdyshi_smcu ret = 0;
    gdyshi_smcu i = 0;
    string_t * str = NULL;
    GDYSHI_LOG_INIT("log.log");
    DO_FUNC(gdyshi_heap_init(buffer, 10, 20*sizeof(gdyshi_u32), &heap));

    DO_FUNC_2ERR(gdyshi_heap_is_empty(&heap));
    printf("%s \n", ret?"heap empty":"heap not empty");
    
    str = gdyshi_heap_alloc(&heap, sizeof(string_t));
    printf("after alloc \n");    
    DO_FUNC_2ERR(gdyshi_heap_is_empty(&heap));
    printf("%s \n", ret?"heap empty":"heap not empty");
    memset(str,0x55,sizeof(string_t));
    
    DO_FUNC(gdyshi_heap_free(&heap, str));
    printf("after free \n");    
    DO_FUNC_2ERR(gdyshi_heap_is_empty(&heap));
    printf("%s \n", ret?"heap empty":"heap not empty");
    
    for (i=0; i<10; i++)
    {
        str = gdyshi_heap_alloc(&heap, sizeof(string_t));
        if (NULL == str)
        {
            printf("alloc err\n");
            break;
        }
    }
    printf("after all alloc \n");    
    DO_FUNC_2ERR(gdyshi_heap_is_full(&heap));
    printf("%s \n", ret?"heap full":"heap not full");
err:
    return ret;
}

/*----------------------------------END OF FILE example.c-------------------------------*/
