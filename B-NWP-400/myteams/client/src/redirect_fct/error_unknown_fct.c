/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** error_unknown_fct
*/

#include "client_cli.h"
#include "logging_client.h"

int redirect_error_unknown_team(reply_t *event_args)
{
    char str_uuid[37] = {0};

    uuid_unparse(event_args->team.uuid, str_uuid);
    client_error_unknown_team(str_uuid);
    return 0;
}

int redirect_error_unknown_channel(reply_t *event_args)
{
    char str_uuid[37] = {0};

    uuid_unparse(event_args->channel.uuid, str_uuid);
    client_error_unknown_channel(str_uuid);
    return 0;
}

int redirect_error_unknown_thread(reply_t *event_args)
{
    char str_uuid[37] = {0};

    uuid_unparse(event_args->thread.uuid, str_uuid);
    client_error_unknown_thread(str_uuid);
    return 0;
}

int redirect_error_unknown_user(reply_t *event_args)
{
    char str_uuid[37] = {0};

    uuid_unparse(event_args->user.user_uuid, str_uuid);
    client_error_unknown_user(str_uuid);
    return 0;
}
