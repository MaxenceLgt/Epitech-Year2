/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** help
*/

#include "client_cli.h"

int client_help(reply_t *event_args)
{
    (void)event_args;
    printf("\x1b[1;33m");
    printf("USAGE: ./myteams_cli ip port\n");
    printf("\x1b[0m");
    printf("\x1b[1;33m");
    printf("DESCRIPTION:\n");
    printf("\x1b[0m");
    printf("\x1b[1;33m");
    printf("\t- ip is the server ip address on which the server listens\n");
    printf("\t- port is the port number on which the server socket listens\n");
    printf("\x1b[0m");
    return 0;
}
