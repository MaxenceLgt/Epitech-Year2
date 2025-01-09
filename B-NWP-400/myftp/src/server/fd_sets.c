/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** fd_sets.c
*/

#include <sys/select.h>
#include "server.h"
#include "client_list.h"

void instantiate_fd_sets(fd_set *readSet, fd_set *writeSet, server_s *server)
{
    FD_ZERO(readSet);
    FD_ZERO(writeSet);
    FD_SET(server->serverFd, readSet);
    FD_SET(server->serverFd, writeSet);
    for (client_s *client = server->clientList->head; client != NULL;
        client = client->next) {
        if (client->clientData.logout == false) {
            FD_SET(client->clientData.clientFd, readSet);
            FD_SET(client->clientData.clientFd, writeSet);
        }
    }
}
