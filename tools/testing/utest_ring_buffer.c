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
#include "gdyshi_ring_buffer.c"
#include "utest_ring_buffer.h"

typedef struct
{
    char ch;
    short sh;
    int it;
}buffer_t;
buffer_t buffer[10] = {0};
gdyshi_ring_buffer_t ring_buffer = {0};

void ring_buffer_init_test(void)
{
    gdyshi_smcu ret = 0;

    ret = gdyshi_ring_buffer_init(NULL, buffer, ARRAY_SIZE(buffer), sizeof(buffer_t));
    CU_ASSERT(GDYSHI_EFAULT == ret);    
    ret = gdyshi_ring_buffer_init(&ring_buffer, NULL, ARRAY_SIZE(buffer), sizeof(buffer_t));
    CU_ASSERT(GDYSHI_EFAULT == ret);    
    ret = gdyshi_ring_buffer_init(&ring_buffer, buffer, 0, sizeof(buffer_t));
    CU_ASSERT(GDYSHI_EINVAL == ret);
    ret = gdyshi_ring_buffer_init(&ring_buffer, buffer, ARRAY_SIZE(buffer), 0);
    CU_ASSERT(GDYSHI_EINVAL == ret);
    
    ret = gdyshi_ring_buffer_init(&ring_buffer, buffer, ARRAY_SIZE(buffer), sizeof(buffer_t));
    CU_ASSERT(0 == ret);
    CU_ASSERT(0 == ring_buffer.write_offset);
    CU_ASSERT(0 == ring_buffer.read_offset);
    CU_ASSERT(ARRAY_SIZE(buffer) == ring_buffer.buffer_num);
    CU_ASSERT(0 == ring_buffer.count);
    CU_ASSERT((gdyshi_u8 *)buffer == ring_buffer.buffer);
}

void ring_buffer_get_next_write_test(void)
{
    gdyshi_smcu ret = 0;

    ret = gdyshi_ring_buffer_get_next_write(NULL);
    CU_ASSERT(GDYSHI_EFAULT == ret);
    ring_buffer.write_offset = 0;
    ret = gdyshi_ring_buffer_get_next_write(&ring_buffer);
    CU_ASSERT(1 == ret);
    ring_buffer.write_offset = ring_buffer.buffer_num-2;
    ret = gdyshi_ring_buffer_get_next_write(&ring_buffer);
    CU_ASSERT(ring_buffer.buffer_num-1 == ret);
    ring_buffer.write_offset = ring_buffer.buffer_num-1;
    ret = gdyshi_ring_buffer_get_next_write(&ring_buffer);
    CU_ASSERT(0 == ret);
}

void ring_buffer_get_next_read_test(void)
{
    gdyshi_smcu ret = 0;

    ret = gdyshi_ring_buffer_get_next_read(NULL);
    CU_ASSERT(GDYSHI_EFAULT == ret);
    ring_buffer.read_offset = 0;
    ret = gdyshi_ring_buffer_get_next_read(&ring_buffer);
    CU_ASSERT(1 == ret);
    ring_buffer.read_offset = ring_buffer.buffer_num-2;
    ret = gdyshi_ring_buffer_get_next_read(&ring_buffer);
    CU_ASSERT(ring_buffer.buffer_num-1 == ret);
    ring_buffer.read_offset = ring_buffer.buffer_num-1;
    ret = gdyshi_ring_buffer_get_next_read(&ring_buffer);
    CU_ASSERT(0 == ret);
}


void ring_buffer_is_full_test(void)
{
    gdyshi_smcu ret = 0;

    ret = gdyshi_ring_buffer_is_full(NULL);
    CU_ASSERT(GDYSHI_EFAULT == ret);
    ring_buffer.count = ring_buffer.buffer_num -1;
    ret = gdyshi_ring_buffer_is_full(&ring_buffer);
    CU_ASSERT(0 == ret);
    
    ring_buffer.count = ring_buffer.buffer_num;
    ret = gdyshi_ring_buffer_is_full(&ring_buffer);
    CU_ASSERT(1 == ret);
    
#if 0
    ring_buffer.count = ring_buffer.buffer_num + 1;
    ret = gdyshi_ring_buffer_is_full(&ring_buffer, &result);
    CU_ASSERT(GDYSHI_ENOMEM == ret);
#endif /* if 0 end */
}

