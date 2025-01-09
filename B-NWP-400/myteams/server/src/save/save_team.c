/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Ubuntu]
** File description:
** save_team
*/

#include "server_h.h"
#include "team_h.h"
#include <stdio.h>
#include <stdlib.h>

int save_team(mlist_t *save_team)
{
    FILE* file = fopen("saves/team.txt", "w");
    team_t *team_data;
    char uuid_str[37];

    if (file == NULL) {
        return 1;
    }
    for (mnode_t *team = save_team->head; team != NULL;
        team = team->next) {
        team_data = (team_t *)team->data;
        uuid_unparse(team_data->uuid, uuid_str);
        fprintf(file, "%s;%s;%s\n", team_data->name, team_data->description
        , uuid_str);
    }
    fclose(file);
    return 0;
}
