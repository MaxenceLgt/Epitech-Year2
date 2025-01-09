/*
** EPITECH PROJECT, 2023
** my_teams [WSL: Ubuntu-22.04]
** File description:
** server_loop.c
*/

#include <stdio.h>
#include <sys/select.h>
#include <stdbool.h>
#include "client_h.h"
#include "server_h.h"
#include "queue_h.h"
#include "nc_clients_h.h"
#include <signal.h>
#include <unistd.h>
#include <string.h>

static struct {
    server_t *server;
} close_server_t;

static void init_nc_clients_fd(fd_set *read_set, fd_set *write_set,
    server_t *server)
{
    nc_client_t *client_data;

    for (mnode_t *client = NC_CLIENTS; client != NULL; client = client->next) {
        client_data = (nc_client_t *)client->data;
        FD_SET(client_data->client_fd, read_set);
        FD_SET(client_data->client_fd, write_set);
    }
}

static void close_client(client_t *client)
{
    reply_t reply;

    strcpy(reply.code, "666");
    printf("size %d\n", client->size_fds);
    for (int i = 0; i != client->size_fds; i++) {
        write(client->client_fds[i], &reply, sizeof(reply_t));
        printf("Client %d is shutting down...\n", client->client_fds[i]);
    }
}

static void close_nc_client(nc_client_t *client)
{
    reply_t reply;

    strcpy(reply.code, "666");
    write(client->client_fd, &reply, sizeof(reply_t));
    close(client->client_fd);
}

void handle_sigint(int sig)
{
    server_t *server = close_server_t.server;

    (void)sig;
    printf("Server is shutting down...\n");
    for (mnode_t *client = server->client_list->head; client != NULL;
    client = client->next)
        close_client((client_t *)client->data);
    for (mnode_t *client = server->client_not_connected->head; client != NULL;
    client = client->next)
        close_nc_client((nc_client_t *)client->data);
    exit(0);
}

static void instantiate_fd(fd_set *read_set, fd_set *write_set,
    server_t *server)
{
    client_t *client_data;

    FD_ZERO(read_set);
    FD_ZERO(write_set);
    FD_SET(server->server_fd, read_set);
    FD_SET(server->server_fd, write_set);
    init_nc_clients_fd(read_set, write_set, server);
    for (mnode_t *client = CLIENTS; client != NULL; client = client->next) {
        client_data = (client_t *) client->data;
        if (!client_data->is_connected)
            continue;
        for (int i = 0; i != client_data->size_fds; i++) {
            FD_SET(client_data->client_fds[i], read_set);
            FD_SET(client_data->client_fds[i], write_set);
        }
    }
}

int server_loop(server_t *server)
{
    fd_set read_set;
    fd_set write_set;

    while (true) {
        instantiate_fd(&read_set, &write_set, server);
        if (select(FD_SETSIZE, &read_set, &write_set, NULL, NULL) == -1)
            return 0;
        if (FD_ISSET(server->server_fd, &read_set) &&
            server->server_users < FD_SETSIZE - 1) {
            handle_connection(server);
            close_server_t.server = server;
            signal(SIGINT, handle_sigint);
        }
        handle_cmd(server, &read_set, &write_set);
        handle_queue(server, &write_set);
    }
}
