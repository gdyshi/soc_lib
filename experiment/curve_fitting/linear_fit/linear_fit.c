#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#include "math.h"
#include "linear_fit.h"

static gdyshi_real32 s_k=1,s_b=0; 
gdyshi_s32 linear_fit_init(gdyshi_measure_t * measure1,gdyshi_measure_t * measure2)
{
    gdyshi_s32 result = 0;

    s_k = (gdyshi_real32)(measure2->actual_value-measure1->actual_value) / 
        (measure2->measured_value-measure1->measured_value);
    s_b = measure2->actual - s_k*measure2->measured_value;
    return result;
}
gdyshi_s32 linear_fit_get_data(gdyshi_s32 measured_value)
{
    return s_k*measured_value+s_b;
}


