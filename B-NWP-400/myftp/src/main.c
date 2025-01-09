/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** main.c
*/

#include "error_handling.h"
#include "commands.h"
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/select.h>

void exec_server_loop(server_s *server)
{
    fd_set readSet;
    fd_set writeSet;

    while (true) {
        instantiate_fd_sets(&readSet, &writeSet, server);
        if (select(FD_SETSIZE, &readSet, &writeSet, NULL, NULL) == -1)
            exit_as_error("Error : select return -1", server);
        if (FD_ISSET(server->serverFd, &readSet) && server->clientList->size <
            server->clientList->maxSize)
                handle_new_connection(server);
        check_connection_code(server, &writeSet);
        handle_commands(server, &readSet, &writeSet);
    }
}

int main(int ac, char **av)
{
    server_s *server = malloc(sizeof(server_s) * 1);
    struct sockaddr_in serverAddr;
    client_l *clientList;
    int fdServer;

    srand(time(NULL));
    handle_argument_errors(ac, av, server);
    fdServer = setup_server(&serverAddr, av[1]);
    clientList = setup_client_list();
    server->clientList = clientList;
    server->serverFd = fdServer;
    server->serverAddr = &serverAddr;
    server->lenAddr = sizeof(struct sockaddr_in);
    exec_server_loop(server);
    close(fdServer);
    return 0;
}
