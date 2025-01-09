/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** main
*/

#include <string.h>
#include "error_handling_h.h"
#include "server_h.h"
#include <stdio.h>

int main(int ac, char **av)
{
    server_t *server = NULL;

    if (handle_err(ac, av) == 84)
        return display_usage(84);
    if (strcmp(av[1], "-h") == 0 || strcmp(av[1], "-help") == 0)
        return display_usage(0);
    server = init_server(av[1]);
    if (server == NULL)
        return 84;
    server_loop(server);
    server = destroy_server(server);
    return 0;
}
