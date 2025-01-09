/*
** EPITECH PROJECT, 2023
** my_teams [WSL: Ubuntu-22.04]
** File description:
** create.c
*/

#include "server_h.h"
#include "queue_h.h"
#include "logging_server.h"

void create(char **params, server_t *server, queue_t *request,
    fd_set *write_set)
{
    client_t *client = get_client_by_fd(server, request->fd_client);

    if (!client->context)
        return write_invalid_code(request->fd_client, "594", write_set);
    switch (client->context->context) {
    case USER_C:
        return create_team(params, server, request, write_set);
    case TEAM_C:
        return create_channel(params, server, request, write_set);
    case CHANNEL_C:
        return create_thread(params, server, request, write_set);
    case THREAD_C:
        return create_reply(params, server, request, write_set);
    default:
        return write_invalid_code(request->fd_client, "594", write_set);
    }
}
