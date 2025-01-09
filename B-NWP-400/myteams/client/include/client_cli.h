/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** client_cli
*/

#ifndef CLIENT_CLI
    #define CLIENT_CLI

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <arpa/inet.h>
    #include <uuid/uuid.h>
    #include <time.h>
    #include <stdbool.h>
    #include <sys/select.h>

    #define BUFFER_SIZE 1024

typedef struct server_data_s {
    char *ip;
    int port;
} server_data_t;

typedef struct user_s {
    uuid_t user_uuid;
    bool user_status;
    char user_name[33];
} user_t;

typedef struct scope_s {
    uuid_t uuid;
    uuid_t creator;
    time_t timestamp;
    char title[33];
    char description[256];
    char body[512];
} scope_t;

typedef struct reply_s {
    char code[4];
    user_t user;
    scope_t team;
    scope_t channel;
    scope_t thread;
    scope_t message;
} reply_t;

typedef struct client_s {
    int fd;
    struct sockaddr_in addr;
    server_data_t *server_data;
    fd_set write_fd;
    fd_set read_fds;
    int fdmax;
} client_t;


typedef struct command_s {
    char code[4];
    int (*func)(reply_t *event_args);
} command_t;

client_t *set_client(int ac, char **av);
int error_handling(int ac, char **av);
reply_t *connect_to_server(client_t *client);
void client_loop(client_t *client, reply_t *server_response);
//int search_sender_id(reply_t *args);
int client_help(reply_t *event_args);
int command_handling(reply_t *server_response);

//------------------------------- Redirects -----------------------------------
int redirect_login(reply_t *event_args);
int redirect_logout(reply_t *event_args);
int redirect_pv_msg_rcv(reply_t *event_args);
int redirect_thread_msg_rcv(reply_t *event_args);
int redirect_team_created(reply_t *event_args);
int redirect_channel_created(reply_t *event_args);
int redirect_thread_created(reply_t *event_args);
int redirect_print_users(reply_t *event_args);
int redirect_print_user(reply_t *event_args);
int redirect_print_team(reply_t *event_args);
int redirect_print_channel(reply_t *event_args);
int redirect_teams_print_channels(reply_t *event_args);
int redirect_channels_print_threads(reply_t *event_args);
int redirect_threads_print_replies(reply_t *event_args);
int redirect_private_message_print_messages(reply_t *event_args);
int redirect_error_unknown_team(reply_t *event_args);
int redirect_error_unknown_channel(reply_t *event_args);
int redirect_error_unknown_thread(reply_t *event_args);
int redirect_error_unknown_user(reply_t *event_args);
int redirect_error_unauthorized(reply_t *event_args);
int redirect_error_already_exist(reply_t *event_args);
int redirect_print_thread(reply_t *event_args);
int redirect_print_team_created(reply_t *event_args);
int redirect_print_channel_created(reply_t *event_args);
int redirect_print_thread_created(reply_t *event_args);
int redirect_print_reply_created(reply_t *event_args);
int redirect_print_subscribed(reply_t *event_args);
int redirect_print_unsubscribed(reply_t *event_args);
int redirect_list(reply_t *event_args);
int redirect_info(reply_t *event_args);
int redirect_context(reply_t *event_args);
int redirect_reply_created(reply_t *event_args);
int redirect_already_created(reply_t *event_args);

#endif //CLIENT_CLI
