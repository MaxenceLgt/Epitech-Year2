/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** user_fct
*/

#include "client_cli.h"
#include "logging_client.h"

int redirect_login(reply_t *event_args)
{
    char str_uuid[37] = {0};

    uuid_unparse(event_args->user.user_uuid, str_uuid);
    client_event_logged_in(str_uuid, event_args->user.user_name);
    return 0;
}

int redirect_logout(reply_t *event_args)
{
    char str_uuid[37] = {0};

    uuid_unparse(event_args->user.user_uuid, str_uuid);
    client_event_logged_out(str_uuid, event_args->user.user_name);
    return 0;
}

int redirect_pv_msg_rcv(reply_t *event_args)
{
    char str_uuid[37] = {0};

    uuid_unparse(event_args->message.creator, str_uuid);
    client_event_private_message_received(str_uuid,
    event_args->message.body);
    return 0;
}

int redirect_print_users(reply_t *event_args)
{
    char str_uuid[37] = {0};

    uuid_unparse(event_args->user.user_uuid, str_uuid);
    client_print_users(str_uuid, event_args->user.user_name,
        event_args->user.user_status);
    return 0;
}

int redirect_print_user(reply_t *event_args)
{
    char str_uuid[37] = {0};

    uuid_unparse(event_args->user.user_uuid, str_uuid);
    client_print_user(str_uuid, event_args->user.user_name,
    event_args->user.user_status);
    return 0;
}
