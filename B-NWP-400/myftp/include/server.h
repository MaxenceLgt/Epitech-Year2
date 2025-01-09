/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** server.h
*/

#ifndef SERVER_H
    #define SERVER_H

    #include <netinet/in.h>
    #include <sys/select.h>
    #include "client_list.h"

    #define CLIENT_H server->clientList->head

typedef struct server_struct {
    int serverFd;
    struct sockaddr_in *serverAddr;
    char *serverDir;
    socklen_t lenAddr;
    client_l *clientList;
} server_s;

int setup_server(struct sockaddr_in *serverAddr, char *serverPort);
void instantiate_fd_sets(fd_set *readSet, fd_set *writeSet, server_s *server);
void handle_new_connection(server_s *server);
void check_connection_code(server_s *server, fd_set *writeS);

#endif /* SERVER_H */