void ring_buffer_is_empty_test(void)
{
    gdyshi_smcu ret = 0;

    ret = gdyshi_ring_buffer_is_empty(NULL);
    CU_ASSERT(GDYSHI_EFAULT == ret);
    ring_buffer.count = ring_buffer.buffer_num -1;
    ret = gdyshi_ring_buffer_is_empty(&ring_buffer);
    CU_ASSERT(0 == ret);
    
    ring_buffer.count = 0;
    ret = gdyshi_ring_buffer_is_empty(&ring_buffer);
    CU_ASSERT(1 == ret);
}

void ring_buffer_get_count_test(void)
{
    gdyshi_smcu ret = 0;
    
    ret = gdyshi_ring_buffer_get_count(NULL);
    CU_ASSERT(GDYSHI_EFAULT == ret);

    ring_buffer.count = 9;
    ret = gdyshi_ring_buffer_get_count(&ring_buffer);
    CU_ASSERT(ring_buffer.count == ret);
    
    ring_buffer.count = 0;
    ret = gdyshi_ring_buffer_get_count(&ring_buffer);
    CU_ASSERT(ring_buffer.count == ret);
}

void ring_buffer_write_test(void)
{
    gdyshi_smcu ret = 0;
    gdyshi_u8 i = 0;
    buffer_t data = {0};

    /* 入参检查 */
    ret = gdyshi_ring_buffer_write(NULL, &data);
    CU_ASSERT(GDYSHI_EFAULT == ret);   
    ret = gdyshi_ring_buffer_write(&ring_buffer, NULL);
    CU_ASSERT(GDYSHI_EFAULT == ret);    

    ret = gdyshi_ring_buffer_init(&ring_buffer, buffer, ARRAY_SIZE(buffer), sizeof(buffer_t));
    for(i=0; i<(ARRAY_SIZE(buffer)-1); i++)
    {
        data.ch = i;
        data.it = i+1;
        data.sh = i+2;
        ret = gdyshi_ring_buffer_get_next_read(&ring_buffer);
        CU_ASSERT(1 == ret);
        ret = gdyshi_ring_buffer_get_next_write(&ring_buffer);
        CU_ASSERT(i+1 == ret);
        ret = gdyshi_ring_buffer_get_count(&ring_buffer);
        CU_ASSERT(i == ret);
        
        ret = gdyshi_ring_buffer_write(&ring_buffer, &data);
        CU_ASSERT(0 == ret);
        ret = memcmp(&data, &buffer[i], sizeof(data));
        CU_ASSERT(0 == ret);
        CU_ASSERT(0 == ring_buffer.read_offset);
        CU_ASSERT(i+1 == ring_buffer.count);
        CU_ASSERT(i+1 == ring_buffer.write_offset);
        
    }
    data.ch = i;
    data.it = i+1;
    data.sh = i+2;
    ret = gdyshi_ring_buffer_get_next_read(&ring_buffer);
    CU_ASSERT(1 == ret);
    ret = gdyshi_ring_buffer_get_next_write(&ring_buffer);
    CU_ASSERT(0 == ret);
    ret = gdyshi_ring_buffer_get_count(&ring_buffer);
    CU_ASSERT(i == ret);
    
    ret = gdyshi_ring_buffer_write(&ring_buffer, &data);
    CU_ASSERT(0 == ret);
    ret = memcmp(&data, &buffer[i], sizeof(data));
    CU_ASSERT(0 == ret);
    CU_ASSERT(0 == ring_buffer.read_offset);
    CU_ASSERT(i+1 == ring_buffer.count);
    CU_ASSERT(0 == ring_buffer.write_offset);

    data.ch = i;
    data.it = i+1;
    data.sh = i+2;
    ret = gdyshi_ring_buffer_get_next_read(&ring_buffer);
    CU_ASSERT(1 == ret);
    ret = gdyshi_ring_buffer_get_next_write(&ring_buffer);
    CU_ASSERT(1 == ret);
    ret = gdyshi_ring_buffer_get_count(&ring_buffer);
    CU_ASSERT(ARRAY_SIZE(buffer) == ret);
    
    ret = gdyshi_ring_buffer_write(&ring_buffer, &data);
    CU_ASSERT(GDYSHI_ENOMEM == ret);
    CU_ASSERT(0 == ring_buffer.read_offset);
    CU_ASSERT(ARRAY_SIZE(buffer) == ring_buffer.count);
    CU_ASSERT(0 == ring_buffer.write_offset);
}

