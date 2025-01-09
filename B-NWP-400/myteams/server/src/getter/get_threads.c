/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Ubuntu]
** File description:
** get_threads
*/

#include <string.h>
#include "server_h.h"
#include "team_h.h"
#include "channels_h.h"
#include "threads_h.h"

void search_threads2(uuid_t uuid, channels_t *channels, threads_t *threads_new)
{
    threads_t *threads_data;

    (void)threads_new;
    for (mnode_t *threads = channels->threads->head; threads != NULL;
        threads = threads->next) {
        threads_data = (threads_t *)threads->data;
        if (uuid_compare(uuid, threads_data->uuid)) {
            threads_new = threads_data;
            return;
        }
    }
}

void search_threads(team_t *team, uuid_t uuid, threads_t *threads)
{
    channels_t *channel_data;

    for (mnode_t *channel = team->channels->head; channel != NULL;
        channel = channel->next) {
        channel_data = (channels_t *)channel->data;
        search_threads2(uuid, channel_data, threads);
        if (threads != NULL)
            return;
    }
}

threads_t *get_threads(server_t *server, uuid_t uuid)
{
    team_t *team = NULL;
    threads_t *threads = NULL;

    for (mnode_t *node = TEAM; node != NULL; node = node->next) {
        team = (team_t *)node->data;
        search_threads(team, uuid, threads);
        if (threads != NULL)
            return threads;
    }
    return NULL;
}

threads_t *get_thread_from_channel(channels_t *channel, uuid_t uuid)
{
    threads_t *thread = NULL;

    if (!channel)
        return NULL;
    for (mnode_t *node = channel->threads->head; node; node = node->next) {
        thread = (threads_t *)node->data;
        if (uuid_compare(thread->uuid, uuid) == 0)
            return thread;
    }
    return NULL;
}
