/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** thread_fct
*/

#include "client_cli.h"
#include "logging_client.h"

int redirect_thread_msg_rcv(reply_t *event_args)
{
    char str_uuid[37] = {0};
    char str_uuid2[37] = {0};
    char str_uuid3[37] = {0};

    uuid_unparse(event_args->team.uuid, str_uuid);
    uuid_unparse(event_args->thread.uuid, str_uuid2);
    uuid_unparse(event_args->message.creator, str_uuid3);
    client_event_thread_reply_received(str_uuid, str_uuid2,
    str_uuid2, event_args->message.body);
    return 0;
}

int redirect_thread_created(reply_t *event_args)
{
    char str_uuid[37] = {0};
    char str_uuid2[37] = {0};

    uuid_unparse(event_args->thread.uuid, str_uuid);
    uuid_unparse(event_args->thread.creator, str_uuid2);
    client_event_thread_created(str_uuid, str_uuid2,
    event_args->thread.timestamp, event_args->thread.title,
    event_args->thread.body);
    return 0;
}

int redirect_threads_print_replies(reply_t *event_args)
{
    char str_uuid[37] = {0};
    char str_uuid2[37] = {0};

    uuid_unparse(event_args->thread.uuid, str_uuid);
    uuid_unparse(event_args->message.creator, str_uuid2);
    client_thread_print_replies(str_uuid, str_uuid2,
    event_args->message.timestamp,
    event_args->message.body);
    return 0;
}

int redirect_print_thread(reply_t *event_args)
{
    char str_uuid[37] = {0};
    char str_uuid2[37] = {0};

    uuid_unparse(event_args->thread.uuid, str_uuid);
    uuid_unparse(event_args->thread.creator, str_uuid2);
    client_print_thread(str_uuid, str_uuid2,
    event_args->thread.timestamp, event_args->thread.title,
    event_args->thread.body);
    return 0;
}

int redirect_print_thread_created(reply_t *event_args)
{
    char str_uuid[37] = {0};
    char str_uuid2[37] = {0};

    uuid_unparse(event_args->thread.uuid, str_uuid);
    uuid_unparse(event_args->thread.creator, str_uuid2);
    client_print_thread_created(str_uuid, str_uuid2,
    event_args->thread.timestamp, event_args->thread.title,
    event_args->thread.body);
    return 0;
}
