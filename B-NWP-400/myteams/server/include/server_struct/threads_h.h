/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** threads_h
*/

#ifndef THREADS_H_H_
    #define THREADS_H_H_

    #include <uuid/uuid.h>
    #include <time.h>
    #include "ml_list_head.h"
    #include "define_h.h"

typedef struct threads_struct {
    char title[MAX_NAME_LENGTH];
    char body[MAX_BODY_LENGTH];
    time_t time_stamp;
    uuid_t uuid;
    uuid_t creator;
    mlist_t *discutions;
} threads_t;

#endif /* !THREADS_H_H_ */
