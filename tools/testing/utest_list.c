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
#include "gdyshi_list.c"
#include "utest_list.h"

#define TEST_DATA 0X56

typedef struct
{
    struct gdyshi_list_head list;
    gdyshi_s32 arg;
}list_t;
typedef struct
{
    struct gdyshi_list_head device_head;
    gdyshi_s32 device_id;
}device_t;

device_t device;

void init_list_node_test(void)
{
    gdyshi_smcu ret = 0;

    ret = gdyshi_init_list_node(NULL);
    CU_ASSERT(GDYSHI_EFAULT == ret);
    
    ret = gdyshi_init_list_node(&(device.device_head));
    CU_ASSERT(0 == ret);
    CU_ASSERT(&(device.device_head) == device.device_head.next);
    CU_ASSERT(&(device.device_head) == device.device_head.prev);
}

void __list_add_del_test(void)
{
    list_t *body_list = NULL;
    
    body_list = malloc(sizeof(list_t));    
    __list_add(&(body_list->list), &(device.device_head), &(device.device_head));
    CU_ASSERT(&(body_list->list) == device.device_head.prev);
    CU_ASSERT(&(body_list->list) == device.device_head.next);
    CU_ASSERT(&(device.device_head) == body_list->list.next);
    CU_ASSERT(&(device.device_head) == body_list->list.prev);
    
    body_list = malloc(sizeof(list_t));    
    __list_add(&(body_list->list), &(device.device_head), device.device_head.next);
    CU_ASSERT(body_list->list.next == device.device_head.prev);
    CU_ASSERT(&(body_list->list) == device.device_head.next);
    CU_ASSERT(device.device_head.next->next == body_list->list.next);
    CU_ASSERT(&(device.device_head) == body_list->list.prev);

    __list_del(body_list->list.prev, body_list->list.next);
    CU_ASSERT(device.device_head.next == device.device_head.prev);
    CU_ASSERT(&(device.device_head) != device.device_head.next);
    free(body_list);

    body_list = gdyshi_list_entry(device.device_head.next, struct gdyshi_list_head, next);
    __list_del(body_list->list.prev, body_list->list.next);
    CU_ASSERT(device.device_head.next == device.device_head.prev);
    CU_ASSERT(&(device.device_head) == device.device_head.next);
    free(body_list);
}

void list_entry_test(void)
{
    gdyshi_smcu ret = 0;
    list_t *body_list = NULL;
    list_t * tmp_list = NULL;
    struct gdyshi_list_head *tmp_list_p = NULL;
    
    body_list = malloc(sizeof(list_t));   
    tmp_list_p = &(body_list->list);
    body_list->arg = 3;    
    tmp_list = gdyshi_list_entry(tmp_list_p, list_t, list);
    CU_ASSERT(3 == tmp_list->arg);
    body_list->arg = 5;    
    tmp_list = gdyshi_list_entry(tmp_list_p, list_t, list);
    CU_ASSERT(5 == tmp_list->arg);
    
    free(body_list);
}

