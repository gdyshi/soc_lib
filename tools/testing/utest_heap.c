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
#define __UTEST
#include "utest_include.h"
#include "gdyshi_heap.c"
#include "utest_heap.h"

gdyshi_u32 heap_buffer[10][20] = {0};
gdyshi_heap_t heap = {0};
typedef struct
{
    char ch[20*sizeof(gdyshi_u32) - 4];
}string_t;
string_t * str[11] = {0};

void heap_init_test(void)
{
    gdyshi_smcu ret = 0;
    
    ret = gdyshi_heap_init(NULL, 10, 20*sizeof(gdyshi_u32), &heap);
    CU_ASSERT(GDYSHI_EFAULT == ret);    
    ret = gdyshi_heap_init(heap_buffer, 10, 20*sizeof(gdyshi_u32), NULL);
    CU_ASSERT(GDYSHI_EFAULT == ret);    
    ret = gdyshi_heap_init(heap_buffer, 0, 20*sizeof(gdyshi_u32), &heap);
    CU_ASSERT(GDYSHI_EINVAL == ret);
    ret = gdyshi_heap_init(heap_buffer, 10, 0, &heap);
    CU_ASSERT(GDYSHI_EINVAL == ret);
    
    ret = gdyshi_heap_init(heap_buffer, 10, 20*sizeof(gdyshi_u32), &heap);
    CU_ASSERT(0 == ret);
	CU_ASSERT((gdyshi_u8 *)&heap_buffer[0][0] == heap.addr);
	CU_ASSERT(20 * sizeof(gdyshi_u32) == heap.blksize);
    CU_ASSERT(10 == heap.nblks);
    CU_ASSERT(10 == heap.nfree);
}

void heap_alloc_test(void)
{
    gdyshi_smcu i = 0,ret=0;
    
    ret = gdyshi_heap_init(heap_buffer, 10, 20*sizeof(gdyshi_u32), &heap);
    str[0] =  gdyshi_heap_alloc(NULL, sizeof(string_t));
    CU_ASSERT(NULL == str[0]);
    str[0] =  gdyshi_heap_alloc(&heap, 0);
    CU_ASSERT(NULL == str[0]);
    str[0] =  gdyshi_heap_alloc(&heap, 20*sizeof(gdyshi_u32)-sizeof(gdyshi_umcu)+1);
    CU_ASSERT(NULL == str[0]);
    str[0] =  gdyshi_heap_alloc(&heap, 20*sizeof(gdyshi_u32));
    CU_ASSERT(NULL == str[0]);    

    for(i=0; i<10; i++)
    {
        str[i] =  gdyshi_heap_alloc(&heap, sizeof(string_t));
		CU_ASSERT((gdyshi_u8 *)&heap_buffer[i][sizeof(gdyshi_umcu)/sizeof(gdyshi_u32)] == (gdyshi_u8 *)str[i]);
    }
    
    str[11] =  gdyshi_heap_alloc(&heap, sizeof(string_t));
    CU_ASSERT(NULL == str[11]);
}

void heap_free_test(void)
{
    gdyshi_smcu ret = 0, i=0;
    gdyshi_u8 result = 0;

    ret = gdyshi_heap_init(heap_buffer, 10, 20*sizeof(gdyshi_u32), &heap);
    for(i=0; i<10; i++)
    {
        str[i] =  gdyshi_heap_alloc(&heap, sizeof(string_t));
        memset(str[i],0x55, sizeof(string_t));
    }
	ret = gdyshi_heap_free(NULL, (gdyshi_u8 *)str[0]);
    CU_ASSERT(GDYSHI_EFAULT == ret);
    ret = gdyshi_heap_free(&heap, NULL);
    CU_ASSERT(GDYSHI_EFAULT == ret);
    
	ret = gdyshi_heap_free(&heap, (gdyshi_u8 *)str[5]);
    CU_ASSERT(0 == ret);
    str[5] = gdyshi_heap_alloc(&heap, sizeof(string_t));
	CU_ASSERT((gdyshi_u8 *)&heap_buffer[5][sizeof(gdyshi_umcu)/sizeof(gdyshi_u32)] == (gdyshi_u8 *)str[5]);

    for(i=0; i<10; i++)
    {
		ret = gdyshi_heap_free(&heap, (gdyshi_u8 *)str[i]);
        CU_ASSERT(0 == ret);
    }
    
	ret = gdyshi_heap_free(&heap, (gdyshi_u8 *)str[0]);
    CU_ASSERT(GDYSHI_ENOMEM == ret);
}


void heap_is_full_test(void)
{
    gdyshi_smcu ret = 0,i=0;
    gdyshi_bool result = 0;

    ret = gdyshi_heap_init(heap_buffer, 10, 20*sizeof(gdyshi_u32), &heap);
    
    ret = gdyshi_heap_is_full(NULL);
    CU_ASSERT(GDYSHI_EFAULT == ret);
    ret = gdyshi_heap_is_full(&heap);
    CU_ASSERT(0 == ret);

    for(i=0; i<9; i++)
    {
        str[i] =  gdyshi_heap_alloc(&heap, sizeof(string_t));
        ret = gdyshi_heap_is_full(&heap);
        CU_ASSERT(0 == ret);
    }
    
	str[i] = gdyshi_heap_alloc(&heap, sizeof(string_t));
	ret = gdyshi_heap_is_full(&heap);
    CU_ASSERT(ret);
}

void heap_is_empty_test(void)
{
    gdyshi_smcu ret = 0,i=0;
    gdyshi_bool result = 0;

    ret = gdyshi_heap_init(heap_buffer, 10, 20*sizeof(gdyshi_u32), &heap);
    
    ret = gdyshi_heap_is_empty(NULL);
    CU_ASSERT(GDYSHI_EFAULT == ret);
    ret = gdyshi_heap_is_empty(&heap);
    CU_ASSERT(ret);

    for(i=0; i<10; i++)
    {
        str[i] =  gdyshi_heap_alloc(&heap, sizeof(string_t));
        ret = gdyshi_heap_is_empty(&heap);
        CU_ASSERT(0 == ret);
    }
    
    for(i=0; i<9; i++)
    {
		ret = gdyshi_heap_free(&heap, (gdyshi_u8 *)str[i]);
        ret = gdyshi_heap_is_empty(&heap);
        CU_ASSERT(0 == ret);
    }
    
	ret = gdyshi_heap_free(&heap, (gdyshi_u8 *)str[9]);
    ret = gdyshi_heap_is_empty(&heap);
    CU_ASSERT(ret);
}

CU_TestFunc heap_test_array[] = 
{
    heap_init_test,
    heap_alloc_test,
    heap_free_test,
    heap_is_full_test,
    heap_is_empty_test,
    NULL,
};

/*----------------------------------END OF FILE utest.c-------------------------------*/
