/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Ubuntu]
** File description:
** load_threads
*/

#include "client_h.h"
#include "team_h.h"
#include "server_h.h"
#include <stdio.h>
#include "channels_h.h"
#include "threads_h.h"
#include <stdlib.h>
#include <string.h>

void add_thread4(threads_t *new_threads, char *line)
{
    char **token = my_str_tok(line, ";");

    strcpy(new_threads->title, token[2]);
    strcpy(new_threads->body, token[3]);
    new_threads->time_stamp = convert_string_to_time_t(token[4]);
    new_threads->discutions = ml_create_list();
    return;
}

void add_thread3(mlist_t *save_channel, char *line)
{
    channels_t *channel_data;
    threads_t *new_threads = malloc(sizeof(threads_t));
    char **token = my_str_tok(line, ";");
    uuid_t temp_uuid;

    if (token[2] == NULL)
        return;
    uuid_parse(token[1], temp_uuid);
    for (mnode_t *channel = save_channel->head; channel != NULL;
        channel = channel->next) {
        channel_data = (channels_t *)channel->data;
        if (uuid_compare(channel_data->uuid, temp_uuid) == 0) {
            uuid_parse(token[5], new_threads->uuid);
            uuid_parse(token[6], new_threads->creator);
            add_thread4(new_threads, line);
            ml_add_node_back(channel_data->threads, new_threads);
            return;
        }
    }
}

void add_thread2(mlist_t *save_team, char *line)
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
            add_thread3(team_data->channels, line);
            return;
        }
    }
    return;
}

int load_thread(mlist_t *save_team)
{
    FILE *file = fopen("saves/threads.txt", "r");
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
        add_thread2(save_team, line);
        read = getline(&line, &len, file);
    }
    free(line);
    fclose(file);
    return 0;
}
