/*
** EPITECH PROJECT, 2023
** ml_create_list
** File description:
** ml_create_list
*/

#include <stdlib.h>
#include "ml_list_h.h"

mlist_t *ml_create_list(void)
{
    mlist_t *list = malloc(sizeof(mlist_t));

    if (!list)
        return NULL;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}
