/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** notify
*/

#include <unistd.h>
#include "reply_h.h"
#include "server_h.h"
#include "client_h.h"

void notify_client(int client_fd, reply_t *reply, fd_set *write_set)
{
    if (FD_ISSET(client_fd, write_set))
        write(client_fd, reply, sizeof(reply_t));
}

void notify_all(server_t *server, reply_t *reply, fd_set *write_set)
{
    client_t *client;

    for (mnode_t *node = CLIENTS; node != NULL; node = node->next) {
        client = (client_t *)node->data;
        if (!client->is_connected)
            continue;
        for (int i = 0; i < client->size_fds && client->client_fds[i] != 0;
            i++)
            notify_client(client->client_fds[i], reply, write_set);
    }
}

void notify_team(server_t *server, team_t *team, reply_t *reply,
    fd_set *write_set)
{
    client_t *client_uuid;
    client_t *client;

    for (mnode_t *node = team->clients->head; node; node = node->next) {
        client_uuid = (client_t *)node->data;
        client = get_client_by_uuid(server, client_uuid->uuid);
        if (!client->is_connected)
            continue;
        for (int i = 0; i < client->size_fds && client->client_fds[i] != 0;
            i++)
            notify_client(client->client_fds[i], reply, write_set);
    }
}
