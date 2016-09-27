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
#include "gdyshi_cunit.c"
#include "utest_cunit.h"

void cunit_init_test(void)
{
    gdyshi_smcu ret = 0;

    CU_ASSERT(0 == ret);
}
void cunit_run_suit_test(void)
{
    gdyshi_smcu ret = 0;

    CU_ASSERT(0 == ret);
}

CU_TestFunc cunit_test_array[] = 
{
    cunit_init_test,
    cunit_run_suit_test,
    NULL,
};

/*----------------------------------END OF FILE utest.c-------------------------------*/
