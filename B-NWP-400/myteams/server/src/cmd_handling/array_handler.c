/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** array_handler
*/

#include <sys/types.h>
#include <stdlib.h>

void destroy_array(char **array)
{
    for (size_t i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}

size_t get_array_size(char **array)
{
    size_t size = 0;

    if (!array)
        return size;
    for (; array[size] != NULL; size++);
    return size;
}
