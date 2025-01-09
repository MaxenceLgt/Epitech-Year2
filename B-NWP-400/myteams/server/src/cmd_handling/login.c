/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** login
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "server_h.h"
#include "queue_h.h"
#include "client_h.h"
#include "reply_h.h"
#include "logging_server.h"
#include "nc_clients_h.h"

static void destroy_nc_cli(server_t *server, int fd)
{
    nc_client_t *client;

    for (mnode_t *node = NC_CLIENTS; node != NULL; node = node->next) {
        client = (nc_client_t *)node->data;
        if (client->client_fd == fd) {
            ml_destroy_node(server->client_not_connected, node,
                &destroy_nc_client);
            break;
        }
    }
}

static client_t *init_new_client(int fd, char *username)
{
    client_t *client = malloc(sizeof(client_t) * 1);

    memset(client->client_fds, 0, sizeof(int) * 15);
    client->client_fds[0] = fd;
    strcpy(client->username, username);
    client->is_connected = true;
    uuid_generate(client->uuid);
    client->context = malloc(sizeof(context_t));
    client->private_conv = ml_create_list();
    client->size_fds = 1;
    client->context->context = NO_CONTEXT;
    return client;
}

static void create_new_client(server_t *server, reply_t *reply, int fd,
    fd_set *write_set)
{
    client_t *client = init_new_client(fd, reply->user.user_name);
    char uuid[37] = {0};

    uuid_unparse(client->uuid, uuid);
    uuid_copy(reply->user.user_uuid, client->uuid);
    server_event_user_created(uuid, client->username);
    ml_add_node_back(server->client_list, client);
    server_event_user_logged_in(uuid);
    destroy_nc_cli(server, fd);
    return notify_all(server, reply, write_set);
}

static void insert_client(client_t *client, server_t *server, int fd_client)
{
    char uuid[37] = {0};

    if (client->size_fds < 15) {
        client->client_fds[client->size_fds] = fd_client;
        client->size_fds += 1;
    }
    if (!client->is_connected)
        client->is_connected = true;
    uuid_unparse(client->uuid, uuid);
    server_event_user_logged_in(uuid);
    destroy_nc_cli(server, fd_client);
}

void login(char **cmd, server_t *server, queue_t *request, fd_set *write_set)
{
    client_t *client = NULL;
    reply_t reply = {0};

    memset(reply.user.user_name, 0, sizeof(char) * MAX_NAME_LENGTH);
    if (get_array_size(cmd) != 1 || strlen(cmd[0]) > MAX_NAME_LENGTH - 1)
        return write_invalid_code(request->fd_client, ERROR_ARGS, write_set);
    strcpy(reply.user.user_name, cmd[0]);
    strcpy(reply.code, "200");
    client = get_client_by_username(server, cmd[0]);
    if (client != NULL) {
        insert_client(client, server, request->fd_client);
        uuid_copy(reply.user.user_uuid, client->uuid);
        return notify_all(server, &reply, write_set);
    } else
        return create_new_client(server, &reply, request->fd_client,
            write_set);
}
