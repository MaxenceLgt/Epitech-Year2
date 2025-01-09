/*
** EPITECH PROJECT, 2024
** Untitled (Workspace)
** File description:
** retrieve
*/

#include "commands.h"

static void exec_retr(char *fpath, int writeFd)
{
    (void)fpath;
    (void)writeFd;
}

void handle_retrieve(client_s *client, server_s *server, char **args)
{
    char *fpath = NULL;

    if (client->clientData.connectedUser == false)
        return user_not_logged(client);
    if (args[1] == NULL || (args[1] != NULL && args[2] != NULL))
        return error_in_arguments(client);
    if (client->clientData.dataTransferIp == NULL) {
        dprintf(client->clientData.clientFd, ERR_425);
        return;
    }
    fpath = get_file_path(args[1], client);
    if (fpath == NULL)
        return error_in_arguments(client);
    if (client->clientData.pasv == true)
        return handle_pasv_cmd(client, server, &exec_retr, fpath);
    return handle_actv_cmd(client, server, &exec_retr, fpath);
}
