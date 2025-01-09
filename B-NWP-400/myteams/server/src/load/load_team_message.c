/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Ubuntu]
** File description:
** load_team_message
*/

#include "client_h.h"
#include "team_h.h"
#include "server_h.h"
#include <stdio.h>
#include "channels_h.h"
#include "threads_h.h"
#include "discutions_h.h"
#include <stdlib.h>
#include <string.h>

void load_team_message4(mlist_t *save_threads, char *line)
{
    threads_t *threads_data;
    discutions_t *new_discution = malloc(sizeof(discutions_t));
    char **token = my_str_tok(line, ";");
    uuid_t temp_uuid;

    if (token[3] == NULL)
        return;
    uuid_parse(token[2], temp_uuid);
    for (mnode_t *thread = save_threads->head; thread != NULL;
        thread = thread->next) {
        threads_data = (threads_t *)thread->data;
        if (uuid_compare(threads_data->uuid, temp_uuid) == 0) {
            strcpy(new_discution->message, token[3]);
            new_discution->timestamp = convert_string_to_time_t(token[4]);
            ml_add_node_back(threads_data->discutions, new_discution);
            return;
        }
    }
}

void load_team_message3(mlist_t *save_channel, char *line)
{
    channels_t *channel_data;
    char **token = my_str_tok(line, ";");
    uuid_t temp_uuid;

    if (token[2] == NULL)
        return;
    uuid_parse(token[1], temp_uuid);
    for (mnode_t *channel = save_channel->head; channel != NULL;
        channel = channel->next) {
        channel_data = (channels_t *)channel->data;
        if (uuid_compare(channel_data->uuid, temp_uuid) == 0) {
            load_team_message4(channel_data->threads, line);
            return;
        }
    }
    return;
}

void load_team_message2(mlist_t *save_team, char *line)
{
    team_t *team_data;
    char **token = my_str_tok(line, ";");
    uuid_t temp_uuid;

    if (token[1] == NULL)
        return;
    uuid_parse(token[0], temp_uuid);
    for (mnode_t *team = save_team->head; team != NULL;
        team = team->next) {
        team_data = (team_t *)team->data;
        if (uuid_compare(team_data->uuid, temp_uuid) == 0) {
            load_team_message3(team_data->channels, line);
            return;
        }
    }
    return;
}

int load_team_message(mlist_t *save_team)
{
    FILE *file = fopen("saves/team_message.txt", "r");
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
        load_team_message2(save_team, line);
        read = getline(&line, &len, file);
    }
    free(line);
    fclose(file);
    return 0;
}