void ring_buffer_read_test(void)
{
    gdyshi_smcu ret = 0;
    gdyshi_u8 i = 0;
    buffer_t data = {0};

    /* 入参检查 */
    ret = gdyshi_ring_buffer_read(NULL, &data);
    CU_ASSERT(GDYSHI_EFAULT == ret);   
    ret = gdyshi_ring_buffer_read(&ring_buffer, NULL);
    CU_ASSERT(GDYSHI_EFAULT == ret);    

    for(i=0; i<(ARRAY_SIZE(buffer)-1); i++)
    {
        ret = gdyshi_ring_buffer_get_next_read(&ring_buffer);
        CU_ASSERT(i+1 == ret);
        ret = gdyshi_ring_buffer_get_next_write(&ring_buffer);
        CU_ASSERT(1 == ret);
        ret = gdyshi_ring_buffer_get_count(&ring_buffer);
        CU_ASSERT(ARRAY_SIZE(buffer) - i == ret);
        
        ret = gdyshi_ring_buffer_read(&ring_buffer, &data);
        CU_ASSERT(0 == ret);
        ret = memcmp(&data, &buffer[i], sizeof(data));
        CU_ASSERT(0 == ret);
        CU_ASSERT(i+1 == ring_buffer.read_offset);
        CU_ASSERT(ARRAY_SIZE(buffer)-1-i == ring_buffer.count);
        CU_ASSERT(0 == ring_buffer.write_offset);
        
    }
    ret = gdyshi_ring_buffer_get_next_read(&ring_buffer);
    CU_ASSERT(0 == ret);
    ret = gdyshi_ring_buffer_get_next_write(&ring_buffer);
    CU_ASSERT(1 == ret);
    ret = gdyshi_ring_buffer_get_count(&ring_buffer);
    CU_ASSERT(1 == ret);
    
    ret = gdyshi_ring_buffer_read(&ring_buffer, &data);
    CU_ASSERT(0 == ret);
    ret = memcmp(&data, &buffer[i], sizeof(data));
    CU_ASSERT(0 == ret);
    CU_ASSERT(0 == ring_buffer.read_offset);
    CU_ASSERT(0 == ring_buffer.count);
    CU_ASSERT(0 == ring_buffer.write_offset);

    ret = gdyshi_ring_buffer_get_next_read(&ring_buffer);
    CU_ASSERT(1 == ret);
    ret = gdyshi_ring_buffer_get_next_write(&ring_buffer);
    CU_ASSERT(1 == ret);
    ret = gdyshi_ring_buffer_get_count(&ring_buffer);
    CU_ASSERT(0 == ret);
    
    ret = gdyshi_ring_buffer_read(&ring_buffer, &data);
    CU_ASSERT(GDYSHI_ENOMEM == ret);
    CU_ASSERT(0 == ring_buffer.read_offset);
    CU_ASSERT(0 == ring_buffer.count);
    CU_ASSERT(0 == ring_buffer.write_offset);
}


CU_TestFunc ring_buffer_test_array[] = 
{
    ring_buffer_init_test,
    ring_buffer_get_next_write_test,
    ring_buffer_get_next_read_test,
    ring_buffer_is_full_test,
    ring_buffer_is_empty_test,
    ring_buffer_get_count_test,
    ring_buffer_write_test,
    ring_buffer_read_test,
    NULL,
};

/*----------------------------------END OF FILE utest.c-------------------------------*/
