/*
** EPITECH PROJECT, 2024
** B-NWP-400-REN-4-1-myftp-maxence.largeot
** File description:
** simple_commands
*/

#include <string.h>
#include <unistd.h>
#include "commands.h"

static const char cmds[] =
"214 - USER PASS CWD CDUP QUIT DELE PWD PASV PORT HELP NOOP RETR STOR LIST\n";

void handle_noop(client_s *client, UNUSED server_s *server, char **args)
{
    char noopOk[] = "200 Command okay.\n";

    if (client->clientData.connectedUser == true && args[1] == NULL)
        write(client->clientData.clientFd, noopOk, 18);
    else if (client->clientData.connectedUser == false)
        return user_not_logged(client);
    else
        return write_invalid_command(client);
    return reset_client_command(client);
}

void handle_help(client_s *client, UNUSED server_s *server, char **args)
{
    if (args[1] == NULL || (args[1] != NULL && args[2] == NULL)) {
        write(client->clientData.clientFd, cmds, 74);
        return reset_client_command(client);
    }
    return write_invalid_command(client);
}
