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
#include "gdyshi_stack.c"
#include "utest_stack.h"

typedef struct
{
    char ch;
    short sh;
    int it;
}buffer_t;
static buffer_t stack_buffer[10] = {0};
static gdyshi_stack_t stack = {0};

void stack_init_test(void)
{
    gdyshi_smcu ret = 0;

    ret = gdyshi_stack_init(NULL, stack_buffer, ARRAY_SIZE(stack_buffer), sizeof(buffer_t));
    CU_ASSERT(GDYSHI_EFAULT == ret);    
    ret = gdyshi_stack_init(&stack, NULL, ARRAY_SIZE(stack_buffer), sizeof(buffer_t));
    CU_ASSERT(GDYSHI_EFAULT == ret);    
    ret = gdyshi_stack_init(&stack, stack_buffer, 0, sizeof(buffer_t));
    CU_ASSERT(GDYSHI_EINVAL == ret);
    ret = gdyshi_stack_init(&stack, stack_buffer, ARRAY_SIZE(stack_buffer), 0);
    CU_ASSERT(GDYSHI_EINVAL == ret);
    
    ret = gdyshi_stack_init(&stack, stack_buffer, ARRAY_SIZE(stack_buffer), sizeof(buffer_t));
    CU_ASSERT(0 == ret);
    CU_ASSERT(0 == stack.stack_offset);
    CU_ASSERT(sizeof(buffer_t) == stack.blksize);
    CU_ASSERT(ARRAY_SIZE(stack_buffer) == stack.nblks);
    CU_ASSERT((gdyshi_u8 *)stack_buffer == stack.buffer);
}


void stack_is_full_test(void)
{
    gdyshi_smcu ret = 0;

    ret = gdyshi_is_stack_full(NULL);
    CU_ASSERT(GDYSHI_EFAULT == ret);
    stack.stack_offset= stack.nblks-1;
    ret = gdyshi_is_stack_full(&stack);
    CU_ASSERT(0 == ret);
    
    stack.stack_offset = stack.nblks;
    ret = gdyshi_is_stack_full(&stack);
    CU_ASSERT(1 == ret);
    
}

void stack_is_empty_test(void)
{
    gdyshi_smcu ret = 0;

    ret = gdyshi_is_stack_empty(NULL);
    CU_ASSERT(GDYSHI_EFAULT == ret);
    stack.stack_offset= stack.nblks-1;
    ret = gdyshi_is_stack_empty(&stack);
    CU_ASSERT(0 == ret);
    
    stack.stack_offset = 0;
    ret = gdyshi_is_stack_empty(&stack);
    CU_ASSERT(1 == ret);
}

void stack_push_test(void)
{
    gdyshi_smcu ret = 0;
    gdyshi_u8 i = 0;
    buffer_t data = {0};

    ret = gdyshi_stack_init(&stack, stack_buffer, ARRAY_SIZE(stack_buffer), sizeof(buffer_t));
    /* 入参检查 */
    ret = gdyshi_stack_push(NULL, &data);
    CU_ASSERT(GDYSHI_EFAULT == ret);   
    ret = gdyshi_stack_push(&stack, NULL);
    CU_ASSERT(GDYSHI_EFAULT == ret);    

    for(i=0; i<(ARRAY_SIZE(stack_buffer)-1); i++)
    {
        data.ch = i;
        data.it = i+1;
        data.sh = i+2;
        
        ret = gdyshi_stack_push(&stack, &data);
        CU_ASSERT(0 == ret);
        ret = memcmp(&data, &stack_buffer[i], sizeof(data));
        CU_ASSERT(0 == ret);
        CU_ASSERT(i+1 == stack.stack_offset);
    }
    data.ch = i;
    data.it = i+1;
    data.sh = i+2;   
    ret = gdyshi_stack_push(&stack, &data);
    CU_ASSERT(0 == ret);
    ret = memcmp(&data, &stack_buffer[i], sizeof(data));
    CU_ASSERT(0 == ret);
    CU_ASSERT(i+1 == stack.stack_offset);

    data.ch = i;
    data.it = i+1;
    data.sh = i+2;
    ret = gdyshi_stack_push(&stack, &data);
    CU_ASSERT(GDYSHI_ENOMEM == ret);
    CU_ASSERT(ARRAY_SIZE(stack_buffer) == stack.stack_offset);
}

void stack_pop_test(void)
{
    gdyshi_smcu ret = 0;
    gdyshi_u8 i = 0;
    buffer_t data = {0};

    /* 入参检查 */
    ret = gdyshi_stack_pop(NULL, &data);
    CU_ASSERT(GDYSHI_EFAULT == ret);   
    ret = gdyshi_stack_pop(&stack, NULL);
    CU_ASSERT(GDYSHI_EFAULT == ret);    

    for(i=0; i<(ARRAY_SIZE(stack_buffer)-1); i++)
    {       
        ret = gdyshi_stack_pop(&stack, &data);
        CU_ASSERT(0 == ret);
        ret = memcmp(&data, &stack_buffer[stack.nblks -1- i], sizeof(data));
        CU_ASSERT(0 == ret);
        CU_ASSERT(stack.nblks -1- i == stack.stack_offset);
    }
    ret = gdyshi_stack_pop(&stack, &data);
    CU_ASSERT(0 == ret);
    ret = memcmp(&data, &stack_buffer[stack.nblks -1- i], sizeof(data));
    CU_ASSERT(0 == ret);
    CU_ASSERT(stack.nblks -1- i == stack.stack_offset);
    
    ret = gdyshi_stack_pop(&stack, &data);
    CU_ASSERT(GDYSHI_ENOMEM == ret);
    CU_ASSERT(0 == stack.stack_offset);
}


CU_TestFunc stack_test_array[] = 
{
    stack_init_test,
    stack_is_full_test,
    stack_is_empty_test,
    stack_push_test,
    stack_pop_test,
    NULL,
};

/*----------------------------------END OF FILE utest.c-------------------------------*/
