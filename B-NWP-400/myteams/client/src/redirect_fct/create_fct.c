/*
** EPITECH PROJECT, 2023
** my_teams [WSL: Ubuntu-22.04]
** File description:
** subscribe_fct.c
*/

#include <stdio.h>
#include "client_cli.h"
#include "logging_client.h"

int redirect_already_created(reply_t *event_args)
{
    (void)event_args;
    client_error_already_exist();
    return 0;
}
