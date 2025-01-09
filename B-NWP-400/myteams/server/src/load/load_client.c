/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Ubuntu]
** File description:
** load_client
*/

#include "server_h.h"
#include "client_h.h"
#include "logging_server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_client(mlist_t *save_client, char *line)
{
    client_t *new_client = malloc(sizeof(client_t));
    char **token = my_str_tok(line, ";");

    strcpy(new_client->username, token[0]);
    uuid_parse(token[1], new_client->uuid);
    new_client->private_conv = ml_create_list();
    server_event_user_loaded(token[1], new_client->username);
    ml_add_node_back(save_client, new_client);
    return;
}

int load_client(mlist_t *save_client)
{
    FILE *file = fopen("saves/client.txt", "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    if (file == NULL)
        return 1;
    read = getline(&line, &len, file);
    while (read != -1) {
        if (line[read - 1] == '\n') {
            line[read - 1] = '\0';
        }
        add_client(save_client, line);
        read = getline(&line, &len, file);
    }
    free(line);
    fclose(file);
    return 0;
}
