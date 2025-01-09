/*
** EPITECH PROJECT, 2024
** B-NWP-400-REN-4-1-myftp-maxence.largeot
** File description:
** file_commands
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "commands.h"

static bool is_existing_file(char *fpath)
{
    if (access(fpath, F_OK) == -1)
        return false;
    return true;
}

static char *check_file_path(char **splitedPath, size_t lenTab,
    char *completePath)
{
    char *file = strdup(splitedPath[lenTab - 1]);

    for (size_t i = 0; splitedPath[i] != NULL; i++)
        free(splitedPath[i]);
    free(splitedPath);
    asprintf(&completePath, "%s/%s", completePath, file);
    free(file);
    if (!is_existing_file(completePath)) {
        free(completePath);
        return NULL;
    }
    return completePath;
}

size_t get_len_tab(char **tab)
{
    size_t len = 0;

    if (!tab)
        return len;
    for (; tab[len] != NULL; len++);
    return len;
}

char *get_file_path(char *fpath, client_s *client)
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
    return check_file_path(splitedPath, lenTab, completePath);
}

char *get_folder_path(char *fpath, client_s *client)
{
    char *path = NULL;

    asprintf(&path, "%s%s", client->clientData.scwd, client->clientData.cwd);
    if (fpath)
        asprintf(&path, "%s%s", path, fpath);
    path = realpath(path, NULL);
    return path;
}

void handle_delete(client_s *client, UNUSED server_s *server, char **args)
{
    char *file;
    char invalidFile[] = "550 Requested action not taken.\n";
    char validFile[] = "250 Requested file action okay, completed.\n";

    if (client->clientData.connectedUser == false)
        return user_not_logged(client);
    if (args[1] == NULL || args[2] != NULL)
        return write_invalid_command(client);
    file = get_file_path(args[1], client);
    if (file == NULL || remove(file) == -1)
        write(client->clientData.clientFd, invalidFile, 32);
    else
        write(client->clientData.clientFd, validFile, 43);
    reset_client_command(client);
}
