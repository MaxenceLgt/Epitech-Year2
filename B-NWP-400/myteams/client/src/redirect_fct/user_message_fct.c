/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** user_message_fct
*/

#include "client_cli.h"
#include "logging_client.h"

int redirect_private_message_print_messages(reply_t *event_args)
{
    char str_uuid[37] = {0};

    uuid_unparse(event_args->message.creator, str_uuid);
    client_private_message_print_messages(str_uuid,
    event_args->message.timestamp,
    event_args->message.body);
    return 0;
}

int redirect_print_reply_created(reply_t *event_args)
{
    char str_uuid[37] = {0};
    char str_uuid2[37] = {0};

    uuid_unparse(event_args->user.user_uuid, str_uuid);
    uuid_unparse(event_args->message.creator, str_uuid2);
    client_print_reply_created(str_uuid, str_uuid2,
    event_args->message.timestamp, event_args->message.body);
    return 0;
}

int redirect_print_subscribed(reply_t *event_args)
{
    char str_uuid[37] = {0};
    char str_uuid2[37] = {0};

    uuid_unparse(event_args->user.user_uuid, str_uuid);
    uuid_unparse(event_args->team.uuid, str_uuid2);
    client_print_subscribed(str_uuid, str_uuid2);
    return 0;
}

int redirect_print_unsubscribed(reply_t *event_args)
{
    char str_uuid[37] = {0};
    char str_uuid2[37] = {0};

    uuid_unparse(event_args->user.user_uuid, str_uuid);
    uuid_unparse(event_args->team.uuid, str_uuid2);
    client_print_unsubscribed(str_uuid, str_uuid2);
    return 0;
}
