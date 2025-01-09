/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** error_handling.h
*/

#ifndef ERROR_HANDLING_H
    #define ERROR_HANDLING_H

    #include "server.h"

void handle_argument_errors(int ac, char **av, server_s *server);
void exit_as_error(char *errorMessage, server_s *clientList);

#endif /* ERROR_HANDLING_H */
