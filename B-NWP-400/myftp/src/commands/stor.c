/*
** EPITECH PROJECT, 2024
** Untitled (Workspace)
** File description:
** stor
*/

#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "commands.h"

char *get_file_realpath(char *fpath, client_s *client)
{
    char *pathToFile = NULL;
    char *completePath = NULL;
    char **splitedPath = split_command(fpath, "/");
    size_t lenTab = get_len_tab(splitedPath);

    if (splitedPath == NULL)
        return NULL;
    for (size_t i = 0; splitedPath[i] != NULL && splitedPath[i + 1] != NULL;
        i++)
            asprintf(&pathToFile, "%s/", splitedPath[i]);
    completePath = get_folder_path(pathToFile, client);
    free(pathToFile);
    if (completePath != NULL)
        asprintf(&completePath, "%s/%s", completePath,
            splitedPath[lenTab - 1]);
    for (size_t i = 0; splitedPath[i]; i++)
        free(splitedPath[i]);
    free(splitedPath);
    return completePath;
}

static void exec_stor(char *fpath, int readFd)
{
    FILE *fd = fopen(fpath, "w");
    char buffer[1024];
    ssize_t len = 0;

    if (fd == NULL)
        return;
    memset(buffer, 0, sizeof(char) * 1024);
    len = read(readFd, buffer, 1023);
    while (len > 0) {
        fwrite(buffer, 1, len, fd);
        memset(buffer, 0, sizeof(char) * 1024);
        len = read(readFd, buffer, 1023);
    }
    fclose(fd);
}

void handle_stor(client_s *client, server_s *server, char **args)
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
    if (args[1][strlen(args[1]) - 1] == '/')
        return error_in_arguments(client);
    fpath = get_file_realpath(args[1], client);
    if (fpath == NULL)
        return error_in_arguments(client);
    if (client->clientData.pasv == true)
        return handle_pasv_cmd(client, server, &exec_stor, fpath);
    return handle_actv_cmd(client, server, &exec_stor, fpath);
}
