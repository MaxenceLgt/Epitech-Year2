/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** queue_handler
*/

#include <sys/select.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "server_h.h"
#include "queue_h.h"
#include "nc_clients_h.h"
#include "cmd_fptr.h"
#include "reply_h.h"
#include "define_h.h"

static const commands_t tab[] = {{"/login", true, &login},
    {"/logout", false, &logout}, {"/users", false, &cmd_users},
    {"/user", false, &cmd_user}, {"/send", false, &cmd_send},
    {"/messages", false, &cmd_message}, {"/subscribe", false, &subscribe},
    {"/subscribed", false, &subscribed}, {"/unsubscribe", false, &unsubscribe},
    {"/use", false, &cmd_use}, {"/create", false, &create},
    {"/list", false, &cmd_list}, {"/info", false, &cmd_infos}};

void temp(char **params, server_t *server, queue_t *request,
    fd_set *write_set)
{
    (void)params;
    (void)server;
    (void)request;
    (void)write_set;
    dprintf(1, "Je passe dans la fonction");
}

static void exec_request(server_t *server, queue_t *request, bool is_limited,
    fd_set *write_set)
{
    char **parsed_cmd = parse_cmd(request->command);
    int res_cmp = 0;

    if (parsed_cmd == NULL || !parsed_cmd[0])
        return write_invalid_code(request->fd_client, ERROR_ARGS, write_set);
    for (size_t i = 0; i < 13; i++) {
        res_cmp = strcmp(tab[i].command, parsed_cmd[0]);
        if (res_cmp == 0 && is_limited == tab[i].is_limited) {
            tab[i].fptr(&parsed_cmd[1], server, request, write_set);
            break;
        }
        if (res_cmp == 0) {
            write_invalid_priv(is_limited, request);
            break;
        }
        if (i == 12 && res_cmp != 0)
            write_invalid_code(request->fd_client, ERROR_COMMAND, write_set);
    }
    destroy_array(parsed_cmd);
}

static void parse_priv(server_t *server, queue_t *request, fd_set *write_set)
{
    nc_client_t *client_data;

    if (request->command[strlen(request->command) - 1] == '\n')
        memset(&request->command[strlen(request->command) - 1], 0, 1);
    for (mnode_t *nc_client = NC_CLIENTS; nc_client != NULL;
        nc_client = nc_client->next) {
        client_data = (nc_client_t *)nc_client->data;
        if (request->fd_client == client_data->client_fd)
            return exec_request(server, request, true, write_set);
    }
    return exec_request(server, request, false, write_set);
}

void handle_queue(server_t *server, fd_set *write_set)
{
    queue_t *request;
    mnode_t *queue_n = QUEUE;

    while (queue_n != NULL) {
        request = (queue_t *)queue_n->data;
        if (request->finish_cmd && FD_ISSET(request->fd_client, write_set)) {
            request->handle_time = time(NULL);
            parse_priv(server, request, write_set);
            ml_destroy_node(server->request_queue, queue_n, NULL);
            queue_n = QUEUE;
            save(server);
            continue;
        }
        queue_n = queue_n->next;
    }
}
