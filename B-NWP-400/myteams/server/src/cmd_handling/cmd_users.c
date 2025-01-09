/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Ubuntu]
** File description:
** cmd_users
*/

#include "server_h.h"
#include "queue_h.h"
#include "reply_h.h"
#include "client_h.h"
#include <string.h>
#include <unistd.h>

bool search_clients(mlist_t *user, reply_t *new_reply, int fd)
{
    client_t *client_data;

    strcpy(new_reply->code, "214");
    for (mnode_t *client = user->head; client != NULL;
        client = client->next) {
        client_data = (client_t *)client->data;
        create_user(new_reply, client_data);
        write(fd, new_reply, sizeof(reply_t));
    }
    return true;
}

void cmd_users(char **cmd, server_t *server, queue_t *queue, fd_set *write_set)
{
    reply_t new_reply = {0};

    (void)write_set;
    if (cmd[0] != NULL) {
        strcpy(new_reply.code, "592");
        write(queue->fd_client, &new_reply, sizeof(reply_t));
        return;
    }
    if (search_clients(server->client_list, &new_reply,
        queue->fd_client) == false) {
        strcpy(new_reply.code, "525");
        write(queue->fd_client, &new_reply, sizeof(reply_t));
        return;
    }
    return;
}
