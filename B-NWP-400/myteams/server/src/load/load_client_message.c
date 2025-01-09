/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Ubuntu]
** File description:
** load_client_message
*/

#include "server_h.h"
#include "client_h.h"
#include "discutions_h.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

time_t convert_string_to_time_t(const char *date_string)
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    struct tm tm_time = {0};

    if (sscanf(date_string, "%d-%d-%d %d:%d:%d", &year,
    &month, &day, &hour, &minute, &second) != 6) {
        return (time_t)-1;
    }
    tm_time.tm_year = year - 1900;
    tm_time.tm_mon = month - 1;
    tm_time.tm_mday = day;
    tm_time.tm_hour = hour;
    tm_time.tm_min = minute;
    tm_time.tm_sec = second;
    return mktime(&tm_time);
}

void add_client_message2(mlist_t *conv_save, char **token)
{
    conv_t *conv_data;
    discutions_t *new_message = malloc(sizeof(discutions_t));
    uuid_t temp_uuid;

    if (token[2] == NULL)
        return;
    uuid_parse(token[1], temp_uuid);
    for (mnode_t *conv = conv_save->head; conv != NULL;
        conv = conv->next) {
        conv_data = (conv_t *)conv->data;
        if (uuid_compare(conv_data->reciever_uuid, temp_uuid) == 0) {
            strcpy(new_message->message, token[2]);
            new_message->timestamp = convert_string_to_time_t(token[3]);
            uuid_parse(token[4], new_message->sender);
            ml_add_node_back(conv_data->discution, new_message);
            return;
        }
    }
    return;
}

void add_client_message(mlist_t *save_client, char *line)
{
    client_t *client_data;
    char **token = my_str_tok(line, ";");
    uuid_t temp_uuid;

    uuid_parse(token[0], temp_uuid);
    for (mnode_t *client = save_client->head; client != NULL;
        client = client->next) {
        client_data = (client_t *)client->data;
        if (uuid_compare(client_data->uuid, temp_uuid) == 0) {
            add_client_message2(client_data->private_conv, token);
            return;
        }
    }
    return;
}

int load_client_message(mlist_t *save_client)
{
    FILE *file = fopen("saves/client_message.txt", "r");
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
        add_client_message(save_client, line);
        read = getline(&line, &len, file);
    }
    free(line);
    fclose(file);
    return 0;
}
