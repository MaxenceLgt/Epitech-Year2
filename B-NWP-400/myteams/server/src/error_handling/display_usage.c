/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** display_usage
*/

#include <stdio.h>

int display_usage(int return_result)
{
    printf("USAGE: ./myteams_server port\n\n\t");
    printf("port is the port number on which the server socket listens.\n");
    return return_result;
}
