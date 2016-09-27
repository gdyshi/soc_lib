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
#include "gdyshi_log.c"
#include "utest_log.h"

void log_init_test(void)
{
    gdyshi_smcu ret = 0;

    ret = gdyshi_log_init(NULL);
    CU_ASSERT(GDYSHI_ENOENT == ret);
    ret = gdyshi_log_init("log.log");
    CU_ASSERT(0 == ret);
}
void log_print_out_test(void)
{
    gdyshi_smcu ret = 0;

    CU_ASSERT(0 == ret);
}

CU_TestFunc log_test_array[] = 
{
    log_init_test,
    log_print_out_test,
    NULL,
};

/*----------------------------------END OF FILE utest.c-------------------------------*/
