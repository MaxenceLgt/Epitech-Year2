/*
** EPITECH PROJECT, 2023
** ml_add_node_front
** File description:
** ml_add_node_front
*/

#include <stdlib.h>
#include "ml_list_h.h"

static mnode_t *create_node_front(mlist_t *list, void *data)
{
    mnode_t *node = malloc(sizeof(mnode_t));

    if (!list || !data || !node)
        return NULL;
    node->next = list->head;
    node->prev = NULL;
    node->data = data;
    return node;
}

void ml_add_node_front(mlist_t *list, void *data)
{
    mnode_t *node = create_node_front(list, data);

    if (!list || !data || !node)
        return;
    if (list->size == 0) {
        list->head = node;
        list->tail = node;
    } else {
        list->head->prev = node;
        list->head = node;
    }
    list->size += 1;
}
