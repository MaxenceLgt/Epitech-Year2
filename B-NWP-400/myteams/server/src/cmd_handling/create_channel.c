/*
** EPITECH PROJECT, 2023
** my_teams [WSL: Ubuntu-22.04]
** File description:
** create_channel.c
*/

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "server_h.h"
#include "queue_h.h"
#include "logging_server.h"

static bool handle_errors_team(char **params, team_t *team,
    queue_t *request, fd_set *write_set)
{
    if (get_array_size(params) != 2 || strlen(params[0]) >= MAX_NAME_LENGTH ||
        strlen(params[1]) >= MAX_DESCRIPTION_LENGTH) {
        write_invalid_code(request->fd_client, ERROR_ARGS, write_set);
        return true;
    }
    if (!team) {
        write_invalid_code(request->fd_client, "540", write_set);
        return true;
    }
    return false;
}

static bool exist_chan(mlist_t *chan_lst, char *name,
    queue_t *request, fd_set *write_set)
{
    channels_t *channel = NULL;

    for (mnode_t *node = chan_lst->head; node; node = node->next) {
        channel = (channels_t *)node;
        if (strcmp(channel->name, name) == 0) {
            write_invalid_code(request->fd_client, "543", write_set);
            return true;
        }
    }
    return false;
}

bool is_client_sub(client_t *client, team_t *team, queue_t *request,
    fd_set *write_set)
{
    if (client_is_already_sub(team, client))
        return true;
    write_invalid_code(request->fd_client, "531", write_set);
    return false;
}

static channels_t *add_channel(char **params, team_t *team)
{
    channels_t *channel = malloc(sizeof(channels_t) * 1);
    char uuid_team[37] = {0};
    char uuid_channel[37] = {0};

    channel->threads = ml_create_list();
    uuid_generate(channel->uuid);
    strcpy(channel->name, params[0]);
    strcpy(channel->description, params[1]);
    uuid_unparse(team->uuid, uuid_team);
    uuid_unparse(channel->uuid, uuid_channel);
    server_event_channel_created(uuid_team, uuid_channel, channel->name);
    ml_add_node_back(team->channels, channel);
    return channel;
}

static void notify_channel_created(channels_t *chan, team_t *team,
    server_t *server, fd_set *write_set)
{
    reply_t reply = {0};

    strcpy(reply.code, "283");
    strcpy(reply.channel.title, chan->name);
    strcpy(reply.channel.description, chan->description);
    uuid_copy(reply.channel.uuid, chan->uuid);
    notify_team(server, team, &reply, write_set);
}

static void notify_user(channels_t *channel, queue_t *request)
{
    reply_t reply = {0};

    strcpy(reply.code, "240");
    strcpy(reply.channel.title, channel->name);
    strcpy(reply.channel.description, channel->description);
    uuid_copy(reply.channel.uuid, channel->uuid);
    write(request->fd_client, &reply, (sizeof(reply_t)));
}

void create_channel(char **params, server_t *server, queue_t *request,
    fd_set *write_set)
{
    client_t *client = get_client_by_fd(server, request->fd_client);
    team_t *team = get_team(server, client->context->uuid_team);
    channels_t *channel = NULL;

    if (handle_errors_team(params, team, request, write_set))
        return;
    if (!is_client_sub(client, team, request, write_set) ||
        exist_chan(team->channels, params[0], request, write_set))
        return;
    channel = add_channel(params, team);
    notify_user(channel, request);
    return notify_channel_created(channel, team, server, write_set);
}
