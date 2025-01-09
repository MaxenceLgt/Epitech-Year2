/*
** EPITECH PROJECT, 2023
** my_teams [WSL: Ubuntu-22.04]
** File description:
** unsubscribe.c
*/

#include <string.h>
#include <unistd.h>
#include "queue_h.h"
#include "server_h.h"
#include "logging_server.h"

static void unsubscribe_client_to_team(team_t *team, client_t *client,
    queue_t *request)
{
    client_t *team_cli = NULL;
    reply_t reply = {0};

    strcpy(reply.code, "231");
    uuid_copy(reply.team.uuid, team->uuid);
    uuid_copy(reply.user.user_uuid, client->uuid);
    for (mnode_t *node = team->clients->head; node; node = node->next) {
        team_cli = (client_t *)node->data;
        if (uuid_compare(team_cli->uuid, client->uuid) == 0) {
            ml_destroy_node(team->clients, node, &destroy_client_node);
            write(request->fd_client, &reply, sizeof(reply_t));
            return;
        }
    }
}

void unsubscribe(char **params, server_t *server, queue_t *request,
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
    if (!client_is_already_sub(team, client))
        return write_invalid_code(request->fd_client, "531", write_set);
    unsubscribe_client_to_team(team, client, request);
    uuid_unparse(client->uuid, user_uuid);
    server_event_user_unsubscribed(params[1], user_uuid);
}
