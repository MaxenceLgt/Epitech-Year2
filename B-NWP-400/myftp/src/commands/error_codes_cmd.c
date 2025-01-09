/*
** EPITECH PROJECT, 2024
** B-NWP-400-REN-4-1-myftp-maxence.largeot
** File description:
** error_codes_cmd
*/

#include <string.h>
#include <unistd.h>
#include "server.h"

void write_invalid_command(client_s *client)
{
    char invalid[] = "500 Syntax error, command unrecognized.\n";

    write(client->clientData.clientFd, invalid, 40);
    client->clientData.cmd.index = 0;
    memset(client->clientData.cmd.command, 0, sizeof(char) * 1024);
}

void reset_client_command(client_s *client)
{
    client->clientData.cmd.index = 0;
    memset(client->clientData.cmd.command, 0, sizeof(char) * 1024);
}

void user_not_logged(client_s *client)
{
    char notLogged[] = "530 Not logged in.\n";

    write(client->clientData.clientFd, notLogged, 19);
    client->clientData.cmd.index = 0;
    memset(client->clientData.cmd.command, 0, sizeof(char) * 1024);
}

void error_in_arguments(client_s *client)
{
    char invalid[] = "550 Requested action not taken.\n";

    write(client->clientData.clientFd, invalid, 32);
    client->clientData.cmd.index = 0;
    memset(client->clientData.cmd.command, 0, sizeof(char) * 1024);
}