void list_add_del_test(void)
{
    gdyshi_smcu ret = 0;
    list_t *body_list = NULL;
    list_t * tmp_list = NULL;
    struct gdyshi_list_head *tmp_list_p = NULL;
    
    body_list = malloc(sizeof(list_t));   
    body_list->arg = 0;
    gdyshi_init_list_node(&(device.device_head));

    tmp_list_p = device.device_head.next;
    device.device_head.next = NULL;
    ret = gdyshi_list_add(&(body_list->list), &(device.device_head));
    CU_ASSERT(GDYSHI_EFAULT == ret);
    device.device_head.next = tmp_list_p;
    
    ret = gdyshi_list_add(NULL, &(device.device_head));
    CU_ASSERT(GDYSHI_EFAULT == ret);
    ret = gdyshi_list_add(&(body_list->list), NULL);
    CU_ASSERT(GDYSHI_EFAULT == ret);
    
    ret = gdyshi_list_add(&(body_list->list), &(device.device_head));
    CU_ASSERT(GDYSHI_SUCCESS == ret);
    CU_ASSERT(&(body_list->list) == device.device_head.prev);
    CU_ASSERT(&(body_list->list) == device.device_head.next);
    CU_ASSERT(&(device.device_head) == body_list->list.next);
    CU_ASSERT(&(device.device_head) == body_list->list.prev);
    tmp_list = gdyshi_list_entry(device.device_head.next, list_t, list);
    CU_ASSERT(0 == tmp_list->arg);
    
    body_list = malloc(sizeof(list_t));    
    body_list->arg = 1;
    ret = gdyshi_list_add(&(body_list->list), device.device_head.next);
    CU_ASSERT(GDYSHI_SUCCESS == ret);
    CU_ASSERT(body_list->list.prev == device.device_head.next);
    CU_ASSERT(&(body_list->list) == device.device_head.next->next);
    CU_ASSERT(&(device.device_head) == body_list->list.next);
    tmp_list = gdyshi_list_entry(device.device_head.next, list_t, list);
    CU_ASSERT(0 == tmp_list->arg);
    tmp_list = gdyshi_list_entry(device.device_head.next->next, list_t, list);
    CU_ASSERT(1 == tmp_list->arg);

    tmp_list_p = body_list->list.next;
    body_list->list.next = NULL;
    ret = gdyshi_list_del(&(body_list->list));
    CU_ASSERT(GDYSHI_EFAULT == ret);
    tmp_list = gdyshi_list_entry(device.device_head.next, list_t, list);
    CU_ASSERT(0 == tmp_list->arg);
    body_list->list.next = tmp_list_p;

    tmp_list_p = body_list->list.prev;
    body_list->list.prev = NULL;
    ret = gdyshi_list_del(&(body_list->list));
    CU_ASSERT(GDYSHI_EFAULT == ret);
    body_list->list.prev = tmp_list_p;

    ret = gdyshi_list_del(NULL);
    CU_ASSERT(GDYSHI_EFAULT == ret);
    
    ret = gdyshi_list_del(&(body_list->list));
    CU_ASSERT(GDYSHI_SUCCESS == ret);
    CU_ASSERT(device.device_head.next == device.device_head.prev);
    CU_ASSERT(&(device.device_head) != device.device_head.next);
    free(body_list);

    //body_list = device.device_head.next;
    body_list = gdyshi_list_entry(device.device_head.next, struct gdyshi_list_head, next);
    ret = gdyshi_list_del(&(body_list->list));
    CU_ASSERT(GDYSHI_SUCCESS == ret);
    CU_ASSERT(device.device_head.next == device.device_head.prev);
    CU_ASSERT(&(device.device_head) == device.device_head.next);
    free(body_list);
}

