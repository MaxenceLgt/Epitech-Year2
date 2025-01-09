/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** main
*/

#include "client_cli.h"

int main(int ac, char **av)
{
    client_t *client = NULL;
    reply_t *reply = NULL;

    if (error_handling(ac, av) == -1)
        return -1;
    client = set_client(ac, av);
    reply = connect_to_server(client);
    if (reply == NULL)
        return -1;
    client_loop(client, reply);
    return 0;
}
