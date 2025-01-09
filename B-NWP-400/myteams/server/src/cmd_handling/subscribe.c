/*
** EPITECH PROJECT, 2023
** my_teams [WSL: Ubuntu-22.04]
** File description:
** subscribe.c
*/

#include <string.h>
#include <unistd.h>
#include "queue_h.h"
#include "server_h.h"
#include "logging_server.h"
#include <stdio.h>

static void subscribe_client_to_team(team_t *team, client_t *client,
    queue_t *request)
{
    client_t *team_cli = malloc(sizeof(client_t) * 1);
    reply_t reply = {0};

    memset(team_cli, 0, sizeof(client_t));
    uuid_copy(team_cli->uuid, client->uuid);
    ml_add_node_back(team->clients, team_cli);
    strcpy(reply.code, "230");
    uuid_copy(reply.user.user_uuid, client->uuid);
    uuid_copy(reply.team.uuid, team->uuid);
    write(request->fd_client, &reply, sizeof(reply_t));
}

bool client_is_already_sub(team_t *team, client_t *client)
{
    client_t *team_cli;

    for (mnode_t *node = team->clients->head; node; node = node->next) {
        team_cli = (client_t *)node->data;
        if (uuid_compare(team_cli->uuid, client->uuid) == 0)
            return true;
    }
    return false;
}

void subscribe(char **params, server_t *server, queue_t *request,
    fd_set *write_set)
{
    team_t *team = NULL;
    client_t *client = NULL;
    uuid_t team_uuid;
    char user_uuid[37] = {0};

    if (get_array_size(params) != 1)
        return write_invalid_code(request->fd_client, ERROR_ARGS, write_set);
    uuid_parse(params[0], team_uuid);
    team = get_team(server, team_uuid);
    client = get_client_by_fd(server, request->fd_client);
    if (team == NULL)
        return write_invalid_code(request->fd_client, "530", write_set);
    if (client_is_already_sub(team, client))
        return write_invalid_code(request->fd_client, "533", write_set);
    subscribe_client_to_team(team, client, request);
    uuid_unparse(client->uuid, user_uuid);
    server_event_user_subscribed(params[0], user_uuid);
}
