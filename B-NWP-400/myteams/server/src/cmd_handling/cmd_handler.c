/*
** EPITECH PROJECT, 2023
** my_teams [WSL: Ubuntu-22.04]
** File description:
** cmd_handler.c
*/

#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "queue_h.h"
#include "server_h.h"
#include "nc_clients_h.h"

static bool is_wfinish_cmd(const char *buffer)
{
    int sizeB = strlen(buffer);

    if (sizeB >= 1 && buffer[sizeB - 1] == '\n')
        return true;
    return false;
}

static void concat_cmd(queue_t *command, const char *buffer)
{
    for (size_t i = 0; buffer[i] != '\0'; i++) {
        if (command->cmd_index >= 1024) {
            command->command[command->cmd_index % 1024] = buffer[i];
            command->cmd_index = (command->cmd_index) % 1024;
        } else {
            command->command[command->cmd_index] = buffer[i];
            command->cmd_index += 1;
        }
    }
    if (is_wfinish_cmd(command->command))
        command->finish_cmd = true;
}

static void handle_new_request(char *buffer, int client_fd, server_t *server,
    fd_set *write_set)
{
    queue_t *new_request;

    if (server->request_queue->size >= 3000)
        return write_invalid_code(client_fd, "495", write_set);
    new_request = malloc(sizeof(queue_t) * 1);
    new_request->fd_client = client_fd;
    memset(new_request->command, 0, sizeof(char) * 1024);
    strcpy(new_request->command, buffer);
    if (is_wfinish_cmd(new_request->command))
        new_request->finish_cmd = true;
    else
        new_request->finish_cmd = false;
    new_request->cmd_index = strlen(buffer);
    new_request->handle_time = 0;
    ml_add_node_back(server->request_queue, new_request);
}

static void handle_client_command(int client_fd, server_t *server,
    fd_set *write_set)
{
    char buffer[1024];
    queue_t *queued_cmd;

    memset(buffer, 0, sizeof(char) * 1024);
    if (read(client_fd, buffer, 1023) == 0)
        return;
    for (mnode_t *queue_n = QUEUE; queue_n != NULL; queue_n = queue_n->next) {
        queued_cmd = (queue_t *)queue_n->data;
        if (queued_cmd->fd_client == client_fd && !queued_cmd->finish_cmd) {
            concat_cmd(queued_cmd, buffer);
            return;
        }
    }
    return handle_new_request(buffer, client_fd, server, write_set);
}

static void parse_connected_clients(client_t *client, server_t *server,
    fd_set *read_set, fd_set *write_set)
{
    for (int i = 0; i < client->size_fds; i++)
        if (FD_ISSET(client->client_fds[i], read_set))
            handle_client_command(client->client_fds[i], server, write_set);
}

void handle_cmd(server_t *server, fd_set *read_set, fd_set *write_set)
{
    nc_client_t *client_data;
    client_t *client;

    for (mnode_t *nc_client = NC_CLIENTS; nc_client != NULL;
        nc_client = nc_client->next) {
        client_data = (nc_client_t *)nc_client->data;
        if (FD_ISSET(client_data->client_fd, read_set))
                handle_client_command(client_data->client_fd,
                    server, write_set);
    }
    for (mnode_t *node = CLIENTS; node != NULL; node = node->next) {
        client = (client_t *)node->data;
        if (!client->is_connected)
            continue;
        parse_connected_clients(client, server, read_set, write_set);
    }
}
