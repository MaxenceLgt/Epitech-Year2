/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** subscribed
*/

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "queue_h.h"
#include "server_h.h"
#include "reply_h.h"
#include "team_h.h"
#include "client_h.h"

void display_teams(queue_t *request, mlist_t *team_lst, fd_set *write_set)
{
    reply_t reply = {0};
    team_t *team;

    (void)write_set;
    memset(&reply.team.title, 0, sizeof(char) * MAX_NAME_LENGTH);
    memset(&reply.team.description, 0, sizeof(char) * MAX_NAME_LENGTH);
    strcpy(reply.code, "215");
    for (mnode_t *node = team_lst->head; node != NULL; node = node->next) {
        team = (team_t *)node->data;
        uuid_copy(reply.team.uuid, team->uuid);
        strcpy(reply.team.title, team->name);
        strcpy(reply.team.description, team->description);
        write(request->fd_client, &reply, sizeof(reply_t));
    }
}

void display_user(queue_t *request, mlist_t *client_lst, fd_set *write_set)
{
    reply_t reply = {0};
    client_t *client;

    (void)write_set;
    strcpy(reply.code, "216");
    for (mnode_t *node = client_lst->head; node != NULL; node = node->next) {
        client = (client_t *)node->data;
        uuid_copy(reply.user.user_uuid, client->uuid);
        write(request->fd_client, &reply, sizeof(reply_t));
    }
}

void subscribed(char **params, server_t *server, queue_t *request,
    fd_set *write_set)
{
    team_t *team;
    uuid_t uuid_arg;

    if (!params[0])
        return display_teams(request, server->team_list, write_set);
    if (get_array_size(params) > 1 || uuid_parse(params[0], uuid_arg) == -1)
        return write_invalid_code(request->fd_client, ERROR_ARGS, write_set);
    for (mnode_t *node = TEAM; node != NULL; node = node->next) {
        team = (team_t *)node->data;
        if (uuid_compare(uuid_arg, team->uuid) == 0)
            return display_user(request, team->clients, write_set);
    }
    return write_invalid_code(request->fd_client, "530", write_set);
}
