/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** handle_err
*/

#include <stdlib.h>

static int check_port_validity(char *port)
{
    for (size_t i = 0; port[i] != '\0'; i++)
        if (port[i] < 48 || port[i] > 57)
            return 84;
    if (atoi(port) > 65535)
        return 84;
    return 0;
}

int handle_err(int ac, char **av)
{
    if (ac != 2 || check_port_validity(av[1]) == 84)
        return 84;
    return 0;
}
