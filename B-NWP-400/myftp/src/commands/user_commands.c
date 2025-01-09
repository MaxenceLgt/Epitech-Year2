/*
** EPITECH PROJECT, 2023
** B-NWP-400-REN-4-1-myftp-maxence.largeot [WSL: Ubuntu-22.04]
** File description:
** user.c
*/

#include <string.h>
#include <unistd.h>
#include "commands.h"

void handle_user(client_s *client, UNUSED server_s *server, char **args)
{
    char username[] = "331 User name okay, need password.\n";

    if (client->clientData.username != NULL) {
        free(client->clientData.username);
        client->clientData.username = NULL;
    }
    if (args[1] == NULL || args[2] != NULL)
        return write_invalid_command(client);
    client->clientData.username = strdup(args[1]);
    write(client->clientData.clientFd, username, 35);
    return reset_client_command(client);
}

void handle_pass(client_s *client, UNUSED server_s *server, char **args)
{
    char validLog[] = "230 User logged in, proceed.\n";
    char invalidLog[] = "332 Need account for login.\n";
    char badSequence[] = "530 Not login.\n";

    if (!args[1] && client->clientData.username &&
        strcmp(client->clientData.username, "Anonymous") == 0) {
        client->clientData.connectedUser = true;
        write(client->clientData.clientFd, validLog, 29);
    } else if (!client->clientData.username) {
        client->clientData.connectedUser = false;
        write(client->clientData.clientFd, invalidLog, 28);
    } else {
        client->clientData.connectedUser = false;
        write(client->clientData.clientFd, badSequence, 15);
    }
    return reset_client_command(client);
}

void handle_quit(client_s *client, UNUSED server_s *server, char **args)
{
    char disconected[] = "221 Service closing control connection.\n";

    if (args[1] != NULL)
        return write_invalid_command(client);
    client->clientData.logout = true;
    write(client->clientData.clientFd, disconected, 40);
    close(client->clientData.clientFd);
    return reset_client_command(client);
}
