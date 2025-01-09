/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Ubuntu]
** File description:
** load
*/

#include <stdio.h>
#include <stdlib.h>
#include "server_h.h"

int load(server_t *server)
{
    load_client(server->client_list);
    load_client_conv(server->client_list);
    load_client_message(server->client_list);
    load_team(server->team_list);
    load_client_team(server->team_list);
    load_channel(server->team_list);
    load_thread(server->team_list);
    load_team_message(server->team_list);
    return 0;
}
