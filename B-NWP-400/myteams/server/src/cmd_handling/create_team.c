/*
** EPITECH PROJECT, 2023
** my_teams [WSL: Ubuntu-22.04]
** File description:
** create_team_channel.c
*/

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "server_h.h"
#include "queue_h.h"
#include "logging_server.h"

static team_t *init_team(char *name, char *description)
{
    team_t *team = malloc(sizeof(team_t) * 1);

    team->channels = ml_create_list();
    team->clients = ml_create_list();
    uuid_generate(team->uuid);
    strcpy(team->name, name);
    strcpy(team->description, description);
    return team;
}

static void notify_team_created(team_t *team, server_t *server,
    queue_t *request, fd_set *write_set)
{
    reply_t reply = {0};

    strcpy(reply.code, "232");
    strcpy(reply.team.title, team->name);
    strcpy(reply.team.description, team->description);
    uuid_copy(reply.team.uuid, team->uuid);
    write(request->fd_client, &reply, sizeof(reply_t));
    strcpy(reply.code, "282");
    notify_all(server, &reply, write_set);
}

static bool is_existing_team(server_t *server, char *name)
{
    team_t *team = NULL;

    for (mnode_t *node = TEAM; node; node = node->next) {
        team = (team_t *)node;
        if (strcmp(team->name, name) == 0)
            return true;
    }
    return false;
}

void create_team(char **params, server_t *server, queue_t *request,
    fd_set *write_set)
{
    client_t *client = get_client_by_fd(server, request->fd_client);
    team_t *team = NULL;
    char uuid_team[37] = {0};
    char uuid_client[37] = {0};

    if (get_array_size(params) != 2 || strlen(params[0]) >= MAX_NAME_LENGTH ||
        strlen(params[1]) >= MAX_DESCRIPTION_LENGTH)
        return write_invalid_code(request->fd_client, ERROR_ARGS, write_set);
    if (is_existing_team(server, params[0]))
        return write_invalid_code(request->fd_client, "532", write_set);
    team = init_team(params[0], params[1]);
    uuid_unparse(team->uuid, uuid_team);
    uuid_unparse(client->uuid, uuid_client);
    ml_add_node_back(server->team_list, team);
    server_event_team_created(uuid_team, team->name, uuid_client);
    return notify_team_created(team, server, request, write_set);
}
