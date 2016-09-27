#include "gdyshi_includes.h"
#include "gdyshi_list.h"

#undef __MODULE_NAME__
#define __MODULE_NAME__     "LIST"
#undef LOG_VALUE
#define LOG_VALUE   GDYSHI_LOG_LEVEL_INFO | GDYSHI_LOG_LITE_MODULE | GDYSHI_LOG_LITE_FUNC | GDYSHI_LOG_LITE_LINE | GDYSHI_LOG_LITE_TIME

/*
 * Insert a new_node entry between two known consecutive entries. 
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static void __list_add(struct gdyshi_list_head *new_node,
                                    struct gdyshi_list_head *prev,
                                    struct gdyshi_list_head *next)
{
    GDYSHI_DEBUG_POS();
    next->prev = new_node;
    new_node->next = next;
    new_node->prev = prev;
    prev->next = new_node;
}

gdyshi_smcu gdyshi_init_list_node(struct gdyshi_list_head *node)
{
    gdyshi_smcu ret = 0;

    GDYSHI_DEBUG_POS();
    GDYSHI_CHECK_POINTER(node);
    
    node->next = node; node->prev = node;

    return ret;
}

/**
 * list_add - add a new_node entry
 * @new_node: new_node entry to be added
 * @head: list head to add it after
 *
 * Insert a new_node entry after the specified head.
 * This is good for implementing stacks.
 */
gdyshi_smcu gdyshi_list_add(struct gdyshi_list_head *new_node, struct gdyshi_list_head *head)
{
    gdyshi_smcu ret = 0;

    GDYSHI_DEBUG_POS();
    GDYSHI_CHECK_POINTER(new_node);
    GDYSHI_CHECK_POINTER(head);
    GDYSHI_CHECK_POINTER(head->next);
    
    __list_add(new_node, head, head->next);

    return ret;
}

/**
 * list_add_tail - add a new_node entry
 * @new_node: new_node entry to be added
 * @head: list head to add it before
 *
 * Insert a new_node entry before the specified head.
 * This is useful for implementing queues.
 */
gdyshi_smcu gdyshi_list_add_tail(struct gdyshi_list_head *new_node, struct gdyshi_list_head *head)
{
    gdyshi_smcu ret = 0;

    GDYSHI_DEBUG_POS();
    GDYSHI_CHECK_POINTER(new_node);
    GDYSHI_CHECK_POINTER(head);
    GDYSHI_CHECK_POINTER(head->prev);

    __list_add(new_node, head->prev, head);

    return ret;
}

/*
 * Delete a list entry by making the prev/next entries
 * point to each other.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static void __list_del(struct gdyshi_list_head *prev, struct gdyshi_list_head *next)
{
    GDYSHI_DEBUG_POS();
    next->prev = prev;
    prev->next = next;
}

/**
 * list_del - deletes entry from list.
 * @entry: the element to delete from the list.
 * Note: list_empty on entry does not return true after this, the entry is in an undefined state.
 */
gdyshi_smcu gdyshi_list_del(struct gdyshi_list_head *entry)
{
    gdyshi_smcu ret = 0;

    GDYSHI_DEBUG_POS();
    GDYSHI_CHECK_POINTER(entry);
    GDYSHI_CHECK_POINTER(entry->prev);
    GDYSHI_CHECK_POINTER(entry->next);

    __list_del(entry->prev, entry->next);
    //entry->next = (struct gdyshi_list_head *)(void *) 0;
    //entry->prev = (struct gdyshi_list_head *)(void *) 0;
    ret = gdyshi_init_list_node(entry); 

    return ret;
}

/**
 * list_empty - tests whether a list is empty
 * @head: the list to test.
 */
gdyshi_smcu gdyshi_list_is_empty(struct gdyshi_list_head *head, gdyshi_bool *result)
{
    gdyshi_smcu ret = 0;

    GDYSHI_DEBUG_POS();
    GDYSHI_CHECK_POINTER(head);
    GDYSHI_CHECK_POINTER(result);

    *result = (head->next == head);

    return ret;
}
