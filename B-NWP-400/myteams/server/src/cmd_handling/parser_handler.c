/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** parser_handler
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "parser_h.h"

static bool is_empty_args(char *args)
{
    if (!args)
        return true;
    for (size_t i = 0; args[i] != '\0'; i++)
        if (args[i] != '\t' && args[i] != ' ' && args[i] != '\n')
            return false;
    return true;
}

parser_t *init_parser(void)
{
    parser_t *parser = malloc(sizeof(parser_t) * 1);

    if (!parser)
        return NULL;
    parser->head = NULL;
    parser->tail = NULL;
    parser->size = 0;
    return parser;
}

static void dest_lst_content(parser_data_t *lst_node)
{
    while (lst_node->prev){
        lst_node = lst_node->prev;
        if (lst_node->next->arg)
            free(lst_node->next->arg);
        free(lst_node->next);
    }
    if (lst_node->arg)
        free(lst_node->arg);
    free(lst_node);
}

void destroy_parser(parser_t *parser)
{
    parser_data_t *lst_node = NULL;

    if (!parser)
        return;
    lst_node = parser->tail;
    if (lst_node)
        dest_lst_content(lst_node);
    free(parser);
}

void parser_add_node_back(parser_t *parser, char *args, bool is_tangible)
{
    parser_data_t *node = NULL;

    if (is_tangible == true && is_empty_args(args))
        return;
    node = malloc(sizeof(parser_data_t) * 1);
    if (!node)
        return;
    node->is_tangible = is_tangible;
    node->arg = strdup(args);
    node->next = NULL;
    node->prev = parser->tail;
    if (parser->head == NULL)
        parser->head = node;
    if (parser->tail)
        parser->tail->next = node;
    parser->tail = node;
    parser->size++;
}
