/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** clientList.c
*/

#include "client_list.h"
#include <stdio.h>
#include <sys/select.h>

static void destroy_client_data(client_s *client)
{
    if (client->clientData.dataTransferIp)
        free(client->clientData.dataTransferIp);
    if (client->clientData.username)
        free(client->clientData.username);
    if (client->clientData.cwd)
        free(client->clientData.cwd);
    if (client->clientData.scwd)
        free(client->clientData.scwd);
}

client_l *setup_client_list(void)
{
    client_l *clientList = malloc(sizeof(client_l) * 1);

    if (clientList == NULL) {
        perror("Error : Unexpected error while creating client list.\n");
        exit(84);
    }
    clientList->head = NULL;
    clientList->tail = NULL;
    clientList->size = 0;
    clientList->maxSize = FD_SETSIZE - 1;
    return clientList;
}

void push_client_back(client_l *clientList, client_d clientData)
{
    client_s *client;

    if (clientList->size == clientList->maxSize)
        return;
    client = malloc(sizeof(client_s) * 1);
    if (client == NULL) {
        perror("Error : Unexpected error while adding client to list");
        exit(84);
    }
    client->next = NULL;
    client->prev = clientList->tail;
    client->clientData = clientData;
    if (clientList->head == NULL)
        clientList->head = client;
    if (clientList->tail != NULL)
        clientList->tail->next = client;
    clientList->tail = client;
    clientList->size += 1;
}

void destroy_client_list(client_l *clientList)
{
    client_s *client = NULL;

    if (!clientList)
        return;
    if (clientList->tail) {
        client = clientList->tail;
        while (client->prev) {
            destroy_client_data(client);
            client = client->prev;
            free(client->next);
        }
        free(client);
    }
    free(clientList);
}

void destroy_client_from_list(client_s *client, client_l *client_list)
{
    destroy_client_data(client);
    if (client->prev)
        client->prev->next = client->next;
    if (client->next)
        client->next->prev = client->prev;
    if (client == client_list->head)
        client_list->head = client->next;
    if (client == client_list->tail)
        client_list->tail = client->prev;
    free(client);
}
