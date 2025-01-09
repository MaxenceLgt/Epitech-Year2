/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** handle_argument_errors.c
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "server.h"

void exit_as_error(char *errorMessage, server_s *server)
{
    if (server) {
        destroy_client_list(server->clientList);
        if (server->serverDir)
            free(server->serverDir);
        free(server);
    }
    write(2, errorMessage, strlen(errorMessage));
    exit(84);
}

static void check_port(char *port, server_s *server)
{
    for (size_t i = 0; port[i] != '\0'; i++) {
        if (port[i] < 48 || port[i] > 57)
            exit_as_error("Error : Invalid port passed as parameter.\n",
                server);
    }
    if (atoi(port) > 65535)
        exit_as_error("Error : Port passed is invalid (0 - 65535).\n",
            server);
}

void handle_argument_errors(int ac, char **av, server_s *server)
{
    if (server == NULL)
        exit_as_error("Error : server malloc return NULL.\n", server);
    memset(server, 0, sizeof(server_s));
    if (ac != 3)
        exit_as_error("Error : Invalid number of argument.\n", server);
    check_port(av[1], server);
    if (chdir(av[2]) == -1)
        exit_as_error("Error : Inavlid path enter as parameter.\n", server);
    server->serverDir = getcwd(NULL, 0);
    if (server->serverDir == NULL)
        exit_as_error("getcwd : ", server);
}
