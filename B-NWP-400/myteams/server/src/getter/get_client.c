/*
** EPITECH PROJECT, 2023
** my_teams [WSL: Ubuntu-22.04]
** File description:
** get_client.c
*/

#include <string.h>
#include "server_h.h"

static bool client_contains_fd(client_t *client, int fd)
{
    for (int i = 0; i < client->size_fds; i++)
        if (client->client_fds[i] == fd)
            return true;
    return false;
}

client_t *get_client_by_fd(server_t *server, int fd)
{
    client_t *client = NULL;

    for (mnode_t *node = CLIENTS; node != NULL; node = node->next) {
        client = (client_t *)node->data;
        if (client_contains_fd(client, fd))
            return client;
    }
    return NULL;
}

client_t *get_client_by_username(server_t *server, char *username)
{
    client_t *client = NULL;

    for (mnode_t *node = CLIENTS; node != NULL; node = node->next) {
        client = (client_t *)node->data;
        if (strncmp(username, client->username, MAX_NAME_LENGTH - 1) == 0)
            return client;
    }
    return NULL;
}

client_t *get_client_by_uuid(server_t *server, uuid_t uuid)
{
    client_t *client = NULL;

    for (mnode_t *node = CLIENTS; node != NULL; node = node->next) {
        client = (client_t *)node->data;
        if (uuid_compare(uuid, client->uuid) == 0)
            return client;
    }
    return NULL;
}
