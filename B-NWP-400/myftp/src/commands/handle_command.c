/*
** EPITECH PROJECT, 2024
** handle_command
** File description:
** handle_command
*/

#include <unistd.h>
#include <string.h>
#include "commands.h"

static const f_pointer commands[] = {{"USER", &handle_user},
    {"PASS", &handle_pass}, {"QUIT", &handle_quit}, {"NOOP", &handle_noop},
    {"HELP", &handle_help}, {"PORT", &handle_port}, {"CWD", &handle_cwd},
    {"PWD", &handle_pwd}, {"CDUP", &handle_cdup}, {"PASV", &handle_pasv},
    {"DELE", &handle_delete}, {"LIST", &handle_list}, {"STOR", &handle_stor},
    {"RETR", &handle_retrieve}};

static void concat_cmd_to_user(client_s *client, const char *buffer)
{
    cmd_s cmd = client->clientData.cmd;

    for (size_t i = 0; buffer[i] != '\0'; i++) {
        if (cmd.index >= 1024) {
            cmd.command[cmd.index % 1024] = buffer[i];
            cmd.index = (cmd.index) % 1024;
        } else {
            cmd.command[cmd.index] = buffer[i];
            cmd.index += 1;
        }
    }
    client->clientData.cmd = cmd;
}

static bool is_wfinish_cmd(const char *buffer)
{
    int sizeB = strlen(buffer);

    if (sizeB >= 2 && buffer[sizeB - 2] == '\r' && buffer[sizeB - 1] == '\n')
        return true;
    return false;
}

static void handle_client_command(client_s *client, server_s *server)
{
    char buffer[1024];
    char **command;

    memset(buffer, 0, sizeof(char) * 1024);
    if (read(client->clientData.clientFd, buffer, 1023) == 0)
        return;
    if (!is_wfinish_cmd(buffer))
        return concat_cmd_to_user(client, buffer);
    concat_cmd_to_user(client, buffer);
    if (client->clientData.cmd.command != NULL &&
        client->clientData.cmd.command[0] == ' ')
        return write_invalid_command(client);
    command = split_command(client->clientData.cmd.command, " \t\r\n");
    for (size_t i = 0; i < 14; i++) {
        if (strcmp(command[0], commands[i].command) == 0) {
            return commands[i].fptr(client, server, command);
        }
    }
    return write_invalid_command(client);
}

void handle_commands(server_s *server, fd_set *readSet, fd_set *writeSet)
{
    for (client_s *client = CLIENT_H; client != NULL; client = client->next) {
        if (client->clientData.logout == true) {
            destroy_client_from_list(client, server->clientList);
            client = server->clientList->head;
        }
    }
    for (client_s *client = CLIENT_H; client != NULL; client = client->next) {
        if (client->clientData.connectionHandled == true &&
            FD_ISSET(client->clientData.clientFd, readSet) &&
            FD_ISSET(client->clientData.clientFd, writeSet)) {
                handle_client_command(client, server);
            }
    }
}
