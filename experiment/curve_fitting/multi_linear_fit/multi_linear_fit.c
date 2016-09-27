#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#include "math.h"
#include "linear_fit.h"

/* measured_value从小到大排列 */
static gdyshi_measure_t * s_measure_array = NULL;
static gdyshi_u8 s_array_num = 0;

gdyshi_s32 multi_linear_fit_init(gdyshi_measure_t * measure_array, gdyshi_u8 array_num)
{
    gdyshi_s32 result = 0;
    
    s_measure_array = measure_array;
    s_array_num = array_num;
    
    return result;
}
gdyshi_s32 multi_linear_fit_get_data(gdyshi_s32 measured_value)
{
    gdyshi_s32 actual_value = 0, i=0;
    gdyshi_s32 delta = 0;

	/* 找到合适档位 */
    for(i=0; i<s_array_num; i++)
    {
        if(measured_value < s_measure_array[i].measured_value)
        {
            break;
        }
    }
    
    /* 超左界 */
    if(i==0)
    {
        actual_value = 0x80000000;
    }
    else if(i==s_array_num)
    {
        /* 右闭合点 */
        if(measured_value == s_measure_array[s_array_num-1].measured_value)
        {
            actual_value = s_measure_array[s_array_num-1].actual_value;
        }        
        /* 超右界 */
        else
        {
            actual_value = 0x7fffffff;
        }
    }
    /* 正常界限内 */
    else
    {
        delta = (gdyshi_s64)(s_measure_array[i].measured_value - measured_value) *
                            (s_measure_array[i].actual_value - s_measure_array[i-1].actual_value) /
                            (s_measure_array[i].measured_value - s_measure_array[i-1].measured_value);
        actual_value = s_measure_array[i].actual_value - delta;
    }
    
    return actual_value;
}


