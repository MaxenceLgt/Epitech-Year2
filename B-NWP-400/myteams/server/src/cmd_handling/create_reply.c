/*
** EPITECH PROJECT, 2023
** my_teams [WSL: Ubuntu-22.04]
** File description:
** create_reply.c
*/

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "server_h.h"
#include "queue_h.h"
#include "logging_server.h"
#include "discutions_h.h"

static bool handle_errors_team_param(char **params, team_t *team,
    queue_t *request, fd_set *write_set)
{
    if (get_array_size(params) != 1 || strlen(params[0]) >= MAX_BODY_LENGTH) {
        write_invalid_code(request->fd_client, ERROR_ARGS, write_set);
        return true;
    }
    if (!team) {
        write_invalid_code(request->fd_client, "530", write_set);
        return true;
    }
    return false;
}

static bool handle_errors_chan_thread(channels_t *channel, threads_t *thread,
    queue_t *request, fd_set *write_set)
{
    if (!channel) {
        write_invalid_code(request->fd_client, "540", write_set);
        return true;
    }
    if (!thread) {
        write_invalid_code(request->fd_client, "541", write_set);
        return true;
    }
    return false;
}

static discutions_t *add_message(client_t *client, threads_t *thread,
    char **params)
{
    discutions_t *message = malloc(sizeof(discutions_t) * 1);
    char uuid_creator[37] = {0};
    char uuid_thread[37] = {0};

    uuid_copy(message->sender, client->uuid);
    strcpy(message->message, params[0]);
    message->timestamp = time(NULL);
    uuid_unparse(client->uuid, uuid_creator);
    uuid_unparse(thread->uuid, uuid_thread);
    server_event_reply_created(uuid_thread, uuid_creator, message->message);
    ml_add_node_back(thread->discutions, message);
    return message;
}

static reply_t notify_reply_created(threads_t *thread, discutions_t *message,
    team_t *team)
{
    reply_t reply = {0};

    strcpy(reply.code, "281");
    uuid_copy(reply.team.uuid, team->uuid);
    uuid_copy(reply.thread.uuid, thread->uuid);
    uuid_copy(reply.message.creator, message->sender);
    strcpy(reply.message.body, message->message);
    return reply;
}

static void notify_user(discutions_t *message, queue_t *request,
    threads_t *thread)
{
    reply_t reply = {0};

    strcpy(reply.code, "242");
    strcpy(reply.message.body, message->message);
    uuid_copy(reply.message.creator, message->sender);
    uuid_copy(reply.thread.uuid, thread->uuid);
    reply.message.timestamp = message->timestamp;
    write(request->fd_client, &reply, (sizeof(reply_t)));
}

void create_reply(char **params, server_t *server, queue_t *request,
    fd_set *write_set)
{
    client_t *client = get_client_by_fd(server, request->fd_client);
    team_t *team = get_team(server, client->context->uuid_team);
    channels_t *channel = get_channel_from_team(team,
        client->context->uuid_channel);
    threads_t *thread = get_thread_from_channel(channel,
        client->context->uuid_thread);
    discutions_t *message = NULL;
    reply_t reply = {0};

    if (handle_errors_team_param(params, team, request, write_set))
        return;
    if (!is_client_sub(client, team, request, write_set) ||
        handle_errors_chan_thread(channel, thread, request, write_set))
        return;
    message = add_message(client, thread, params);
    notify_user(message, request, thread);
    reply = notify_reply_created(thread, message, team);
    return notify_team(server, team, &reply, write_set);
}
