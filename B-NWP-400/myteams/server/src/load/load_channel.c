/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Ubuntu]
** File description:
** load_channel
*/

#include "client_h.h"
#include "team_h.h"
#include "server_h.h"
#include <stdio.h>
#include "channels_h.h"
#include <stdlib.h>
#include <string.h>

void add_channel_team(mlist_t *save_team, char *line)
{
    team_t *team_data;
    channels_t *new_channel = malloc(sizeof(channels_t));
    char **token = my_str_tok(line, ";");
    uuid_t temp_uuid;

    if (token[1] == NULL)
        return;
    uuid_parse(token[0], temp_uuid);
    for (mnode_t *team = save_team->head; team != NULL;
        team = team->next) {
        team_data = (team_t *)team->data;
        if (uuid_compare(team_data->uuid, temp_uuid) == 0) {
            uuid_parse(token[3], new_channel->uuid);
            strcpy(new_channel->name, token[1]);
            strcpy(new_channel->description, token[2]);
            new_channel->threads = ml_create_list();
            ml_add_node_back(team_data->channels, new_channel);
            return;
        }
    }
}

int load_channel(mlist_t *save_team)
{
    FILE *file = fopen("saves/channel.txt", "r");
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
        add_channel_team(save_team, line);
        read = getline(&line, &len, file);
    }
    free(line);
    fclose(file);
    return 0;
}
