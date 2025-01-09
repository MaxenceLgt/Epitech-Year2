/*
** EPITECH PROJECT, 2024
** Untitled (Workspace)
** File description:
** server_h
*/

#ifndef SERVER_H_H_
    #define SERVER_H_H_

    #include <netinet/in.h>
    #include <sys/select.h>
    #include "queue_h.h"
    #include "threads_h.h"
    #include "channels_h.h"
    #include "team_h.h"
    #include "ml_list_head.h"
    #include "client_h.h"
    #include "reply_h.h"

    #define NC_CLIENTS server->client_not_connected->head
    #define CLIENTS server->client_list->head
    #define TEAM server->team_list->head
    #define QUEUE server->request_queue->head
    #define LIST_REPLY !uuid_is_null(client_data->context->uuid_team)
    #define LIST_REPLY2 !uuid_is_null(client_data->context->uuid_channel)
    #define LIST_REPLY3 !uuid_is_null(client_data->context->uuid_thread)
    #define LIST_THREAD !uuid_is_null(client_data->context->uuid_team)
    #define LIST_THREAD2 !uuid_is_null(client_data->context->uuid_channel)
    #define LIST_CHANNEL !uuid_is_null(client_data->context->uuid_team)

typedef struct server_s {
    int server_fd;
    int server_users;
    struct sockaddr_in *server_addr;
    socklen_t len_addr;
    mlist_t *client_not_connected;
    mlist_t *client_list;
    mlist_t *team_list;
    mlist_t *request_queue;
} server_t;

/**
 * @brief Init full teams server with port parameter
 * @param port port of the server
 * @return NULL if initiation fail, server_t otherwise
*/
server_t *init_server(char *port);

/**
 * @brief This functions destroy server content and free server to
 * return NULL server
 * @param server server to destroy
 * @return NULL pointer
*/
server_t *destroy_server(server_t *server);

void destroy_nc_client(void *data);

void destroy_queue_node(void *data);

void destroy_client_node(void *data);

/**
 * @brief This function saves given list inside file given as param
 * @param struct_list List to save
 * @param path Path to file to save list into
 * @return 0 on succes, 1 on error
*/
int save(server_t *server);

/**
 * @brief This function loads the content of the file in the given list
 * @param list_to_load list that will contain file content
 * @param path path to file to be loaded
 * @return 0 on success, 1 otherwise
*/
int load(server_t *server);

int save_client(mlist_t *save_client);
int load_client(mlist_t *save_client);
char **my_str_tok(char const *str, char const *token);
void destroy_array(char **array);
size_t get_array_size(char **array);
char *remove_padding(char *str);
int save_client_conv(mlist_t *save_client);
int load_client_conv(mlist_t *save_client);
int save_client_message(mlist_t *save_client);
int load_client_message(mlist_t *save_client);
int save_team(mlist_t *save_team);
int load_team(mlist_t *save_team);
int save_client_team(mlist_t *save_team);
int load_client_team(mlist_t *save_team);
int save_channel(mlist_t *save_team);
int load_channel(mlist_t *save_team);
time_t convert_string_to_time_t(const char *date_string);
char *convert_time_t_to_string(time_t time);
int save_thread(mlist_t *save_team);
int load_thread(mlist_t *save_team);
int save_team_message(mlist_t *save_team);
int load_team_message(mlist_t *save_team);
void create_user(reply_t *new_reply, client_t *client_data);
void cmd_message(char **cmd, server_t *server, queue_t *queue,
    fd_set *write_set);
void cmd_send(char **cmd, server_t *server, queue_t *queue,
    fd_set *write_set);
void cmd_user(char **cmd, server_t *server, queue_t *queue,
    fd_set *write_set);
void cmd_users(char **cmd, server_t *server, queue_t *queue,
    fd_set *write_set);
void cmd_use(char **cmd, server_t *server, queue_t *queue,
    fd_set *write_set);
void cmd_infos(char **cmd, server_t *server, queue_t *queue,
    fd_set *write_set);
void cmd_list(char **params, server_t *server, queue_t *request,
    fd_set *write_set);
client_t *get_client_by_uuid(server_t *server, uuid_t uuid);
conv_t *get_conv(server_t *server, uuid_t uuid0, uuid_t uuid1);
/**
 * @brief This function is server loop to be constant running
 * @param server structure containing all server informations
 * @return 0
*/
int server_loop(server_t *server);

/**
 * @brief This function handle new connections inside server
 * @param server structure containing list of connected user to be filled
 * @return Nothing
*/
void handle_connection(server_t *server);

void handle_cmd(server_t *server, fd_set *read_set, fd_set *write_set);

void handle_queue(server_t *server, fd_set *write_set);

void temp(char **params, server_t *server, queue_t *request,
    fd_set *write_set);
void subscribed(char **params, server_t *server, queue_t *request,
    fd_set *write_set);
void login(char **cmd, server_t *server, queue_t *request, fd_set *write_set);
void logout(char **cmd, server_t *server, queue_t *request,
    fd_set *write_set);
void subscribe(char **params, server_t *server, queue_t *request,
    fd_set *write_set);
void unsubscribe(char **params, server_t *server, queue_t *request,
    fd_set *write_set);
void create(char **params, server_t *server, queue_t *request,
    fd_set *write_set);
void create_team(char **params, server_t *server, queue_t *request,
    fd_set *write_set);
void create_channel(char **params, server_t *server, queue_t *request,
    fd_set *write_set);
void create_thread(char **params, server_t *server, queue_t *request,
    fd_set *write_set);
void create_reply(char **params, server_t *server, queue_t *request,
    fd_set *write_set);
void notify_all(server_t *server, reply_t *reply, fd_set *write_set);
void notify_team(server_t *server, team_t *team, reply_t *reply,
    fd_set *write_set);
bool is_client_sub(client_t *client, team_t *team, queue_t *request,
    fd_set *write_set);

bool client_is_already_sub(team_t *team, client_t *client);

/* GETTERS */

client_t *get_client_by_fd(server_t *server, int fd);
client_t *get_client_by_username(server_t *server, char *username);
team_t *get_team(server_t *server, uuid_t uuid);
threads_t *get_threads(server_t *server, uuid_t uuid);
channels_t *get_channel(server_t *server, uuid_t uuid);
client_t *get_client_by_uuid(server_t *server, uuid_t uuid);
channels_t *get_channel_from_team(team_t *team, uuid_t uuid);
threads_t *get_thread_from_channel(channels_t *channel, uuid_t uuid);

/*
return create_reply(params, server, request, write_set);
//return create_thread(params, server, request, write_set);
*/

#endif /* !SERVER_H_H_ */
