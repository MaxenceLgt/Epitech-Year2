/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Ubuntu]
** File description:
** save_team_message
*/

#include "server_h.h"
#include "team_h.h"
#include "channels_h.h"
#include "threads_h.h"
#include <stdio.h>
#include <stdlib.h>
#include "discutions_h.h"

int save_team_message4(FILE *file, threads_t *threads_data,
    uuid_t team, uuid_t channel)
{
    discutions_t *discutions_data;
    char uuid_str[37];

    if (threads_data->discutions->head == NULL) {
        return 0;
    }
    for (mnode_t *temp_discussion = threads_data->discutions->head;
        temp_discussion != NULL; temp_discussion = temp_discussion->next) {
        discutions_data = (discutions_t *)temp_discussion->data;
        uuid_unparse_lower(team, uuid_str);
        fprintf(file, "%s;", uuid_str);
        uuid_unparse(channel, uuid_str);
        fprintf(file, "%s;", uuid_str);
        uuid_unparse(threads_data->uuid, uuid_str);
        fprintf(file, "%s;", uuid_str);
        fprintf(file, "%s;%s\n", discutions_data->message,
        convert_time_t_to_string(discutions_data->timestamp));
    }
    return 0;
}

int save_team_message3(FILE *file, channels_t *channel_data, uuid_t team)
{
    threads_t *thread_data;

    if (channel_data->threads->head == NULL) {
        return 0;
    }
    for (mnode_t *temp_thread = channel_data->threads->head;
        temp_thread != NULL; temp_thread = temp_thread->next) {
        thread_data = (threads_t *)temp_thread->data;
        if (save_team_message4(file, thread_data, team,
            channel_data->uuid) == 1)
            return 1;
    }
    return 0;
}

int save_team_message2(FILE *file, team_t *team_data)
{
    channels_t *channel_data;

    if (team_data->channels->head == NULL) {
        return 0;
    }
    for (mnode_t *temp_channel = team_data->channels->head;
        temp_channel != NULL; temp_channel = temp_channel->next) {
        channel_data = (channels_t *)temp_channel->data;
        if (save_team_message3(file, channel_data, team_data->uuid) == 1)
            return 1;
    }
    return 0;
}

int save_team_message(mlist_t *save_team)
{
    FILE *file = fopen("saves/team_message.txt", "w");
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
        if (save_team_message2(file, team_data) == 1)
            return 1;
    }
    fclose(file);
    return 0;
}
