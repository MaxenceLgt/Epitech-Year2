/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** main.cpp
*/

#include <iostream>
#include "ErrorHandler.hpp"
#include "Core.hpp"

int main(int ac, char **av)
{
    Arcade::ErrorHandler errorHandler;

    try {
        errorHandler.checkArgumentsNumber(ac);
        errorHandler.checkLibValidity(av[1]);
        Arcade::Core core(av[1]);
        core.mainLoop();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
