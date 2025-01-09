/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** teams_fct
*/

#include <stdio.h>
#include "client_cli.h"
#include "logging_client.h"

int redirect_team_created(reply_t *event_args)
{
    char str_uuid[37] = {0};

    uuid_unparse(event_args->team.uuid, str_uuid);
    client_print_team_created(str_uuid, event_args->team.title,
    event_args->team.description);
    return 0;
}

int redirect_print_team(reply_t *event_args)
{
    char str_uuid[37] = {0};

    uuid_unparse(event_args->team.uuid, str_uuid);
    client_print_team(str_uuid, event_args->team.title,
    event_args->team.description);
    return 0;
}

int redirect_teams_print_channels(reply_t *event_args)
{
    char str_uuid[37] = {0};

    uuid_unparse(event_args->channel.uuid, str_uuid);
    client_team_print_channels(str_uuid, event_args->channel.title,
        event_args->channel.description);
    return 0;
}

int redirect_print_team_created(reply_t *event_args)
{
    char str_uuid[37] = {0};

    uuid_unparse(event_args->team.uuid, str_uuid);
    client_event_team_created(str_uuid, event_args->team.title,
    event_args->team.description);
    return 0;
}
