/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** set_client
*/

#include "client_cli.h"

server_data_t *set_server_data(char *ip, int port)
{
    server_data_t *server_data = malloc(sizeof(server_data_t));

    server_data->ip = strdup(ip);
    server_data->port = port;
    return server_data;
}

client_t *set_client_struct(int ac, char **av)
{
    client_t *client = malloc(sizeof(client_t));

    (void)ac;
    client->server_data = set_server_data(av[1], atoi(av[2]));
    client->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client->fd < 0) {
        printf("\x1b[1;31mErreur lors de la création du socket\x1b[0m");
        exit(EXIT_FAILURE);
    }
    client->addr.sin_family = AF_INET;
    client->addr.sin_port = htons(client->server_data->port);
    client->addr.sin_addr.s_addr = inet_addr(client->server_data->ip);
    return client;
}

client_t *set_client(int ac, char **av)
{
    client_t *client = set_client_struct(ac, av);

    inet_pton(AF_INET, client->server_data->ip, &client->addr.sin_addr);
    return client;
}
