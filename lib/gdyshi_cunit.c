/* 打开单元测试日志输出 */
#define GDYSHI_UTEST_LOG
#include "gdyshi_includes.h"
#include "gdyshi_cunit.h"

#ifdef GDYSHI_UTEST_LOG
#include "gdyshi_log.h"
#undef __MODULE_NAME__
#define __MODULE_NAME__     "CUNIT"
#undef LOG_VALUE
//#define LOG_VALUE   GDYSHI_LOG_LEVEL_WARNING
#define LOG_VALUE   GDYSHI_LOG_LEVEL_ERROR
#endif /* GDYSHI_UTEST_LOG */
static gdyshi_s32 gdyshi_cunit_total_case_num = 0;
static gdyshi_s32 gdyshi_cunit_fail_case_num = 0;
gdyshi_s32 CU_assertImplementation(gdyshi_s32 bValue,
                                gdyshi_u32 uiLine,
                                const char *strCondition, 
                                const char *strFile)
{
    gdyshi_s32 ret = 0;
    gdyshi_cunit_total_case_num++;
    if (0 == bValue)
    {
        gdyshi_cunit_fail_case_num++;
        GDYSHI_DEBUG_ERROR("F:%s, L:%d, %s fail!\r\n",strFile,uiLine,strCondition);
    }
    return ret;
}

void gdyshi_cunit_init(void)
{
}
gdyshi_smcu gdyshi_cunit_run_suit(test_suit_t const * const suit)
{
    gdyshi_smcu ret = 0;
    gdyshi_u32 i = 0;
    gdyshi_s32 total_func_num = 0;
    gdyshi_s32 fail_func_num = 0;
	gdyshi_s32 last_cunit_fail_case_num = 0;
    gdyshi_cunit_total_case_num = 0;
    gdyshi_cunit_fail_case_num = 0;
    
    for (i=0; ; i++)
    {
        if(NULL == suit->func_array[i])
            break;
        total_func_num++;
        (suit->func_array[i])();
		if (last_cunit_fail_case_num < gdyshi_cunit_fail_case_num)
        {
            fail_func_num++;
        }
		last_cunit_fail_case_num = gdyshi_cunit_fail_case_num;
    }
    GDYSHI_DEBUG_WARNING("test suit %s result:\r\n",suit->name);
    GDYSHI_DEBUG_WARNING("%d functions of %d functions failed\r\n",
                    fail_func_num,total_func_num);
    GDYSHI_DEBUG_WARNING("%d cases of %d cases failed\r\n",
                    gdyshi_cunit_fail_case_num,gdyshi_cunit_total_case_num);
    ret = (0 == gdyshi_cunit_fail_case_num)? 0 :1;
    return ret;
}
