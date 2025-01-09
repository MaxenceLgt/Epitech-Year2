/*
** EPITECH PROJECT, 2024
** command_spliter
** File description:
** command_spliter
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static bool check_char_in_lst(const char c, const char *lst)
{
    for (size_t i = 0; lst[i] != '\0'; i++)
        if (lst[i] == c)
            return (true);
    return (false);
}

static size_t count_words(char const *str, char const *token)
{
    size_t nb_words = 0;

    if (!str)
        return (0);
    for (size_t i = 0; str[i] != '\0'; i++)
        if (!check_char_in_lst(str[i], token) &&
        (str[i + 1] == '\0' || check_char_in_lst(str[i + 1], token)))
            nb_words++;
    return (nb_words);
}

static size_t get_size_word(char const *str, char const *token)
{
    size_t count = 0;

    while (!check_char_in_lst(str[count], token) &&
    str[count] != '\0')
        count++;
    return (count);
}

char **split_command(char const *str, char const *token)
{
    size_t nb_word = count_words(str, token);
    char **word_arr = malloc(sizeof(char *) * (nb_word + 1));
    size_t size_str = strlen(str);
    size_t size_w = 0;
    size_t pos_arr = 0;

    if (!word_arr)
        return (NULL);
    for (size_t i = 0; i < size_str; i++){
        if (check_char_in_lst(str[i], token))
            continue;
        size_w = get_size_word(&str[i], token);
        word_arr[pos_arr] = strndup(&str[i], size_w);
        i += size_w;
        pos_arr++;
    }
    word_arr[pos_arr] = NULL;
    return (word_arr);
}
