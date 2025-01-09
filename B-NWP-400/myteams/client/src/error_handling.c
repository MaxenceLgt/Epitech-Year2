/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** error_handling
*/

#include "client_cli.h"

int error_handling(int ac, char **av)
{
    if (ac != 3) {
        printf("\x1b[1;31m");
        printf("USAGE: %s ip port\n", av[0]);
        printf("\x1b[0m");
        return -1;
    }
    return 0;
}
