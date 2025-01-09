/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Ubuntu]
** File description:
** save_team
*/

#include "server_h.h"
#include "client_h.h"
#include <stdio.h>
#include <stdlib.h>

int save_client(mlist_t *save_client)
{
    FILE* file = fopen("saves/client.txt", "w");
    client_t *client_data;
    char uuid_str[37];

    if (file == NULL) {
        return 1;
    }
    if (save_client == NULL) {
        fclose(file);
        return 0;
    }
    for (mnode_t *client = save_client->head; client != NULL;
        client = client->next) {
        client_data = (client_t *)client->data;
        uuid_unparse_lower(client_data->uuid, uuid_str);
        fprintf(file, "%s;%s\n", client_data->username, uuid_str);
    }
    fclose(file);
    return 0;
}
