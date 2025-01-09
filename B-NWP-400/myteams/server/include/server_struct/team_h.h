/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** team_h
*/

#ifndef TEAM_H_H_
    #define TEAM_H_H_

    #include <uuid/uuid.h>
    #include "ml_list_head.h"
    #include "define_h.h"

typedef struct team_struct {
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    uuid_t uuid;
    mlist_t *channels;
    mlist_t *clients;
} team_t;

#endif /* !TEAM_H_H_ */
