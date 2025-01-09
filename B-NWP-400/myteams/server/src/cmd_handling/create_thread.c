/*
** EPITECH PROJECT, 2023
** my_teams [WSL: Ubuntu-22.04]
** File description:
** create_team_channel.c
*/

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "server_h.h"
#include "queue_h.h"
#include "logging_server.h"

static bool handle_errors_team_param(char **params, team_t *team,
    queue_t *request, fd_set *write_set)
{
    if (get_array_size(params) != 2 || strlen(params[0]) >= MAX_NAME_LENGTH ||
        strlen(params[1]) >= MAX_BODY_LENGTH) {
        write_invalid_code(request->fd_client, ERROR_ARGS, write_set);
        return true;
    }
    if (!team) {
        write_invalid_code(request->fd_client, "530", write_set);
        return true;
    }
    return false;
}

static bool is_existing_thread(mlist_t *thread_lst, char *name)
{
    threads_t *thread = NULL;

    for (mnode_t *node = thread_lst->head; node; node = node->next) {
        thread = (threads_t *)node;
        if (strcmp(thread->title, name) == 0)
            return true;
    }
    return false;
}

static bool handle_errors_channel(char **params, channels_t *channel,
    queue_t *request, fd_set *write_set)
{
    if (!channel) {
        write_invalid_code(request->fd_client, "540", write_set);
        return true;
    }
    if (is_existing_thread(channel->threads, params[0])) {
        write_invalid_code(request->fd_client, "543", write_set);
        return true;
    }
    return false;
}

static threads_t *add_thread(client_t *client, channels_t *channel,
    char **params)
{
    threads_t *thread = malloc(sizeof(threads_t) * 1);
    char uuid_creator[37] = {0};
    char uuid_thread[37] = {0};
    char uuid_channel[37] = {0};

    thread->discutions = ml_create_list();
    uuid_generate(thread->uuid);
    uuid_copy(thread->creator, client->uuid);
    strcpy(thread->body, params[1]);
    strcpy(thread->title, params[0]);
    thread->time_stamp = time(NULL);
    uuid_unparse(client->uuid, uuid_creator);
    uuid_unparse(channel->uuid, uuid_channel);
    uuid_unparse(thread->uuid, uuid_thread);
    server_event_thread_created(uuid_channel, uuid_thread, uuid_creator,
        thread->title, thread->body);
    ml_add_node_back(channel->threads, thread);
    return thread;
}

static void notify_thread_created(threads_t *thread, team_t *team,
    server_t *server, fd_set *write_set)
{
    reply_t reply = {0};

    strcpy(reply.code, "284");
    strcpy(reply.thread.title, thread->title);
    strcpy(reply.thread.body, thread->body);
    uuid_copy(reply.thread.creator, thread->creator);
    uuid_copy(reply.thread.uuid, thread->uuid);
    reply.thread.timestamp = thread->time_stamp;
    notify_team(server, team, &reply, write_set);
}

static void notify_user(threads_t *thread, queue_t *request)
{
    reply_t reply = {0};

    strcpy(reply.code, "241");
    strcpy(reply.thread.title, thread->title);
    strcpy(reply.thread.body, thread->body);
    uuid_copy(reply.thread.creator, thread->creator);
    uuid_copy(reply.thread.uuid, thread->uuid);
    reply.thread.timestamp = thread->time_stamp;
    write(request->fd_client, &reply, (sizeof(reply_t)));
}

void create_thread(char **params, server_t *server, queue_t *request,
    fd_set *write_set)
{
    client_t *client = get_client_by_fd(server, request->fd_client);
    team_t *team = get_team(server, client->context->uuid_team);
    channels_t *channel = get_channel_from_team(team,
        client->context->uuid_channel);
    threads_t *thread = NULL;

    if (handle_errors_team_param(params, team, request, write_set))
        return;
    if (!is_client_sub(client, team, request, write_set) ||
        handle_errors_channel(params, channel, request, write_set))
        return;
    thread = add_thread(client, channel, params);
    notify_user(thread, request);
    return notify_thread_created(thread, team, server, write_set);
}
