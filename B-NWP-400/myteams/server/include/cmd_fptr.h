/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** cmd_fptr
*/

#ifndef CMD_FPTR_H_
    #define CMD_FPTR_H_

    #include <stdbool.h>

typedef struct commands_s {
    char *command;
    bool is_limited;
    void (*fptr)();
} commands_t;

#endif /* !CMD_FPTR_H_ */
