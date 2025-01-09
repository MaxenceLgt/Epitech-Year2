/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** server.c
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include "server.h"

int setup_server(struct sockaddr_in *serverAddr, char *serverPort)
{
    socklen_t lenAddr = sizeof(struct sockaddr_in);
    int fdServer = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr->sin_family = AF_INET;
    serverAddr->sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr->sin_port = htons(atoi(serverPort));
    if (bind(fdServer, (const struct sockaddr *) serverAddr, lenAddr) == -1) {
        perror("Error : Unexpected error during bind\n");
        exit(84);
    }
    if (listen(fdServer, 30) == -1) {
        perror("Error : Unexpected error during listen\n");
        exit(84);
    }
    return fdServer;
}

void handle_new_connection(server_s *server)
{
    client_d clientData;

    clientData.clientFd = accept(server->serverFd,
    (struct sockaddr *)server->serverAddr, &server->lenAddr);
    clientData.connectionHandled = false;
    clientData.username = NULL;
    clientData.connectedUser = false;
    clientData.dataTransferIp = NULL;
    clientData.dataTransferPort = 0;
    clientData.logout = false;
    clientData.pasv = false;
    clientData.cwd = strdup("/");
    clientData.scwd = strdup(server->serverDir);
    memset(clientData.cmd.command, 0, sizeof(char) * 1024);
    clientData.cmd.index = 0;
    push_client_back(server->clientList, clientData);
}

void check_connection_code(server_s *server, fd_set *writeS)
{
    char succed[] = "220 Service ready for new user.\n";

    for (client_s *client = server->clientList->head; client != NULL;
        client = client->next) {
            if (FD_ISSET(client->clientData.clientFd, writeS) &&
                client->clientData.connectionHandled == false) {
                    write(client->clientData.clientFd, succed, 32);
                    client->clientData.connectionHandled = true;
                }
        }
}
