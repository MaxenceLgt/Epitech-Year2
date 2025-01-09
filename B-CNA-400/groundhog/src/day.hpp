/*
** EPITECH PROJECT, 2024
** B-CNA-410-REN-4-1-groundhog-maxence.largeot [WSL: Ubuntu]
** File description:
** main
*/

#pragma once
#include <unistd.h>
#include <string>
#include <iostream>
#include <memory>
#include <map>

class Day {
    public: 
        Day();
        ~Day();

    public:
        void make_calcul(float nbr);
        void calcul_g(void);
        void calcul_r(void);
        void calcul_s(void);
        int get_day();
        void change_day(int nbr);
        int get_period();
        void change_period(int nbr);
        void stop();

    private:
        int day;
        int period;
        float last;
        bool switch_occurs;
        int switch_count;
        std::map<int, float> date;
};
