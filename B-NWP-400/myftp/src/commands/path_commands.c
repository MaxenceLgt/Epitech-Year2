/*
** EPITECH PROJECT, 2024
** B-NWP-400-REN-4-1-myftp-maxence.largeot
** File description:
** path_commands
*/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "commands.h"
#include "error_handling.h"

static void change_client_path(client_s *client, char *path)
{
    if (path == NULL || strstr(path, client->clientData.scwd) == NULL)
        return reset_client_command(client);
    if (client->clientData.cwd)
        free(client->clientData.cwd);
    asprintf(&client->clientData.cwd, "%s/",
        &path[strlen(client->clientData.scwd)]);
    free(path);
    return reset_client_command(client);
}

void handle_cwd(client_s *client, UNUSED server_s *server, char **args)
{
    char *path;
    char invalidPath[] = "550 Requested action not taken.\n";
    char validPath[] = "250 Requested file action okay, completed.\n";

    if (client->clientData.connectedUser == false)
        return user_not_logged(client);
    if (args[1] == NULL || args[2] != NULL) {
        write(client->clientData.clientFd, invalidPath, 32);
        return reset_client_command(client);
    }
    path = get_folder_path(args[1], client);
    if (path == NULL || strstr(path, client->clientData.scwd) == NULL)
        write(client->clientData.clientFd, invalidPath, 32);
    else
        write(client->clientData.clientFd, validPath, 43);
    return change_client_path(client, path);
}

void handle_pwd(client_s *client, UNUSED server_s *server, char **args)
{
    if (client->clientData.connectedUser == false)
        return user_not_logged(client);
    if (args[1] != NULL)
        return write_invalid_command(client);
    write(client->clientData.clientFd, "257 \"", 5);
    write(client->clientData.clientFd, client->clientData.cwd,
        strlen(client->clientData.cwd));
    write(client->clientData.clientFd, "\"\n", 2);
    return reset_client_command(client);
}

void handle_cdup(client_s *client, UNUSED server_s *server, char **args)
{
    char *path;
    char invalidPath[] = "550 Requested action not taken.\n";
    char validPath[] = "250 Requested file action okay, completed.\n";

    if (client->clientData.connectedUser == false)
        return user_not_logged(client);
    if (args[1] != NULL)
        return write_invalid_command(client);
    path = get_folder_path("../", client);
    if (path == NULL || strstr(path, client->clientData.scwd) == NULL)
        write(client->clientData.clientFd, invalidPath, 32);
    else
        write(client->clientData.clientFd, validPath, 43);
    return change_client_path(client, path);
}
