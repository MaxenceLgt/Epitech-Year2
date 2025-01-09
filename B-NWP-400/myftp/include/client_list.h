/*
** EPITECH PROJECT, 2023
** network [WSL: Ubuntu-22.04]
** File description:
** client_list.h
*/

#ifndef CLIENT_LIST_H
    #define CLIENT_LIST_H

    #include <stdlib.h>
    #include <stdbool.h>

typedef struct client_command {
    size_t index;
    char command[1024];
} cmd_s;

typedef struct client_data {
    int clientFd;
    int dataTransferFd;
    int dataTransferPort;
    char *dataTransferIp;
    char *cwd;
    char *scwd;
    char *username;
    bool connectionHandled;
    bool pasv;
    bool connectedUser;
    bool logout;
    cmd_s cmd;
} client_d;

typedef struct client_struct {
    client_d clientData;
    struct client_struct *next;
    struct client_struct *prev;
} client_s;

typedef struct client_list {
    client_s *head;
    client_s *tail;
    size_t size;
    size_t maxSize;
} client_l;

client_l *setup_client_list(void);
void destroy_client_list(client_l *clientList);
void push_client_back(client_l *clientList, client_d clientData);
void destroy_client_from_list(client_s *client, client_l *client_list);

#endif /* CLIENT_LIST_H */
