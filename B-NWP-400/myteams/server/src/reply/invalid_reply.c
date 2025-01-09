/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** invalid_reply
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "reply_h.h"
#include "queue_h.h"
#include "define_h.h"

void write_invalid_priv(bool is_limited, queue_t *request)
{
    reply_t reply = {0};

    if (is_limited)
        strcpy(reply.code, NOT_LOGGED);
    else
        strcpy(reply.code, ALREADY_LOGGED);
    write(request->fd_client, &reply, sizeof(reply_t));
}

void write_invalid_code(int client_fd, char *code, fd_set *write_set)
{
    reply_t reply = {0};

    strcpy(reply.code, code);
    if (FD_ISSET(client_fd, write_set))
        write(client_fd, &reply, sizeof(reply_t));
}
