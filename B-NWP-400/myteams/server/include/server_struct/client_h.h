/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** client_h
*/

#ifndef CLIENT_H_H_
    #define CLIENT_H_H_

    #include <uuid/uuid.h>
    #include <stdbool.h>
    #include "ml_list_head.h"
    #include "define_h.h"

typedef enum Type {
    NO_CONTEXT,
    USER_C,
    TEAM_C,
    CHANNEL_C,
    THREAD_C
} type_t;

typedef struct context_struct {
    type_t context;
    uuid_t uuid_team;
    uuid_t uuid_channel;
    uuid_t uuid_thread;
} context_t;

typedef struct conv_struct {
    uuid_t reciever_uuid;
    mlist_t *discution;
} conv_t;

typedef struct client_struct {
    char username[MAX_NAME_LENGTH];
    bool is_connected;
    uuid_t uuid;
    int client_fds[15];
    int size_fds;
    context_t *context;
    mlist_t *private_conv;
} client_t;

#endif /* !CLIENT_H_H_ */
