/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Ubuntu]
** File description:
** save_client_team
*/

#include "server_h.h"
#include "team_h.h"
#include "client_h.h"
#include <stdio.h>
#include <stdlib.h>

int save_client_team2(FILE *file, team_t *team_data)
{
    client_t *client_data;
    char uuid_str[37];

    if (team_data->clients->head == NULL) {
        return 0;
    }
    for (mnode_t *temp_client = team_data->clients->head;
        temp_client != NULL; temp_client = temp_client->next) {
        client_data = (client_t *)temp_client->data;
        uuid_unparse_lower(team_data->uuid, uuid_str);
        fprintf(file, "%s;", uuid_str);
        uuid_unparse_lower(client_data->uuid, uuid_str);
        fprintf(file, "%s\n", uuid_str);
    }
    return 0;
}

int save_client_team(mlist_t *save_team)
{
    FILE *file = fopen("saves/client_team.txt", "w");
    team_t *team_data;

    if (file == NULL)
        return 1;
    if (save_team == NULL) {
        fclose(file);
        return 0;
    }
    for (mnode_t *team = save_team->head; team != NULL;
        team = team->next) {
        team_data = (team_t *)team->data;
        if (save_client_team2(file, team_data) == 1)
            return 1;
    }
    fclose(file);
    return 0;
}
