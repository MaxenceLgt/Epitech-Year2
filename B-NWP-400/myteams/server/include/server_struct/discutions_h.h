/*
** EPITECH PROJECT, 2024
** Untitled (Workspace)
** File description:
** discutions_h
*/

#ifndef DISCUTIONS_H_H_
    #define DISCUTIONS_H_H_

    #include <time.h>
    #include <uuid/uuid.h>
    #include "define_h.h"

typedef struct discutions_s {
    char message[MAX_BODY_LENGTH];
    uuid_t sender;
    time_t timestamp;
} discutions_t;

#endif /* !DISCUTIONS_H_H_ */
