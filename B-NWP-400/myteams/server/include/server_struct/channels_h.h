/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** channels_h
*/

#ifndef CHANNELS_H_H_
    #define CHANNELS_H_H_

    #include <uuid/uuid.h>
    #include "ml_list_head.h"
    #include "define_h.h"

typedef struct channels_struct {
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    uuid_t uuid;
    mlist_t *threads;
} channels_t;

#endif /* !CHANNELS_H_H_ */
