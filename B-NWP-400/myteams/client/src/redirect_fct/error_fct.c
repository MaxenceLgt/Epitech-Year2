/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** error_ftc
*/

#include "client_cli.h"
#include "logging_client.h"

int redirect_error_already_exist(reply_t *event_args)
{
    (void)event_args;
    client_error_already_exist();
    return 0;
}

int redirect_error_unauthorized(reply_t *event_args)
{
    (void)event_args;
    client_error_unauthorized();
    return 0;
}
