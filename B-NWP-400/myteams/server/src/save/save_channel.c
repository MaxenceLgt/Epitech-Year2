/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Ubuntu]
** File description:
** save_channel
*/

#include "server_h.h"
#include "team_h.h"
#include "channels_h.h"
#include <stdio.h>
#include <stdlib.h>

int save_channel2(FILE *file, team_t *team_data)
{
    channels_t *channel_data;
    char uuid_str[37];

    if (team_data->channels->head == NULL) {
        return 0;
    }
    for (mnode_t *temp_channel = team_data->channels->head;
        temp_channel != NULL; temp_channel = temp_channel->next) {
        channel_data = (channels_t *)temp_channel->data;
        uuid_unparse_lower(team_data->uuid, uuid_str);
        fprintf(file, "%s;", uuid_str);
        uuid_unparse(channel_data->uuid, uuid_str);
        fprintf(file, "%s;%s;%s\n", channel_data->name,
        channel_data->description, uuid_str);
    }
    return 0;
}

int save_channel(mlist_t *save_team)
{
    FILE *file = fopen("saves/channel.txt", "w");
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
        if (save_channel2(file, team_data) == 1)
            return 1;
    }
    fclose(file);
    return 0;
}
