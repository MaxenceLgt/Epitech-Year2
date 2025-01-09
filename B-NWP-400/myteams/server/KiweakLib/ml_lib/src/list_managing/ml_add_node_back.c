/*
** EPITECH PROJECT, 2023
** ml_add_node_back
** File description:
** ml_add_node_back
*/

#include <stdlib.h>
#include "ml_list_h.h"

static mnode_t *create_node_back(mlist_t *list, void *data)
{
    mnode_t *node = malloc(sizeof(mnode_t));

    if (!node || !list || !data)
        return NULL;
    node->next = NULL;
    node->prev = list->tail;
    node->data = data;
    return node;
}

void ml_add_node_back(mlist_t *list, void *data)
{
    mnode_t *node = create_node_back(list, data);

    if (!node || !list || !data)
        return;
    if (list->size == 0) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }
    list->size += 1;
}
