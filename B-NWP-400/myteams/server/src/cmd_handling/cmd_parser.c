/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** cmd_parser
*/

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server_h.h"
#include "parser_h.h"

static int get_quoted_params(char *command)
{
    size_t nb_quote = 0;

    for (size_t i = 0; command[i] != '\0'; i++)
        if (command[i] == '"')
            nb_quote++;
    if (nb_quote % 2 != 0)
        return -1;
    return (int)nb_quote / 2;
}

static char *get_quoted_arg(char *arg, int *pos)
{
    size_t dup_size = 0;
    char *result;

    for (size_t i = 0; arg[i] != '"'; i++) {
        dup_size++;
        (*pos)++;
    }
    if (dup_size == 0)
        return strdup("");
    result = strndup(arg, dup_size);
    return result;
}

static char *get_arg(char *arg, int *pos)
{
    size_t dup_size = 0;
    char *result;

    for (size_t i = 0; arg[i] != '"' && arg[i] != '\0'; i++) {
        dup_size++;
        (*pos)++;
    }
    if (dup_size == 0)
        return NULL;
    (*pos)--;
    result = strndup(arg, dup_size);
    return result;
}

static void add_splitted(char **splitted, parser_t *parser)
{
    for (size_t i = 0; splitted[i] != NULL; i++)
        parser_add_node_back(parser, splitted[i], true);
}

static void fill_parser(char *command, parser_t *parser)
{
    char *temp;
    char **splited;

    for (int i = 0; command[i] != '\0'; i++) {
        if (command[i] == '"') {
            i++;
            temp = get_quoted_arg(&command[i], &i);
            parser_add_node_back(parser, temp, false);
            free(temp);
            continue;
        }
        temp = get_arg(&command[i], &i);
        splited = my_str_tok(temp, "\n\t ");
        add_splitted(splited, parser);
        destroy_array(splited);
        free(temp);
    }
}

static void fill_parsed_cmd(parser_t *parser, char **parsed_cmd)
{
    char *cmd_arg = NULL;
    size_t pos = 0;

    for (parser_data_t *nod = parser->head; nod != NULL; nod = nod->next) {
        if (!nod->is_tangible)
            cmd_arg = strdup(nod->arg);
        if (nod->is_tangible)
            cmd_arg = remove_padding(nod->arg);
        parsed_cmd[pos] = strdup(cmd_arg);
        free(cmd_arg);
        pos++;
    }
}

char **parse_cmd(char *command)
{
    int quoted_args = get_quoted_params(command);
    parser_t *parser = init_parser();
    char **parsed_cmd = NULL;

    if (quoted_args == -1)
        return parsed_cmd;
    fill_parser(command, parser);
    parsed_cmd = calloc(sizeof(char *), parser->size + 1);
    if (!parsed_cmd)
        return parsed_cmd;
    fill_parsed_cmd(parser, parsed_cmd);
    destroy_parser(parser);
    return parsed_cmd;
}
