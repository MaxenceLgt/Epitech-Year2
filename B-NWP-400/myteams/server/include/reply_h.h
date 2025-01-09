/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** reply_h
*/

#ifndef REPLY_H_H_
    #define REPLY_H_H_

    #include <uuid/uuid.h>
    #include <time.h>
    #include <stdbool.h>
    #include "define_h.h"

typedef struct user_s {
    uuid_t user_uuid;
    bool user_status;
    char user_name[MAX_NAME_LENGTH];
} user_t;

typedef struct scope_s {
    uuid_t uuid;
    uuid_t creator;
    time_t timestamp;
    char title[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    char body[MAX_BODY_LENGTH];
} scope_t;

typedef struct reply_s {
    char code[4];
    user_t user;
    scope_t team;
    scope_t channel;
    scope_t thread;
    scope_t message;
} reply_t;

#endif /* !REPLY_H_H_ */
