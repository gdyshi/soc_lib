/******************************************************************************
 * Copyright: 2012, gdyshi,Ltd.
 * 
 * File name: example.c
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
#define GDYSHI_DEBUG_LEVEL DEBUG_LEVEL_INFO

#include "includes.h"
#include "xor.h"

int main(void)
{
    u8 code = 0;
    u8 temp_code = 0;
    u8 key = 0;
    u32 fail_count = 0;

    do {
        do {
            temp_code = encry(code, key);
            encry(temp_code, key);
            printf("code:0x%0.2x, key:0x%0.2x encode:0x%0.2x test %s \n",
                code, key, temp_code,
                (code == encry(temp_code, key))? "pass": "fail");
            if (code != encry(temp_code, key))
            {
                fail_count++;
            }
            code++;
        }while(0 != code);
        key++;
    }while(0 != key);
    printf("fail count:%d\n",fail_count);
    return 0;
}

/*----------------------------------END OF FILE example.c-------------------------------*/
