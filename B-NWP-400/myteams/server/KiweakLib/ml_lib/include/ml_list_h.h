/*
** EPITECH PROJECT, 2023
** ml_list_h$
** File description:
** ml_list_h
*/

#ifndef ML_LIST_H_
    #define ML_LIST_H_

    #define NULL ((void *)0)
    #include <sys/types.h>

typedef struct ml_list_node {
    void *data;
    struct ml_list_node *next;
    struct ml_list_node *prev;
} mnode_t;

typedef struct ml_list_list {
    size_t size;
    mnode_t *head;
    mnode_t *tail;
} mlist_t;

#endif /* !ML_LIST_H_ */
