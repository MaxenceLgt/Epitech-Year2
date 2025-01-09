/*
** EPITECH PROJECT, 2023
** my_teams [WSL: Ubuntu-22.04]
** File description:
** info_fct.c
*/

#include <stdio.h>
#include "client_cli.h"
#include "logging_client.h"

int redirect_info(reply_t *event_args)
{
    char str_uuid[37] = {0};

    uuid_unparse(event_args->user.user_uuid, str_uuid);
    client_print_user(str_uuid, event_args->user.user_name,
        (int)event_args->user.user_status);
    return 0;
}

int redirect_list(reply_t *event_args)
{
    char str_uuid[37] = {0};

    uuid_unparse(event_args->team.uuid, str_uuid);
    client_print_teams(str_uuid, event_args->team.title,
        event_args->team.description);
    return 0;
}

int redirect_context(reply_t *event_args)
{
    (void)event_args;
    dprintf(1, "Context succesfully set\n");
    return 0;
}

int redirect_reply_created(reply_t *event_args)
{
    char thread_uuid[37] = {0};
    char user_uuid[37] = {0};

    uuid_unparse(event_args->message.creator, user_uuid);
    uuid_unparse(event_args->thread.uuid, thread_uuid);
    client_print_reply_created(thread_uuid, user_uuid,
        event_args->message.timestamp, event_args->message.body);
    return 0;
}
