#include "gdyshi_includes.h"
#include "linear_fit.h"

void main(void)
{
    unsigned short i = 0;
    gdyshi_measure_t measure1 = {4,1};
    gdyshi_measure_t measure2 = {1000,800};
    
    GDYSHI_LOG_INIT("log.log");
    linear_fit_init(&measure1, &measure2);
    
    gdyshi_s32 linear_fit_get_data(100);
    GDYSHI_DEBUG_INFO("measure:%d <----->acture:%d\n",100,gdyshi_s32 linear_fit_get_data(100));
    
}

