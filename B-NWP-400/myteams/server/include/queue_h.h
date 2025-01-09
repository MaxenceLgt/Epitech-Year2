/*
** EPITECH PROJECT, 2023
** my_teams [WSL: Ubuntu-22.04]
** File description:
** queue_h.h
*/

#ifndef QUEUE_H
    #define QUEUE_H

    #include <time.h>
    #include <stdbool.h>
    #include <sys/select.h>

typedef struct queue_s {
    char command[1024];
    bool finish_cmd;
    int cmd_index;
    int fd_client;
    time_t handle_time;
} queue_t;

char **parse_cmd(char *command);
void write_invalid_code(int client_fd, char *code, fd_set *write_set);
void write_invalid_priv(bool is_limited, queue_t *request);

#endif /* QUEUE_H */
