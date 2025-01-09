/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Ubuntu]
** File description:
** get_conv
*/

#include <string.h>
#include "server_h.h"

void search_conv(client_t *client, uuid_t uuid, conv_t **conv_new)
{
    conv_t *conv_data;

    for (mnode_t *conv = client->private_conv->head; conv != NULL;
        conv = conv->next) {
        conv_data = (conv_t *)conv->data;
        if (uuid_compare(uuid, conv_data->reciever_uuid) == 0) {
            *conv_new = conv_data;
            return;
        }
    }
}

conv_t *get_conv(server_t *server, uuid_t uuid0, uuid_t uuid1)
{
    client_t *client = NULL;
    conv_t *conv = NULL;

    for (mnode_t *node = CLIENTS; node != NULL; node = node->next) {
        client = (client_t *)node->data;
        if (uuid_compare(uuid0, client->uuid) == 0) {
            search_conv(client, uuid1, &conv);
        }
        if (conv != NULL)
            return conv;
    }
    return NULL;
}
