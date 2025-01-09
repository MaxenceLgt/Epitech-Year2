/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** destroy_server
*/

#include <stdlib.h>
#include "server_h.h"
#include "nc_clients_h.h"

server_t *destroy_server(server_t *server)
{
    if (!server)
        return NULL;
    ml_destroy_list(server->team_list, NULL);
    ml_destroy_list(server->request_queue, NULL);
    ml_destroy_list(server->client_list, NULL);
    free(server);
    return NULL;
}

void destroy_nc_client(void *data)
{
    nc_client_t *client = (nc_client_t *)data;

    free(client);
}

void destroy_queue_node(void *data)
{
    queue_t *command = (queue_t *)data;

    free(command);
}

void destroy_client_node(void *data)
{
    client_t *client = (client_t *)data;

    if (client->context)
        free(client->context);
    if (client->private_conv)
        ml_destroy_list(client->private_conv, NULL);
    free(client);
}
