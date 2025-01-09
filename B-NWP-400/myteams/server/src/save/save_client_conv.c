/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Ubuntu]
** File description:
** save_client_conv
*/

#include "server_h.h"
#include "client_h.h"
#include <stdio.h>
#include <stdlib.h>

int save_client_conv2(FILE *file, client_t *client_data)
{
    conv_t *conv_data;
    char uuid_str[37];
    char uuid_client[37];

    for (mnode_t *temp_conv = client_data->private_conv->head;
        temp_conv != NULL; temp_conv = temp_conv->next) {
        conv_data = (conv_t *)temp_conv->data;
        uuid_unparse_lower(client_data->uuid, uuid_client);
        fprintf(file, "%s;", uuid_client);
        uuid_unparse_lower(conv_data->reciever_uuid, uuid_str);
        fprintf(file, "%s\n", uuid_str);
    }
    return 0;
}

int save_client_conv(mlist_t *save_client)
{
    FILE *file = fopen("saves/client_conv.txt", "w");
    client_t *client_data;

    if (file == NULL)
        return 1;
    if (save_client == NULL) {
        fclose(file);
        return 0;
    }
    for (mnode_t *client = save_client->head; client != NULL;
        client = client->next) {
        client_data = (client_t *)client->data;
        if (save_client_conv2(file, client_data) == 1)
            return 1;
    }
    fclose(file);
    return 0;
}
