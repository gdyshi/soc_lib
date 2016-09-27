/******************************************************************************
 * Copyright: 2012, gdyshi,Ltd.
 * 
 * File name: includes.h
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
#ifndef _GDYSHI_COMM_INCLUDE_H_
#define _GDYSHI_COMM_INCLUDE_H_

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------- ϵͳͨ��ͷ�ļ� -------------------------------*/
//#include <sys/types.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#ifdef GDYSHI_USE_STD_LIBC
#include <stdlib.h>
#endif /* GDYSHI_USE_STD_LIBC */

/*---------------------------------- �Զ���ͷ�ļ� -------------------------------*/

#include "gdyshi_comm_config.h"/* �Զ����������� */
#include "gdyshi_comm_types.h"/* �Զ����������� */
#include "gdyshi_comm_errno.h"/* ����š�����ֵͷ�ļ� */
#include "gdyshi_comm_debug.h"/* ���Զ���ͷ�ļ� */
#include "gdyshi_comm_lib.h"/* ͨ�ÿⶨ�� */

#ifdef __cplusplus
}
#endif

#endif /* _GDYSHI_COMM_INCLUDE_H_ */
/*----------------------------------END OF FILE includes.h-------------------------------*/
