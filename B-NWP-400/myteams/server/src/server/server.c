/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** server
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "client_h.h"
#include "server_h.h"
#include "channels_h.h"
#include "threads_h.h"
#include "team_h.h"
#include "logging_server.h"
#include "discutions_h.h"

static void set_server_lists(server_t *server)
{
    server->request_queue = ml_create_list();
    server->client_list = ml_create_list();
    server->team_list = ml_create_list();
    server->client_not_connected = ml_create_list();
    server->server_users = 0;
    if (server->request_queue == NULL || server->client_list == NULL ||
    server->team_list == NULL || server->client_not_connected == NULL) {
        server = destroy_server(server);
        return;
    }
    load(server);
}

server_t *init_server(char *port)
{
    server_t *server = malloc(sizeof(server_t) * 1);
    struct sockaddr_in server_addr;

    if (server == NULL)
        return NULL;
    memset(server, 0, sizeof(server_t));
    server->server_fd = socket(AF_INET, SOCK_STREAM, 0);
    server->len_addr = sizeof(struct sockaddr_in);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(port));
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server->server_addr = &server_addr;
    if (bind(server->server_fd, (const struct sockaddr *) server->server_addr,
        server->len_addr) == -1)
            return destroy_server(server);
    if (listen(server->server_fd, 30) == -1)
        return destroy_server(server);
    set_server_lists(server);
    return server;
}
