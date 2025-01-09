/*
** EPITECH PROJECT, 2024
** B-CNA-410-REN-4-1-groundhog-maxence.largeot [WSL: Ubuntu]
** File description:
** main
*/

#include <unistd.h>
#include <string>
#include <iostream>
#include <cctype>
#include <map>
#include "day.hpp"
#include "parseur.hpp"

int main(int argc, char  **argv)
{
    Day day;
    Parseur pars;
    int pars_good = pars.parseur(argc, argv);


    if (pars_good == 1)
        return 0;
    if (pars_good == 2)
        return 84;
    day.change_period(std::stoi(argv[1]));

    std::string nbr;
    while (true) {
        std::getline(std::cin, nbr);
        if (nbr == "STOP") {
            if (day.get_day() < day.get_period())
                return 84;
            day.stop();
            break;
        }
        if (!pars.float_nbr(nbr)) {
            return 84;
        }
        day.change_day(1);
        day.make_calcul(std::stof(nbr));
    }
    return 0;
}
