/*
** EPITECH PROJECT, 2024
** groundhog [WSL: Ubuntu]
** File description:
** parseur
*/

#include "parseur.hpp"

Parseur::Parseur() {}

Parseur::~Parseur() {}

void Parseur::help()
{
    std::cout << "SYNOPSIS" << std::endl;
    std::cout << "      ./groundhog period" << std::endl;
    std::cout << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "      period          the number of days defining a period" << std::endl;
}

bool Parseur::float_nbr(const std::string& str)
{
    bool point = false;

    for (char c : str) {
        if (c == '.' && point == false) {
            point = true;
            continue;
        }
        if (!isdigit(c) && c != '-') {
            return false;
        }
    }
    return true;
}

bool Parseur::Pos(const std::string& str)
{
    if (str.empty()) {
        return false;
    }
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

int Parseur::parseur(int argc, char **argv)
{
    if (argc != 2)
        return 2;
    std::string period = argv[1];
    if (period == "-h") {
        help();
        return 1;
    }
    if (!Pos(period))
        return 2;
    return 0;
}