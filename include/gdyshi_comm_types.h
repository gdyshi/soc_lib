/******************************************************************************
 * Copyright: 2012, gdyshi,Ltd.
 * 
 * File name: types.h
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
#ifndef _GDYSHI_COMM_TYPES_H_
#define _GDYSHI_COMM_TYPES_H_


typedef gdyshi_smcu             gdyshi_bool;
typedef unsigned char	        gdyshi_u8;
typedef signed char	            gdyshi_s8;
typedef unsigned short	        gdyshi_u16;
typedef signed short	        gdyshi_s16;
typedef unsigned int	        gdyshi_u32;
typedef signed int	            gdyshi_s32;
typedef unsigned long long	    gdyshi_u64;
typedef long long               gdyshi_s64;
typedef float                   gdyshi_real32;
typedef double                  gdyshi_real64;

#define GDYSHI_NULL ((void *)0)
#define GDYSHI_TRUE    (1)
#define GDYSHI_FALSE   (0) 

#endif /* _GDYSHI_COMM_TYPES_H_ */
/*----------------------------------END OF FILE types.h-------------------------------*/
