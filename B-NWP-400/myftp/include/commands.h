/*
** EPITECH PROJECT, 2024
** COMMANDS_H_
** File description:
** COMMAND_H_
*/

#ifndef COMMAND_H_
    #define COMMAND_H_

    #define UNUSED __attribute__((unused))
    #define SUCC_150 "150 File status okay, about to open data connection.\n"
    #define ERR_425 "425 Can't open data connection.\n"
    #define SUCC_226 "226 Closing data connection.\n"
    #include <stdio.h>
    #include "server.h"

typedef struct f_pointer_struct {
    char *command;
    void (*fptr)();
} f_pointer;

char **split_command(char const *str, char const *token);
size_t get_len_tab(char **tab);
void handle_commands(server_s *server, fd_set *readSet, fd_set *writeSet);
void write_invalid_command(client_s *client);
void user_not_logged(client_s *client);
void error_in_arguments(client_s *client);
void reset_client_command(client_s *client);
char *get_folder_path(char *fpath, client_s *client);
char *get_file_path(char *fpath, client_s *client);
char *get_file_folder(char *fpath, client_s *client);
void handle_user(client_s *client, UNUSED server_s *server, char **args);
void handle_pass(client_s *client, UNUSED server_s *server, char **args);
void handle_quit(client_s *client, UNUSED server_s *server, char **args);
void handle_noop(client_s *client, UNUSED server_s *server, char **args);
void handle_help(client_s *client, UNUSED server_s *server, char **args);
void handle_delete(client_s *client, UNUSED server_s *server, char **args);
void handle_cwd(client_s *client, UNUSED server_s *server, char **args);
void handle_pwd(client_s *client, UNUSED server_s *server, char **args);
void handle_cdup(client_s *client, UNUSED server_s *server, char **args);
void handle_port(client_s *client, UNUSED server_s *server, char **args);
void handle_pasv(client_s *client, server_s *server, char **args);
void handle_list(client_s *client, server_s *server, char **args);
void handle_retrieve(client_s *client, server_s *server, char **args);
void handle_stor(client_s *client, server_s *server, char **args);
void handle_actv_cmd(client_s *client, server_s *server, void (*fptr)(),
    char *fpath);
void handle_pasv_cmd(client_s *client, server_s *server, void (*fptr)(),
    char *fpath);

#endif /* !COMMAND_H_ */
