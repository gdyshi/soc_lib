#include "gdyshi_includes.h"
#include "gdyshi_cunit.h"

void demo_1(void)
{    
    CU_ASSERT(0 == 0);    
}
void demo_2(void)
{    
    CU_ASSERT(1 == 0);    
}
void demo_3(void)
{    
    CU_ASSERT(0 == 0);    
}
void demo_4(void)
{    
    CU_ASSERT(2 == 0);    
}
CU_TestFunc demo_test_array[] = 
{
    demo_1,
    demo_2,
    demo_3,
    demo_4,
    NULL,
};

test_suit_t suits[] =
{
    { "demo", demo_test_array},
};

int main()
{
    gdyshi_smcu ret = 0;
    gdyshi_s32 i = 0;
    
    GDYSHI_LOG_INIT("log.log");
    gdyshi_cunit_init();
    for (i=0; i<ARRAY_SIZE(suits); i++)
    {
        ret = gdyshi_cunit_run_suit(&suits[i]);
        if (0 == ret)
        {            
            GDYSHI_DEBUG_FATAL("TEST SUIT %s PASSED:\r\n",suits[i].name);
        }
        else
        {
            GDYSHI_DEBUG_FATAL("TEST SUIT %s FAILED:\r\n",suits[i].name);
        }
    }    
}
