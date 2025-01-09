/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Ubuntu]
** File description:
** save
*/

#include <stdio.h>
#include <stdlib.h>
#include "server_h.h"

int save(server_t *server)
{
    save_client(server->client_list);
    save_client_conv(server->client_list);
    save_client_message(server->client_list);
    save_team(server->team_list);
    save_client_team(server->team_list);
    save_channel(server->team_list);
    save_thread(server->team_list);
    save_team_message(server->team_list);
    return 0;
}
