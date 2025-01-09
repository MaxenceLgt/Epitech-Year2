/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Ubuntu]
** File description:
** cmd_info
*/

#include "server_h.h"
#include <string.h>
#include <unistd.h>

static void info_threads(server_t *server, reply_t *reply, context_t *context)
{
    threads_t *thread;
    scope_t scope;

    if (get_channel(server, context->uuid_channel) == NULL) {
        strcpy(reply->code, "594");
        return;
    }
    thread = get_thread_from_channel(
        get_channel_from_team(get_team(server, context->uuid_team),
        context->uuid_channel), context->uuid_thread);
    if (thread == NULL) {
        strcpy(reply->code, "594");
        return;
    }
    strcpy(scope.title, thread->title);
    uuid_copy(scope.uuid, thread->uuid);
    scope.timestamp = thread->time_stamp;
    strcpy(scope.description, thread->body);
    strcpy(reply->code, "248");
    reply->thread = scope;
}

static void info_channel(server_t *server, reply_t *reply, context_t *context)
{
    channels_t *channel;
    scope_t scope;

    if (get_team(server, context->uuid_team) == NULL) {
        strcpy(reply->code, "594");
        return;
    }
    channel = get_channel_from_team(get_team(server, context->uuid_team),
        context->uuid_channel);
    if (channel == NULL) {
        strcpy(reply->code, "594");
        return;
    }
    strcpy(scope.title, channel->name);
    uuid_copy(scope.uuid, channel->uuid);
    strcpy(scope.description, channel->description);
    strcpy(reply->code, "247");
    reply->channel = scope;
}

static void info_team(server_t *server, reply_t *reply, context_t *context)
{
    team_t *team;
    scope_t scope;

    team = get_team(server, context->uuid_team);
    if (team == NULL) {
        strcpy(reply->code, "594");
        return;
    }
    strcpy(scope.title, team->name);
    uuid_copy(scope.uuid, team->uuid);
    strcpy(scope.description, team->description);
    strcpy(reply->code, "235");
    reply->team = scope;
}

static void info_client(server_t *server, reply_t *reply, queue_t *queue)
{
    client_t *client;
    user_t user;

    client = get_client_by_fd(server, queue->fd_client);
    strcpy(user.user_name, client->username);
    uuid_copy(user.user_uuid, client->uuid);
    user.user_status = client->is_connected;
    strcpy(reply->code, "211");
    reply->user = user;
}

void infos_search(server_t *server, reply_t *reply,
    context_t *contexte, queue_t *queue)
{
    if (contexte->context == USER_C) {
        info_client(server, reply, queue);
        return;
    }
    if (contexte->context == TEAM_C) {
        info_team(server, reply, contexte);
        return;
    }
    if (contexte->context == CHANNEL_C) {
        info_channel(server, reply, contexte);
        return;
    }
    if (contexte->context == THREAD_C) {
        info_threads(server, reply, contexte);
        return;
    }
    strcpy(reply->code, "594");
}

void infos_set(server_t *server, queue_t *queue, reply_t *reply)
{
    client_t *client;

    client = get_client_by_fd(server, queue->fd_client);
    infos_search(server, reply, client->context, queue);
    write(queue->fd_client, reply, sizeof(reply_t));
}

void cmd_infos(char **cmd, server_t *server, queue_t *queue, fd_set *write_set)
{
    reply_t new_reply = {0};

    (void)write_set;
    if (get_array_size(cmd) == 0) {
        infos_set(server, queue, &new_reply);
        return;
    }
    strcpy(new_reply.code, "592");
    write(queue->fd_client, &new_reply, sizeof(reply_t));
    return;
}
