/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** connect_to_server
*/

#include "client_cli.h"

void print_rainbow_text(const char *text)
{
    const char *colors[] = {"\x1b[31m", "\x1b[33m",
    "\x1b[32m", "\x1b[36m", "\x1b[34m", "\x1b[35m"};
    size_t num_colors = sizeof(colors) / sizeof(colors[0]);

    for (size_t i = 0; i < strlen(text); ++i) {
        printf("%s%c", colors[i % num_colors], text[i]);
    }
    printf("\x1b[0m");
    fflush(stdout);
}

reply_t *connect_to_server(client_t *client)
{
    reply_t *reply = malloc(sizeof(reply_t));

    if (connect(client->fd, (struct sockaddr *)&client->addr,
        sizeof(client->addr)) < 0) {
        printf("\x1b[1;31mErreur lors de la connexion au serveur\x1b[0m");
        return NULL;
    }
    printf("\x1b[7m");
    print_rainbow_text("Connexion au serveur reussie\n");
    return reply;
}
