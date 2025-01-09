/*
** EPITECH PROJECT, 2024
** my_teams [WSL: Ubuntu]
** File description:
** load_team
*/

#include "server_h.h"
#include "team_h.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void add_team(mlist_t *save_team, char *line)
{
    team_t *new_team = malloc(sizeof(team_t));
    char **token = my_str_tok(line, ";");

    strcpy(new_team->name, token[0]);
    strcpy(new_team->name, token[1]);
    uuid_parse(token[2], new_team->uuid);
    new_team->channels = ml_create_list();
    new_team->clients = ml_create_list();
    ml_add_node_back(save_team, new_team);
    return;
}

int load_team(mlist_t *save_team)
{
    FILE *file = fopen("saves/team.txt", "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    if (file == NULL)
        return 1;
    read = getline(&line, &len, file);
    while (read != -1) {
        if (line[read - 1] == '\n') {
            line[read - 1] = '\0';
        }
        add_team(save_team, line);
        read = getline(&line, &len, file);
    }
    free(line);
    fclose(file);
    return 0;
}
