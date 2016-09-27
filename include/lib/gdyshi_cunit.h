/*----------------------------------------------------------------------------
 * Name:    App_wireless_decode.h
 * Purpose: STM32Register values and Bit definitions
 * Version: V1.02
 * Note(s):
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2005-2008 Keil Software. All rights reserved.
 *----------------------------------------------------------------------------
 * History:
 *          V1.02 added register RCC_APB2ENR values
 *          V1.01 added register RCC_CSR values
 *          V1.00 Initial Version
 *----------------------------------------------------------------------------*/

/* Define to prevent recursive inclusion ------------------------------------ */
#ifndef ___GDYSHI_CUNIT_H
#define ___GDYSHI_CUNIT_H

#ifdef __cplusplus
extern "C" {
#endif

/** Simple assertion.
 *  Reports failure with no other action.
 */
#define CU_ASSERT(value) \
  { CU_assertImplementation((value), __LINE__, #value, __FILE__); }
gdyshi_s32 CU_assertImplementation(gdyshi_s32 bValue,
                              gdyshi_u32 uiLine,
                              const char *strCondition, 
                              const char *strFile);


typedef void (*CU_TestFunc)(void);        /**< Signature for a testing function in a test case. */
typedef struct
{
    char * name;
    CU_TestFunc * func_array;
    gdyshi_u32 fun_array_len;
}test_suit_t;

void gdyshi_cunit_init(void);
gdyshi_smcu gdyshi_cunit_run_suit(test_suit_t const * const suit);

#ifdef __cplusplus
}
#endif

#endif
