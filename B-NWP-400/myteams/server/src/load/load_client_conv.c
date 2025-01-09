/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Ubuntu]
** File description:
** load_client_conv
*/

#include "server_h.h"
#include "client_h.h"
#include <stdio.h>
#include <stdlib.h>

void add_client_conv(mlist_t *save_client, char *line)
{
    client_t *client_data;
    conv_t *new_conv = malloc(sizeof(conv_t));
    char **token = my_str_tok(line, ";");
    uuid_t temp_uuid;

    if (token[1] == NULL)
        return;
    uuid_parse(token[0], temp_uuid);
    for (mnode_t *client = save_client->head; client != NULL;
        client = client->next) {
        client_data = (client_t *)client->data;
        if (uuid_compare(client_data->uuid, temp_uuid) == 0) {
            uuid_parse(token[1], new_conv->reciever_uuid);
            new_conv->discution = ml_create_list();
            ml_add_node_back(client_data->private_conv, new_conv);
            return;
        }
    }
    return;
}

int load_client_conv(mlist_t *save_client)
{
    FILE *file = fopen("saves/client_conv.txt", "r");
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
        add_client_conv(save_client, line);
        read = getline(&line, &len, file);
    }
    free(line);
    fclose(file);
    return 0;
}
