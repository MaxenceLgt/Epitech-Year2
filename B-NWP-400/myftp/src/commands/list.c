/*
** EPITECH PROJECT, 2024
** Untitled (Workspace)
** File description:
** list
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"

static void handle_fopen(char *fpath, int writeFd)
{
    FILE *fp;
    char *command = NULL;
    char buffer[1024];
    char *result = NULL;

    asprintf(&command, "%s %s", "ls", fpath);
    memset(buffer, 0, sizeof(char) * 1024);
    fp = popen(command, "r");
    while (fgets(buffer, (sizeof(buffer) - 1), fp) != NULL) {
        if (result)
            asprintf(&result, "%s%s", result, buffer);
        else
            asprintf(&result, "%s", buffer);
    }
    pclose(fp);
    write(writeFd, result, strlen(result));
}

static struct sockaddr_in setup_data_transfer(client_s *client)
{
    struct sockaddr_in addr;

    client->clientData.dataTransferFd = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(client->clientData.dataTransferIp);
    addr.sin_port = htons(client->clientData.dataTransferPort);
    return addr;
}

static void handle_fork(client_s *client, UNUSED server_s *server,
    void (*fptr)(), char *fpath)
{
    int pid = fork();

    if (pid == -1) {
        dprintf(client->clientData.clientFd, ERR_425);
        return;
    } else if (pid == 0) {
        fptr(fpath, client->clientData.dataTransferFd);
    } else {
        write(client->clientData.clientFd, SUCC_226, strlen(SUCC_226));
        close(client->clientData.dataTransferFd);
        client->clientData.dataTransferPort = 0;
        free(client->clientData.dataTransferIp);
        client->clientData.dataTransferIp = NULL;
    }
}

void handle_pasv_cmd(client_s *client, server_s *server,
    void (*fptr)(), char *fpath)
{
    struct sockaddr_in addr = setup_data_transfer(client);
    socklen_t lenAddr = sizeof(struct sockaddr_in);
    int socketFd = client->clientData.dataTransferFd;

    if (bind(socketFd, (const struct sockaddr *)&addr, lenAddr) == -1) {
        dprintf(client->clientData.clientFd, ERR_425);
        return;
    }
    if (listen(socketFd, 1) == -1) {
        dprintf(client->clientData.clientFd, ERR_425);
        return;
    }
    write(client->clientData.clientFd, SUCC_150, strlen(SUCC_150));
    client->clientData.dataTransferFd = accept(socketFd,
        (struct sockaddr *)&addr, &lenAddr);
    return handle_fork(client, server, fptr, fpath);
}

void handle_actv_cmd(client_s *client, server_s *server, void (*fptr)(),
    char *fpath)
{
    struct sockaddr_in addr = setup_data_transfer(client);
    socklen_t lenAddr = sizeof(struct sockaddr_in);

    if (connect(client->clientData.dataTransferFd, &addr, lenAddr) == -1) {
        dprintf(client->clientData.clientFd, ERR_425);
        return;
    }
    write(client->clientData.clientFd, SUCC_150, strlen(SUCC_150));
    handle_fork(client, server, fptr, fpath);
}

void handle_list(client_s *client, server_s *server, char **args)
{
    char *fpath = NULL;

    if (client->clientData.connectedUser == false)
        return user_not_logged(client);
    if (args[1] != NULL && args[2] != NULL)
        return error_in_arguments(client);
    if (client->clientData.dataTransferIp == NULL) {
        dprintf(client->clientData.clientFd, ERR_425);
        return;
    }
    if (args[1] == NULL)
        fpath = get_folder_path(NULL, client);
    else
        fpath = get_folder_path(args[1], client);
    if (fpath == NULL)
        return error_in_arguments(client);
    if (client->clientData.pasv == true)
        return handle_pasv_cmd(client, server, &handle_fopen, fpath);
    return handle_actv_cmd(client, server, &handle_fopen, fpath);
}
