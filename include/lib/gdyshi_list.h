#ifndef __GDYSHI_LIST_H
#define __GDYSHI_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

struct gdyshi_list_head {
	struct gdyshi_list_head *next, *prev;
};

gdyshi_smcu gdyshi_init_list_node(struct gdyshi_list_head *node);

/**
 * list_add - add a new_node entry
 * @new_node: new_node entry to be added
 * @head: list head to add it after
 *
 * Insert a new_node entry after the specified head.
 * This is good for implementing stacks.
 */
gdyshi_smcu gdyshi_list_add(struct gdyshi_list_head *new_node, struct gdyshi_list_head *head);

/**
 * list_add_tail - add a new_node entry
 * @new_node: new_node entry to be added
 * @head: list head to add it before
 *
 * Insert a new_node entry before the specified head.
 * This is useful for implementing queues.
 */
gdyshi_smcu gdyshi_list_add_tail(struct gdyshi_list_head *new_node, struct gdyshi_list_head *head);

/**
 * list_del - deletes entry from list.
 * @entry: the element to delete from the list.
 * Note: list_empty on entry does not return true after this, the entry is in an undefined state.
 */
gdyshi_smcu gdyshi_list_del(struct gdyshi_list_head *entry);

/**
 * list_empty - tests whether a list is empty
 * @head: the list to test.
 */
gdyshi_smcu gdyshi_list_is_empty(struct gdyshi_list_head const * head);

/**
 * list_entry - get the struct for this entry
 * @ptr:	the &struct gdyshi_list_head pointer.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_struct within the struct.
 */
#define gdyshi_list_entry(ptr, type, member) \
    ((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

/**
 * list_for_each	-	iterate over a list
 * @pos:	the &struct gdyshi_list_head to use as a loop counter.
 * @head:	the head for your list.
 */
#define gdyshi_list_for_each(pos, head) \
    for (pos = (head)->next; pos != (head); \
        pos = pos->next)
/**
 * list_for_each_prev	-	iterate over a list backwards
 * @pos:	the &struct gdyshi_list_head to use as a loop counter.
 * @head:	the head for your list.
 */
#define gdyshi_list_for_each_prev(pos, head) \
    for (pos = (head)->prev; pos != (head); \
        pos = pos->prev)

/**
 * list_for_each_safe   iterate over a list safe against removal of list entry
 * @pos:	the &struct gdyshi_list_head to use as a loop counter.
 * @n:		another &struct gdyshi_list_head to use as temporary storage
 * @head:	the head for your list.
 */
#define gdyshi_list_for_each_safe(pos, n, head) \
    for (pos = (head)->next, n = pos->next; pos != (head); \
        pos = n, n = pos->next)

#ifndef __GNUC__
#define gdyshi_list_for_each_entry_win(pos, type, head, member)    \
        for (pos = gdyshi_list_entry((head)->next, type, member);  \
             &pos->member != (head);                    \
             pos = gdyshi_list_entry(pos->member.next, type, member))
#define gdyshi_list_for_each_entry_safe_win(pos, type, n, head, member)    \
        for (pos = gdyshi_list_entry((head)->next, type, member),  \
            n = gdyshi_list_entry(pos->member.next, type, member); \
            &pos->member != (head);    \
            pos = n, n = gdyshi_list_entry(n->member.next, type, member))
#else
/**
 * list_for_each_entry	-	iterate over list of given type
 * @pos:	the type * to use as a loop counter.
 * @head:	the head for your list.
 * @member:	the name of the list_struct within the struct.
 */
#define gdyshi_list_for_each_entry(pos, head, member)  \
        for (pos = gdyshi_list_entry((head)->next, typeof(*pos), member);  \
             &pos->member != (head);    \
             pos = gdyshi_list_entry(pos->member.next, typeof(*pos), member))
/**
 * list_for_each_entry_safe - iterate over list of given type safe against removal of list entry
 * @pos:    the type * to use as a loop counter.
 * @n:      another type * to use as temporary storage
 * @head:   the head for your list.
 * @member: the name of the list_struct within the struct.
 */
#define gdyshi_list_for_each_entry_safe(pos, n, head, member)  \
        for (pos = gdyshi_list_entry((head)->next, typeof(*pos), member),  \
            n = gdyshi_list_entry(pos->member.next, typeof(*pos), member); \
            &pos->member != (head);    \
            pos = n, n = gdyshi_list_entry(n->member.next, typeof(*n), member))
#endif /* __GNUC__ */


#ifdef __cplusplus
}
#endif

#endif
