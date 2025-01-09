/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Ubuntu]
** File description:
** save_thread
*/

#include "server_h.h"
#include "team_h.h"
#include "channels_h.h"
#include "threads_h.h"
#include <stdio.h>
#include <stdlib.h>

int save_thread3(FILE *file, channels_t *channel_data, uuid_t team)
{
    threads_t *thread_data;
    char uuid_str[37];
    char uuid_creator[37];

    if (channel_data->threads->head == NULL)
        return 0;
    for (mnode_t *temp_thread = channel_data->threads->head;
        temp_thread != NULL; temp_thread = temp_thread->next) {
        thread_data = (threads_t *)temp_thread->data;
        uuid_unparse_lower(team, uuid_str);
        fprintf(file, "%s;", uuid_str);
        uuid_unparse(channel_data->uuid, uuid_str);
        fprintf(file, "%s;", uuid_str);
        uuid_unparse(thread_data->uuid, uuid_str);
        uuid_unparse(thread_data->creator, uuid_creator);
        fprintf(file, "%s;%s;%s;%s;%s\n", thread_data->title,
        thread_data->body, convert_time_t_to_string(thread_data->time_stamp)
        , uuid_str, uuid_creator);
    }
    return 0;
}

int save_thread2(FILE *file, team_t *team_data)
{
    channels_t *channel_data;

    if (team_data->channels->head == NULL) {
        return 0;
    }
    for (mnode_t *temp_channel = team_data->channels->head;
        temp_channel != NULL; temp_channel = temp_channel->next) {
        channel_data = (channels_t *)temp_channel->data;
        if (save_thread3(file, channel_data, team_data->uuid) == 1)
            return 1;
    }
    return 0;
}

int save_thread(mlist_t *save_team)
{
    FILE *file = fopen("saves/threads.txt", "w");
    team_t *team_data;

    if (file == NULL)
        return 1;
    if (save_team == NULL) {
        fclose(file);
        return 0;
    }
    for (mnode_t *team = save_team->head; team != NULL;
        team = team->next) {
        team_data = (team_t *)team->data;
        if (save_thread2(file, team_data) == 1)
            return 1;
    }
    fclose(file);
    return 0;
}
