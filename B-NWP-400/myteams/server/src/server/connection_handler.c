/*
** EPITECH PROJECT, 2023
** my_teams [WSL: Ubuntu-22.04]
** File description:
** connection_handler.c
*/

#include <unistd.h>
#include "server_h.h"
#include "nc_clients_h.h"

void handle_connection(server_t *server)
{
    nc_client_t *new_client;
    int client_fd = accept(server->server_fd,
    (struct sockaddr *)server->server_addr, &server->len_addr);

    if (client_fd == -1)
        return;
    new_client = malloc(sizeof(nc_client_t) * 1);
    if (!new_client)
        return;
    new_client->client_fd = client_fd;
    ml_add_node_back(server->client_not_connected, new_client);
    server->server_users += 1;
}
