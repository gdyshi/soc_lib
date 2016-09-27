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
#ifndef _PROJ_COMM_CONFIG_H_
#define _PROJ_COMM_CONFIG_H_

typedef signed int gdyshi_smcu;
typedef unsigned int gdyshi_umcu;

/* ********************************* ���ܿ��� **************************************** */
#define GDYSHI_CHECK_PARM
#define GDYSHI_ENTER_CRITICAL()
#define GDYSHI_LEAVE_CRITICAL()
#define GDYSHI_USE_STD_LIBC /* ʹ�ñ�׼C�� */
#define GDYSHI_DEBUG

/* ********************************* ģ�鿪�� **************************************** */
#define GDYSHI_MODULE_LOG
#define GDYSHI_MODULE_STACK
#define GDYSHI_MODULE_RING_BUFFER
#define GDYSHI_MODULE_HEAP
#define GDYSHI_MODULE_LIST
#define GDYSHI_MODULE_TIMER

/* ********************************* cunit **************************************** */

/* ********************************* encrypt **************************************** */

/* ********************************* filter **************************************** */

/* ********************************* heap **************************************** */

/* ********************************* list **************************************** */

/* ********************************* log **************************************** */
#ifdef  GDYSHI_MODULE_LOG
#define GDYSHI_MAX_PRINT_BUFFER_LEN   ((gdyshi_umcu)100)/* ��ӡ��������󳤶� */
#define GDYSHI_PRINT_OUT   printf   /* ��ӡ���� */
#ifdef GDYSHI_USE_STD_LIBC
/* ���log���ļ� */
#define GDYSHI_LOG_FILE
/* ʹ�ñ�׼ʱ�亯�� */
#define GDYSHI_USE_STD_TIME
#endif
/* ʹ�ñ�׼�ַ�����ʽ������� */
#define GDYSHI_USE_STRERROR
#endif /* #if GDYSHI_MODULE_LOG */

/* ********************************* queue **************************************** */

/* ********************************* stack **************************************** */

/* ********************************* timer **************************************** */
#ifdef GDYSHI_MODULE_TIMER
#define MS_PER_TICK (10)
#define GDYSHI_MAX_TIMER (10)
#endif /* GDYSHI_MODULE_TIMER */


#endif /* _PROJ_COMM_CONFIG_H_ */
/*----------------------------------END OF FILE types.h-------------------------------*/
