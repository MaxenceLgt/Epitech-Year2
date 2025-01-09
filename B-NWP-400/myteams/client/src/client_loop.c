/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** client_loop
*/

#include "client_cli.h"

static const command_t commmand[] = {
    {"200", &redirect_login},
    {"201", &redirect_logout},
    {"210", &client_help},
    {"211", &redirect_info},
    {"212", &redirect_list},
    {"213", &redirect_print_user},
    {"214", &redirect_print_users},
    {"215", &redirect_print_team},
    {"216", &redirect_print_users},
    {"217", &redirect_private_message_print_messages},
    {"220", &redirect_context},
    {"230", &redirect_print_subscribed},
    {"231", &redirect_print_unsubscribed},
    {"232", &redirect_print_team_created},
    {"234", &redirect_teams_print_channels},
    {"235", &redirect_print_team},
    {"240", &redirect_channel_created},
    {"241", &redirect_thread_created},
    {"242", &redirect_reply_created},
    {"244", &redirect_channels_print_threads},
    {"245", &redirect_threads_print_replies},
    {"247", &redirect_print_channel},
    {"248", &redirect_print_thread},
    {"280", &redirect_pv_msg_rcv},
    {"281", &redirect_thread_msg_rcv},
    {"282", &redirect_print_team_created},
    {"283", &redirect_channel_created},
    {"284", &redirect_thread_created},
    {"500", &redirect_error_unauthorized},
    {"525", &redirect_error_unknown_user},
    {"530", &redirect_error_unknown_team},
    {"531", &redirect_error_unauthorized},
    {"532", &redirect_already_created},
    {"533", &redirect_error_unauthorized},
    {"540", &redirect_error_unknown_channel},
    {"541", &redirect_error_unknown_thread},
    {"543", &redirect_already_created},
    {"544", &redirect_already_created},
    {"594", &redirect_error_unauthorized}
};

int command_handling(reply_t *server_response)
{
    for (int i = 0; i <= 32; i++) {
        if (strcmp(commmand[i].code, server_response->code) == 0) {
            commmand[i].func(server_response);
            return 0;
        }
    }
    return 84;
}

static int is_help_function(char *buffer)
{
    if (strcmp(buffer, "/help\n") == 0) {
        client_help(NULL);
        return 1;
    }
    return 0;
}

static void receive_data_from_server(client_t *client,
    reply_t *server_response)
{
    if (read(client->fd, server_response, sizeof(reply_t)) == -1) {
        printf("\x1b[1;31mErreur réception de la réponse\x1b[0m");
        exit(0);
    }
    if (strcmp(server_response->code, "666") == 0) {
        printf("\033[31;6mServer shutting down ...\033[0m\n");
        exit(0);
    }
    dprintf(1, "Code received : %s\n", server_response->code);
    if (command_handling(server_response) == 84)
        printf("\x1b[1;31mCommand not found\x1b[0m\n");
}

static void send_data_to_server(char *buffer, client_t *client)
{
    read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
    if (is_help_function(buffer) == 1)
        return;
    if (FD_ISSET(client->fd, &client->write_fd)) {
        if (write(client->fd, buffer, 1024) != -1)
            printf("\x1b[1;32mCommande envoyée.\x1b[0m\n");
        else
            printf("\x1b[1;31mErreur lors de l'envoi de la commande\x1b[0m");
    }
    memset(buffer, 0, sizeof(char) * BUFFER_SIZE);
}

static void instantiate_fd(client_t *client)
{
    FD_ZERO(&client->read_fds);
    FD_ZERO(&client->write_fd);
    FD_SET(client->fd, &client->read_fds);
    FD_SET(client->fd, &client->write_fd);
    FD_SET(STDIN_FILENO, &client->read_fds);
    FD_SET(STDIN_FILENO, &client->write_fd);
}

void client_loop(client_t *client, reply_t *server_response)
{
    char buffer[BUFFER_SIZE];

    memset(buffer, 0, sizeof(char) * BUFFER_SIZE);
    while (true) {
        instantiate_fd(client);
        if (select(FD_SETSIZE, &client->read_fds, &client->write_fd,
            NULL, NULL) == -1) {
            printf("Select :");
            exit(84);
        }
        if (FD_ISSET(STDIN_FILENO, &client->read_fds))
            send_data_to_server(buffer, client);
        if (FD_ISSET(client->fd, &client->read_fds))
            receive_data_from_server(client, server_response);
    }
}
