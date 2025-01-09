/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Ubuntu]
** File description:
** cmd_use
*/

#include "server_h.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static void notify_user(queue_t *request)
{
    reply_t reply = {0};

    strcpy(reply.code, "220");
    write(request->fd_client, &reply, sizeof(reply_t));
}

void cmd_use(char **cmd, server_t *server, queue_t *request, fd_set *write_set)
{
    client_t *client = get_client_by_fd(server, request->fd_client);
    size_t size_args = get_array_size(cmd);

    if (size_args > 3)
        return write_invalid_code(request->fd_client, ERROR_ARGS, write_set);
    if (size_args == 0)
        client->context->context = USER_C;
    if (size_args >= 1) {
        client->context->context = TEAM_C;
        uuid_parse(cmd[0], client->context->uuid_team);
    }
    if (size_args >= 2) {
        client->context->context = CHANNEL_C;
        uuid_parse(cmd[1], client->context->uuid_channel);
    }
    if (size_args == 3) {
        client->context->context = THREAD_C;
        uuid_parse(cmd[2], client->context->uuid_thread);
    }
    return notify_user(request);
}
