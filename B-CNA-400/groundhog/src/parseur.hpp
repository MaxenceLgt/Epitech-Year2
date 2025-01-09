/*
** EPITECH PROJECT, 2024
** groundhog [WSL: Ubuntu]
** File description:
** parseur
*/

#pragma once
#include <unistd.h>
#include <string>
#include <iostream>
#include <memory>
#include <map>

class Parseur {
    public: 
        Parseur();
        ~Parseur();

    public:
        void help();
        bool Pos(const std::string& str);
        bool float_nbr(const std::string& str);
        int parseur(int argc, char **argv);

    private:
        
};
