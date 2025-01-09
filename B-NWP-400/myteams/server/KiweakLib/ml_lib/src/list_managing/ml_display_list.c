/*
** EPITECH PROJECT, 2023
** ml_display_list
** File description:
** ml_display_list
*/

#include "ml_list_h.h"

void ml_display_list(mlist_t *list, void (*f_ptr)(void *))
{
    mnode_t *lst_node = NULL;

    if (!list)
        return;
    lst_node = list->head;
    for (; lst_node; lst_node = lst_node->next)
        if (f_ptr)
            f_ptr(lst_node->data);
}
