/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Ubuntu]
** File description:
** cmd_send
*/

#include "server_h.h"
#include "queue_h.h"
#include "reply_h.h"
#include "logging_server.h"
#include "client_h.h"
#include "discutions_h.h"
#include <string.h>
#include <unistd.h>
#include <string.h>

static void fill_discu(char **cmd, int fd, discutions_t *discute,
    server_t *server)
{
    client_t *client;

    client = get_client_by_fd(server, fd);
    strcpy(discute->message, cmd[1]);
    discute->timestamp = time(NULL);
    uuid_copy(discute->sender, client->uuid);
    return;
}

static void fill_first_client(char **cmd, int fd, discutions_t *discute,
    server_t *server)
{
    client_t *client;
    conv_t *conv;
    uuid_t temp_uuid;

    uuid_parse(cmd[0], temp_uuid);
    client = get_client_by_fd(server, fd);
    conv = get_conv(server, get_client_by_fd(server, fd)->uuid, temp_uuid);
    if (conv == NULL) {
        conv = malloc(sizeof(conv_t));
        uuid_copy(conv->reciever_uuid, temp_uuid);
        conv->discution = ml_create_list();
        ml_add_node_back(conv->discution, discute);
        ml_add_node_back(client->private_conv, conv);
        return;
    }
    ml_add_node_back(conv->discution, discute);
}

static void fill_second_client(char **cmd, discutions_t *discute,
    server_t *server, int fd)
{
    client_t *client;
    conv_t *conv;
    uuid_t temp_uuid;

    uuid_parse(cmd[0], temp_uuid);
    client = get_client_by_uuid(server, temp_uuid);
    conv = get_conv(server, temp_uuid, get_client_by_fd(server, fd)->uuid);
    if (conv == NULL) {
        conv = malloc(sizeof(conv_t));
        uuid_copy(conv->reciever_uuid, discute->sender);
        conv->discution = ml_create_list();
        ml_add_node_back(conv->discution, discute);
        ml_add_node_back(client->private_conv, conv);
        return;
    }
    ml_add_node_back(conv->discution, discute);
}

static void fill_scope(reply_t *new_reply, discutions_t *discute,
    client_t *client)
{
    scope_t scope;

    uuid_copy(scope.creator, client->uuid);
    strcpy(scope.body, discute->message);
    scope.timestamp = discute->timestamp;
    new_reply->message = scope;
    return;
}

static void manage_send(char **cmd, server_t *server, queue_t *queue,
    reply_t *new_reply)
{
    discutions_t *discution;
    client_t *client;
    char temp_uuid[37];

    discution = malloc(sizeof(discutions_t));
    fill_discu(cmd, queue->fd_client, discution, server);
    fill_first_client(cmd, queue->fd_client, discution, server);
    fill_second_client(cmd, discution, server, queue->fd_client);
    client = get_client_by_fd(server, queue->fd_client);
    fill_scope(new_reply, discution, client);
    uuid_unparse(client->uuid, temp_uuid);
    server_event_private_message_sended(temp_uuid, cmd[0], cmd[1]);
}

static bool client_exist(server_t *server, char **cmd)
{
    client_t *client;
    uuid_t temp_uuid;

    uuid_parse(cmd[0], temp_uuid);
    client = get_client_by_uuid(server, temp_uuid);
    if (client != NULL)
        return true;
    return false;
}

void create_notif_send(server_t *server, reply_t *new_reply, char **cmd,
    fd_set *write_set)
{
    client_t *client_data;
    uuid_t temp_uuid;

    uuid_parse(cmd[0], temp_uuid);
    client_data = get_client_by_uuid(server, temp_uuid);
    for (int temp = 0; temp != client_data->size_fds; temp++) {
        if (FD_ISSET(client_data->client_fds[temp], write_set)) {
            write(client_data->client_fds[temp], new_reply, sizeof(reply_t));
        }
    }
    return;
}

void cmd_send(char **cmd, server_t *server, queue_t *queue,
    fd_set *write_set)
{
    reply_t new_reply = {0};

    if (get_array_size(cmd) != 2)
        return write_invalid_code(queue->fd_client, "592", write_set);
    if (!client_exist(server, cmd))
        return write_invalid_code(queue->fd_client, "525", write_set);
    manage_send(cmd, server, queue, &new_reply);
    strcpy(new_reply.code, "280");
    create_notif_send(server, &new_reply, cmd, write_set);
}
