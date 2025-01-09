/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Ubuntu]
** File description:
** get_team
*/

#include <string.h>
#include <stdio.h>
#include "server_h.h"
#include "team_h.h"

team_t *get_team(server_t *server, uuid_t uuid)
{
    team_t *team = NULL;

    for (mnode_t *node = TEAM; node != NULL; node = node->next) {
        team = (team_t *)node->data;
        if (uuid_compare(uuid, team->uuid) == 0)
            return team;
    }
    dprintf(1, "Je n'ai pas trouvé de team\n");
    return NULL;
}
