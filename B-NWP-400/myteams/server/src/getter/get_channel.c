/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Ubuntu]
** File description:
** get_channel
*/

#include <string.h>
#include "server_h.h"
#include "team_h.h"
#include "channels_h.h"

void search_channel(team_t *team, uuid_t uuid, channels_t *channels)
{
    channels_t *channel_data;

    (void)channels;
    for (mnode_t *channel = team->channels->head; channel != NULL;
        channel = channel->next) {
        channel_data = (channels_t *)channel->data;
        if (uuid_compare(uuid, channel_data->uuid)) {
            channels = channel_data;
            return;
        }
    }
}

channels_t *get_channel(server_t *server, uuid_t uuid)
{
    team_t *team = NULL;
    channels_t *channel = NULL;

    for (mnode_t *node = TEAM; node != NULL; node = node->next) {
        team = (team_t *)node->data;
        search_channel(team, uuid, channel);
        if (channel != NULL)
            return channel;
    }
    return NULL;
}

channels_t *get_channel_from_team(team_t *team, uuid_t uuid)
{
    channels_t *channel = NULL;

    if (!team)
        return NULL;
    for (mnode_t *node = team->channels->head; node; node = node->next) {
        channel = (channels_t *)node->data;
        if (uuid_compare(channel->uuid, uuid) == 0)
            return channel;
    }
    return NULL;
}
