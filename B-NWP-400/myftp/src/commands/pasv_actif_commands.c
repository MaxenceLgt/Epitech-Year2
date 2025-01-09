/*
** EPITECH PROJECT, 2024
** B-NWP-400-REN-4-1-myftp-maxence.largeot
** File description:
** pasv_actif_commands
*/

#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "commands.h"

static char *get_ip_port(server_s *server)
{
    char *rPasv = NULL;
    char *serverIp = inet_ntoa(server->serverAddr->sin_addr);
    char **splitedIp = split_command(serverIp, ".");

    for (size_t i = 0; splitedIp[i]; i++) {
        if (i == 0)
            asprintf(&rPasv, "%s", splitedIp[i]);
        else
            asprintf(&rPasv, "%s,%s", rPasv, splitedIp[i]);
    }
    for (size_t i = 0; i < 2; i++)
        asprintf(&rPasv, "%s,%i", rPasv, rand() % 256);
    return rPasv;
}

static bool is_num(char *str)
{
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] < 48 || str[i] > 57)
            return false;
    }
    return true;
}

static void handle_client_port(char **portData, client_s *client,
    bool isActive)
{
    client->clientData.dataTransferPort = atoi(portData[4]);
    client->clientData.dataTransferPort *= 256;
    client->clientData.dataTransferPort += atoi(portData[5]);
    for (size_t i = 0; portData[i] != NULL; i++)
        free(portData[i]);
    free(portData);
    if (isActive)
        write(client->clientData.clientFd, "200 Command okay.\n", 18);
    reset_client_command(client);
}

static void handle_ip(char *data, client_s *client, bool isActive)
{
    char **sData = split_command(data, ",");
    size_t dataLen = get_len_tab(sData);

    if (dataLen != 6)
        return error_in_arguments(client);
    for (size_t i = 0; i < 6; i++)
        if (!is_num(sData[i]))
            return error_in_arguments(client);
    for (size_t i = 0; i < 4; i++) {
        if (i != 0)
            asprintf(&client->clientData.dataTransferIp, "%s.%s",
                client->clientData.dataTransferIp, sData[i]);
        else
            asprintf(&client->clientData.dataTransferIp, "%s", sData[i]);
    }
    handle_client_port(sData, client, isActive);
}

void handle_port(client_s *client, UNUSED server_s *server, char **args)
{
    if (client->clientData.connectedUser == false)
        return user_not_logged(client);
    if (client->clientData.dataTransferIp) {
        free(client->clientData.dataTransferIp);
        client->clientData.dataTransferIp = NULL;
    }
    if (args[1] == NULL || args[2] != NULL)
        return error_in_arguments(client);
    client->clientData.pasv = false;
    return handle_ip(args[1], client, true);
}

void handle_pasv(client_s *client, server_s *server, char **args)
{
    char *portIp;

    if (client->clientData.connectedUser == false)
        return user_not_logged(client);
    if (args[1] != NULL)
        return error_in_arguments(client);
    if (client->clientData.dataTransferIp) {
        free(client->clientData.dataTransferIp);
        client->clientData.dataTransferIp = NULL;
    }
    client->clientData.pasv = true;
    portIp = get_ip_port(server);
    dprintf(client->clientData.clientFd, "227 Entering Passive Mode (%s).\n",
        portIp);
    handle_ip(portIp, client, false);
    return reset_client_command(client);
}