void list_add_tail_test(void)
{
    gdyshi_smcu ret = 0;
    list_t *body_list = NULL;
    list_t * tmp_list = NULL;
    struct gdyshi_list_head *tmp_list_p = NULL;
    
    body_list = malloc(sizeof(list_t));   
    body_list->arg = 2;
    gdyshi_init_list_node(&(device.device_head));
    
    ret = gdyshi_list_add_tail(NULL, &(device.device_head));
    CU_ASSERT(GDYSHI_EFAULT == ret);
    ret = gdyshi_list_add_tail(&(body_list->list), NULL);
    CU_ASSERT(GDYSHI_EFAULT == ret);
    
    tmp_list_p = device.device_head.prev;
    device.device_head.prev = NULL;
    ret = gdyshi_list_add_tail(&(body_list->list), &(device.device_head));
    CU_ASSERT(GDYSHI_EFAULT == ret);
    device.device_head.prev = tmp_list_p;
    
    ret = gdyshi_list_add_tail(&(body_list->list), &(device.device_head));
    CU_ASSERT(GDYSHI_SUCCESS == ret);
    CU_ASSERT(&(body_list->list) == device.device_head.prev);
    CU_ASSERT(&(body_list->list) == device.device_head.next);
    CU_ASSERT(&(device.device_head) == body_list->list.next);
    CU_ASSERT(&(device.device_head) == body_list->list.prev);
    tmp_list = gdyshi_list_entry(device.device_head.next, list_t, list);
    CU_ASSERT(2 == tmp_list->arg);
    
    body_list = malloc(sizeof(list_t));    
    body_list->arg = 3;
    ret = gdyshi_list_add_tail(&(body_list->list), device.device_head.next);
    CU_ASSERT(GDYSHI_SUCCESS == ret);
    CU_ASSERT(body_list->list.next == device.device_head.prev);
    CU_ASSERT(&(body_list->list) == device.device_head.next);
    CU_ASSERT(device.device_head.next->next == body_list->list.next);
    CU_ASSERT(&(device.device_head) == body_list->list.prev);
    tmp_list = gdyshi_list_entry(device.device_head.next, list_t, list);
    CU_ASSERT(3 == tmp_list->arg);
    tmp_list = gdyshi_list_entry(device.device_head.next->next, list_t, list);
    CU_ASSERT(2 == tmp_list->arg);

    gdyshi_list_del(&(body_list->list));
    free(body_list);

    //body_list = device.device_head.next;
    body_list = gdyshi_list_entry(device.device_head.next, struct gdyshi_list_head, next);
    gdyshi_list_del(&(body_list->list));
    free(body_list);
}

void list_is_empty_test(void)
{
    gdyshi_smcu ret = 0;
	gdyshi_bool result = 0;
    list_t *body_list = NULL;
    
    gdyshi_init_list_node(&(device.device_head));
	ret = gdyshi_list_is_empty(&(device.device_head));
	CU_ASSERT(1 == ret);

    body_list = malloc(sizeof(list_t));   
    gdyshi_list_add(&(body_list->list), &(device.device_head));    
    
	ret = gdyshi_list_is_empty(NULL);
    CU_ASSERT(GDYSHI_EFAULT == ret);   
	ret = gdyshi_list_is_empty(&(device.device_head));
    CU_ASSERT(0 == ret);

    //body_list = device.device_head.next;
    body_list = gdyshi_list_entry(device.device_head.next, struct gdyshi_list_head, next);
    gdyshi_list_del(&(body_list->list));
    free(body_list);
}

void gdyshi_list_for_each_entry_safe_win_test(void)
{
    gdyshi_smcu ret = 0;
    gdyshi_smcu i = 0;
    list_t *body_list = NULL;    
    list_t * tmp_list = NULL;
    list_t * list_pos = NULL;
    list_t * t_list_pos = NULL;
    
    gdyshi_init_list_node(&(device.device_head));   

    for (i=1; i<6; i++)
    {
        gdyshi_list_for_each_entry_safe_win(list_pos, list_t, t_list_pos, &(device.device_head), list);
        body_list = malloc(sizeof(list_t));
        body_list->arg = i;
        gdyshi_list_add_tail(&(body_list->list), &(device.device_head));    
    }

    i=1;
    gdyshi_list_for_each_entry_safe_win(list_pos, list_t, t_list_pos, &(device.device_head), list)
    {
        CU_ASSERT(i == list_pos->arg);    
        gdyshi_list_del(&(list_pos->list));
        free(list_pos);
        i++;
    }
    CU_ASSERT(i == 6);    
    
}

CU_TestFunc list_test_array[] = 
{
    init_list_node_test,
    __list_add_del_test,
    list_entry_test,
    list_add_del_test,
    list_add_tail_test,
    list_is_empty_test,
    gdyshi_list_for_each_entry_safe_win_test,
    NULL,
};

/*----------------------------------END OF FILE utest.c-------------------------------*/
