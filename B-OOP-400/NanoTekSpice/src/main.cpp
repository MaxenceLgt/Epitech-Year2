/*
** EPITECH PROJECT, 2024
** B-OOP-400-REN-4-1-tekspice-arthur.doriel [WSL: Ubuntu]
** File description:
** main
*/

#include <iostream>
#include "Shell.hpp"

int main(int argc, char  **argv)
{
    if (argc != 2)
        return 84;
    try {
        Shell shell;
        shell.run(argv[1]);
        return 0;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
