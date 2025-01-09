/*
** EPITECH PROJECT, 2023
** my_teams [WSL: Ubuntu-22.04]
** File description:
** logout.c
*/

#include <string.h>
#include <stdio.h>
#include "server_h.h"
#include "queue_h.h"
#include "nc_clients_h.h"
#include "logging_server.h"

static void add_nc_client(server_t *server, int fd)
{
    nc_client_t *client = malloc(sizeof(nc_client_t) * 1);

    client->client_fd = fd;
    ml_add_node_back(server->client_not_connected, client);
}

static void remove_fd_from_client(client_t *client, int fd)
{
    int pos_fd = 0;

    if (client->size_fds == 1) {
        client->size_fds--;
        client->client_fds[0] = 0;
        client->is_connected = false;
        return;
    }
    for (; client->client_fds[pos_fd] != fd; pos_fd++);
    for (; pos_fd < client->size_fds; pos_fd++) {
        if (pos_fd == 14) {
            client->client_fds[pos_fd] = 0;
            continue;
        }
        client->client_fds[pos_fd] = client->client_fds[pos_fd + 1];
    }
    client->size_fds--;
}

void logout(char **cmd, server_t *server, queue_t *request, fd_set *write_set)
{
    client_t *client = NULL;
    reply_t reply = {0};
    char uuid_cli[37] = {0};

    memset(reply.user.user_name, 0, sizeof(char) * MAX_NAME_LENGTH);
    if (get_array_size(cmd) != 0)
        return write_invalid_code(request->fd_client, ERROR_ARGS, write_set);
    client = get_client_by_fd(server, request->fd_client);
    uuid_unparse(client->uuid, uuid_cli);
    server_event_user_logged_out(uuid_cli);
    strcpy(reply.code, "201");
    strcpy(reply.user.user_name, client->username);
    uuid_copy(reply.user.user_uuid, client->uuid);
    notify_all(server, &reply, write_set);
    remove_fd_from_client(client, request->fd_client);
    add_nc_client(server, request->fd_client);
}
