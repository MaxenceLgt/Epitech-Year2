/*
** EPITECH PROJECT, 2023
** ml_destroy_node
** File description:
** ml_destroy_node
*/

#include <stdlib.h>
#include "ml_list_h.h"

void ml_destroy_node(mlist_t *list, mnode_t *node, void (*f_ptr)(void *))
{
    if (!list)
        return;
    if (node != NULL) {
        if (node->prev)
            node->prev->next = node->next;
        if (node->next)
            node->next->prev = node->prev;
        if (list->head == node)
            list->head = node->next;
        if (list->tail == node)
            list->tail = node->prev;
        if (f_ptr)
            f_ptr(node->data);
        free(node);
        list->size--;
    }
}
