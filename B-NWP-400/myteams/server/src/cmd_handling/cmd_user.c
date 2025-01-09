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
#include <stdio.h>

void create_user(reply_t *new_reply, client_t *client_data)
{
    user_t user;

    uuid_copy(user.user_uuid, client_data->uuid);
    strcpy(user.user_name, client_data->username);
    user.user_status = client_data->is_connected;
    new_reply->user = user;
    return;
}

int search_client(mlist_t *user, reply_t *new_reply, char *uuid,
    int fd)
{
    client_t *client_data;
    uuid_t temp_uuid;

    uuid_parse(uuid, temp_uuid);
    for (mnode_t *client = user->head; client != NULL;
        client = client->next) {
        client_data = (client_t *)client->data;
        if (uuid_compare(client_data->uuid, temp_uuid) == 0) {
            strcpy(new_reply->code, "213");
            create_user(new_reply, client_data);
            write(fd, new_reply, sizeof(reply_t));
            return 0;
        }
    }
    return 1;
}

void cmd_user(char **cmd, server_t *server, queue_t *queue, fd_set *write_set)
{
    reply_t new_reply = {0};

    (void)write_set;
    if (get_array_size(cmd) != 1) {
        strcpy(new_reply.code, "592");
        write(queue->fd_client, &new_reply, sizeof(reply_t));
        return;
    }
    if (search_client(server->client_list, &new_reply, cmd[0],
        queue->fd_client) == false) {
        strcpy(new_reply.code, "525");
        write(queue->fd_client, &new_reply, sizeof(reply_t));
        return;
    }
    return;
}
