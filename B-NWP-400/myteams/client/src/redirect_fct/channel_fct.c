/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** channel_fct
*/

#include <stdio.h>
#include "client_cli.h"
#include "logging_client.h"

int redirect_channel_created(reply_t *event_args)
{
    char str_uuid[37] = {0};

    uuid_unparse(event_args->channel.uuid, str_uuid);
    client_event_channel_created(str_uuid, event_args->channel.title,
    event_args->channel.description);
    return 0;
}

int redirect_print_channel_created(reply_t *event_args)
{
    char str_uuid[37] = {0};

    uuid_unparse(event_args->channel.uuid, str_uuid);
    client_print_channel_created(str_uuid, event_args->channel.title,
    event_args->channel.description);
    return 0;
}

int redirect_print_channel(reply_t *event_args)
{
    char str_uuid[37] = {0};

    uuid_unparse(event_args->channel.uuid, str_uuid);
    client_print_channel(str_uuid, event_args->channel.title,
    event_args->channel.description);
    return 0;
}

int redirect_channels_print_threads(reply_t *event_args)
{
    char str_uuid[37] = {0};
    char str_uuid2[37] = {0};

    uuid_unparse(event_args->thread.uuid, str_uuid);
    uuid_unparse(event_args->thread.creator, str_uuid2);
    client_channel_print_threads(str_uuid, str_uuid2,
    event_args->thread.timestamp,
    event_args->thread.title, event_args->thread.body);
    return 0;
}
