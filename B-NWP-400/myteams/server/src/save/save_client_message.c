/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Ubuntu]
** File description:
** save_client_message
*/

#include "server_h.h"
#include "client_h.h"
#include "discutions_h.h"
#include <stdio.h>
#include <stdlib.h>

char *convert_time_t_to_string(time_t time)
{
    char *time_string = malloc(sizeof(char) * 20);
    struct tm* timeinfo = localtime(&time);

    if (time_string == NULL)
        return NULL;
    strftime(time_string, 20, "%Y-%m-%d %H:%M:%S", timeinfo);
    return time_string;
}

int save_client_message3(FILE *file, conv_t *conv_data, uuid_t client_uuid)
{
    discutions_t *message_data;
    char uuid_client[37];
    char uuid_conv[37];
    char temp_uuid[37];

    for (mnode_t *temp_message = conv_data->discution->head;
        temp_message != NULL; temp_message = temp_message->next) {
        message_data = (discutions_t *)temp_message->data;
        uuid_unparse_lower(client_uuid, uuid_client);
        fprintf(file, "%s;", uuid_client);
        uuid_unparse_lower(conv_data->reciever_uuid, uuid_conv);
        fprintf(file, "%s;", uuid_conv);
        fprintf(file, "%s;", message_data->message);
        fprintf(file, "%s;",
            convert_time_t_to_string(message_data->timestamp));
        uuid_unparse(message_data->sender, temp_uuid);
        fprintf(file, "%s\n", temp_uuid);
    }
    return 0;
}

int save_client_message2(FILE *file, client_t *client_data)
{
    conv_t *conv_data;

    for (mnode_t *temp_conv = client_data->private_conv->head;
        temp_conv != NULL; temp_conv = temp_conv->next) {
        conv_data = (conv_t *)temp_conv->data;
        if (save_client_message3(file, conv_data, client_data->uuid) == 1)
            return 1;
    }
    return 0;
}

int save_client_message(mlist_t *save_client)
{
    FILE *file = fopen("saves/client_message.txt", "w");
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
        if (save_client_message2(file, client_data) == 1)
            return 1;
    }
    fclose(file);
    return 0;
}
