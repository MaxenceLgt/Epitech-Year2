/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** padding_remover
*/

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static bool is_padding(char c)
{
    if (c == '\t' || c == ' ' || c == '\n')
        return true;
    return false;
}

static size_t get_padding_size(char *str)
{
    size_t size_padding = 0;

    if (!str)
        return size_padding;
    for (size_t i = 0; str[i] != '\0'; i++)
        if (is_padding(str[i]))
            size_padding++;
    return size_padding;
}

char *remove_padding(char *str)
{
    size_t padding = get_padding_size(str);
    char *result = NULL;
    size_t pos = 0;

    if (!str)
        return NULL;
    result = calloc(sizeof(char), strlen(str) - padding + 1);
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (is_padding(str[i]))
            continue;
        result[pos] = str[i];
        pos++;
    }
    return result;
}
