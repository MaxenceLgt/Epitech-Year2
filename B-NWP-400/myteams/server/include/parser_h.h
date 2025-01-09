/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** parser_h
*/

#ifndef PARSER_H_H_
    #define PARSER_H_H_

    #include <stdbool.h>
    #include <sys/types.h>

typedef struct parser_data_s {
    bool is_tangible;
    char *arg;
    struct parser_data_s *next;
    struct parser_data_s *prev;
} parser_data_t;

typedef struct parser_s {
    parser_data_t *head;
    parser_data_t *tail;
    size_t size;
} parser_t;

parser_t *init_parser(void);
void destroy_parser(parser_t *parser);
void parser_add_node_back(parser_t *parser, char *args, bool is_tangible);

#endif /* !PARSER_H_H_ */
