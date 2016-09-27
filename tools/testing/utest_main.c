#ifdef __cplusplus
extern "C" {
#endif

#define GDYSHI_UTEST_LOG
#include "utest_include.h"
#include "utest_cunit.h"
#include "utest_ring_buffer.h"
#include "utest_heap.h"
#include "utest_timer.h"
#include "utest_list.h"
#include "utest_stack.h"

#ifdef GDYSHI_UTEST_LOG
#include "gdyshi_log.h"
#undef __MODULE_NAME__
#define __MODULE_NAME__     "UTEST"
#undef LOG_VALUE
#define LOG_VALUE   GDYSHI_LOG_LEVEL_ERROR
#endif /* GDYSHI_UTEST_LOG */

#ifdef __cplusplus
}
#endif

test_suit_t suits[] =
{
    { "ring_buffer", ring_buffer_test_array},
	{ "heap", heap_test_array },
    { "timer", timer_test_array },
	{ "list", list_test_array },
    { "stack", stack_test_array },
};

int main()
{
    gdyshi_smcu ret = 0;
    gdyshi_s32 i = 0;
    
    GDYSHI_LOG_INIT("utest.log");
    gdyshi_cunit_init();
    for (i=0; i<ARRAY_SIZE(suits); i++)
    {
        ret = gdyshi_cunit_run_suit(&suits[i]);
        if (0 == ret)
        {            
            GDYSHI_DEBUG_FATAL("TEST SUIT %s PASSED\r\n",suits[i].name);
        }
        else
        {
            GDYSHI_DEBUG_FATAL("TEST SUIT %s FAILED\r\n",suits[i].name);
        }
    }    
}
