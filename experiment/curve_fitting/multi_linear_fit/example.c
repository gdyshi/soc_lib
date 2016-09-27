#include "gdyshi_includes.h"
#include "multi_linear_fit.h"

gdyshi_measure_t measure[] = 
{
    {5329, 4000},
    {5546, 3900},
    {5777, 3800},
    {6017, 3700},
    {6270, 3600},
    {6532, 3500},
    {6807, 3400},
    {7100, 3300},
    {7402, 3200},
    {7722, 3100},
    {8060, 3000},
    {8410, 2900},
    {8779, 2800},
    {9165, 2700},
    {9574, 2600},
    {10000, 2500},
};
void main(void)
{
    unsigned short i = 0;
    
    GDYSHI_LOG_INIT("log.log");
    multi_linear_fit_init(measure, ARRAY_SIZE(measure));
    
    GDYSHI_DEBUG_INFO("measure:%d <----->acture:%d\n",7000,multi_linear_fit_get_data(7000));
    
}

