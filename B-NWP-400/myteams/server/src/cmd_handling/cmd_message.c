/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Ubuntu]
** File description:
** cmd_message
*/

#include "server_h.h"
#include "queue_h.h"
#include "reply_h.h"
#include "client_h.h"
#include "discutions_h.h"
#include <string.h>
#include <unistd.h>
#include <string.h>

static bool double_fd(client_t *client_data, int fd)
{
    for (int temp = 0; temp != client_data->size_fds; temp++) {
        if (client_data->client_fds[temp] == fd)
            return true;
    }
    return false;
}

static void create_messages(discutions_t *discute, reply_t *new_reply)
{
    scope_t new_message;

    new_message.timestamp = discute->timestamp;
    uuid_copy(new_message.creator, discute->sender);
    strcpy(new_message.body, discute->message);
    new_reply->message = new_message;
    return;
}

void search_message3(conv_t *conv, reply_t *new_reply, int fd)
{
    discutions_t *discussion_data;

    for (mnode_t *discut = conv->discution->head; discut != NULL;
        discut = discut->next) {
        discussion_data = (discutions_t *)discut->data;
        create_messages(discussion_data, new_reply);
        write(fd, new_reply, sizeof(reply_t));
    }
    return;
}

void search_message2(client_t *client, reply_t *new_reply, char *uuid, int fd)
{
    conv_t *conv_data;
    uuid_t temp_uuid;

    uuid_parse(uuid, temp_uuid);
    for (mnode_t *conv = client->private_conv->head; conv != NULL;
        conv = conv->next) {
        conv_data = (conv_t *)conv->data;
        if (uuid_compare(conv_data->reciever_uuid, temp_uuid) == 0) {
            strcpy(new_reply->code, "217");
            search_message3(conv_data, new_reply, fd);
            return;
        }
    }
    return;
}

int search_message(mlist_t *clients, reply_t *new_reply, char *uuid, int fd)
{
    client_t *client_data;

    for (mnode_t *client = clients->head; client != NULL;
        client = client->next) {
        client_data = (client_t *)client->data;
        if (double_fd(client_data, fd)) {
            search_message2(client_data, new_reply, uuid, fd);
            return 0;
        }
    }
    return 1;
}

void cmd_message(char **cmd, server_t *server, queue_t *queue,
    fd_set *write_set)
{
    reply_t new_reply = {0};

    (void)write_set;
    if (cmd[0] == NULL || cmd[1] != NULL) {
        strcpy(new_reply.code, "592");
        write(queue->fd_client, &new_reply, sizeof(reply_t));
        return;
    }
    if (search_message(server->client_list, &new_reply, cmd[0],
        queue->fd_client) == 1) {
        strcpy(new_reply.code, "525");
        write(queue->fd_client, &new_reply, sizeof(reply_t));
        return;
    }
    return;
}
