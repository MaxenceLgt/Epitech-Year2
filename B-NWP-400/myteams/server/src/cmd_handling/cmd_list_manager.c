/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** cmd_list_manager
*/

#include "server_h.h"
#include "queue_h.h"
#include "client_h.h"
#include "team_h.h"
#include "discutions_h.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>

static void display_replies(threads_t *thread, queue_t *request)
{
    discutions_t *message;
    reply_t reply = {0};

    strcpy(reply.code, "245");
    uuid_copy(reply.thread.uuid, thread->uuid);
    for (mnode_t *node = thread->discutions->head; node; node = node->next) {
        message = (discutions_t *)node->data;
        uuid_copy(reply.message.creator, message->sender);
        reply.message.timestamp = message->timestamp;
        strcpy(reply.message.body, message->message);
        write(request->fd_client, &reply, sizeof(reply_t));
    }
}

void list_replies(server_t *server, queue_t *request, fd_set *write_set)
{
    client_t *client = get_client_by_fd(server, request->fd_client);
    team_t *team = get_team(server, client->context->uuid_team);
    channels_t *channel = get_channel_from_team(team,
        client->context->uuid_channel);
    threads_t *thread = get_thread_from_channel(channel,
        client->context->uuid_thread);

    if (!team)
        return write_invalid_code(request->fd_client, "530", write_set);
    if (!is_client_sub(client, team, request, write_set))
        return;
    if (!channel)
        return write_invalid_code(request->fd_client, "540", write_set);
    if (!thread)
        return write_invalid_code(request->fd_client, "541", write_set);
    display_replies(thread, request);
}

static void display_threads(channels_t *channel, queue_t *request)
{
    threads_t *thread;
    reply_t reply = {0};

    strcpy(reply.code, "244");
    for (mnode_t *node = channel->threads->head; node; node = node->next) {
        thread = (threads_t *)node->data;
        uuid_copy(reply.thread.uuid, thread->uuid);
        uuid_copy(reply.thread.creator, thread->creator);
        strcpy(reply.thread.title, thread->title);
        strcpy(reply.thread.body, thread->body);
        reply.thread.timestamp = thread->time_stamp;
        write(request->fd_client, &reply, sizeof(reply_t));
    }
}

void list_threads(server_t *server, queue_t *request, fd_set *write_set)
{
    client_t *client = get_client_by_fd(server, request->fd_client);
    team_t *team = get_team(server, client->context->uuid_team);
    channels_t *channel = get_channel_from_team(team,
        client->context->uuid_channel);

    if (!team)
        return write_invalid_code(request->fd_client, "530", write_set);
    if (!is_client_sub(client, team, request, write_set))
        return;
    if (!channel)
        return write_invalid_code(request->fd_client, "540", write_set);
    display_threads(channel, request);
}

static void display_channels(team_t *team, queue_t *request)
{
    channels_t *channel = NULL;
    reply_t reply = {0};

    strcpy(reply.code, "234");
    for (mnode_t *node = team->channels->head; node; node = node->next) {
        channel = (channels_t *)node->data;
        uuid_copy(reply.channel.uuid, channel->uuid);
        strcpy(reply.channel.title, channel->name);
        strcpy(reply.channel.description, channel->name);
        write(request->fd_client, &reply, sizeof(reply_t));
    }
}

void list_channels(server_t *server, queue_t *request, fd_set *write_set)
{
    client_t *client = get_client_by_fd(server, request->fd_client);
    team_t *team = get_team(server, client->context->uuid_team);

    if (!team)
        return write_invalid_code(request->fd_client, "530", write_set);
    if (!is_client_sub(client, team, request, write_set))
        return;
    display_channels(team, request);
}

void cmd_list(char **params, server_t *server, queue_t *request,
    fd_set *write_set)
{
    client_t *client = get_client_by_fd(server, request->fd_client);

    if (!client->context || client->context->context == NO_CONTEXT)
        return write_invalid_code(request->fd_client, "594", write_set);
    if (get_array_size(params) != 0)
        return write_invalid_code(request->fd_client, ERROR_ARGS, write_set);
    switch (client->context->context) {
    case USER_C:
        return subscribed(params, server, request, write_set);
    case TEAM_C:
        return list_channels(server, request, write_set);
    case CHANNEL_C:
        return list_threads(server, request, write_set);
    case THREAD_C:
        return list_replies(server, request, write_set);
    default:
        return write_invalid_code(request->fd_client, "594", write_set);
    }
}
