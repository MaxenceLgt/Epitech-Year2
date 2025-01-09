/*
** EPITECH PROJECT, 2024
** groundhog [WSL: Ubuntu]
** File description:
** calcul
*/

#include "day.hpp"
#include <cmath>
#include <iomanip>

Day::Day()
{
    day = 0;
    switch_count = 0;
    switch_occurs = false;
}

Day::~Day() {}

void Day::calcul_s()
{
    float result = 0;
    float moyenne = 0;
    float moyenne2 = 0;

    if (day < period) {
        std::cout << "      s=nan" << std::endl;
        return;
    }
    for (int temp = day;temp != day - period;temp--) {
        moyenne += date[temp];
    }
    moyenne = moyenne / period;
    for (int temp = day;temp != day - period;temp--) {
        moyenne2 += pow((date[temp] - moyenne), 2);
    }
    moyenne2 = moyenne2 / period;
    result = round(sqrt(moyenne2) * 100) / 100;
    if (switch_occurs) {
        std::cout << std::fixed << std::setprecision(2) << "\t\ts=" << result << "\t\ta switch occurs" << std::endl;
        switch_occurs = false;
        return;
    }
    std::cout << std::fixed << std::setprecision(2) << "\t\ts=" << result << std::endl;
    return;
}

void Day::calcul_r()
{
    float result = 0;
    int result2 = 0;
    float temp2 = 0;
    float temp = day;

    if (day <= period) {
        std::cout << "\t\tr=nan";
        return;
    }
    temp2 = date[temp - period];
    if (temp2 == 0)
        temp2 = 1;
    result = round((((date[temp] - temp2) / temp2) * 100) * 1) / 1;
    if (day != period && day != (period + 1) && ((last < 0 && result >= 0) || (last >= 0 && result < 0))) {
        last = result;
        result2 = result;
        switch_occurs = true;
        switch_count += 1;
        std::cout << "\t\tr=" << result2 << "%";
        return;
    }
    result2 = result;
    std::cout << "\t\tr=" << result2 << "%";
    last = result;
    return;
}

void Day::calcul_g()
{
    float result = 0;
    float moyenne = 0;

    if (day <= period) {
        std::cout << "g=nan";
        return;
    }
    for (int temp = day;temp != day - period;temp--) {
        if (date[temp - 1] < date[temp])
            moyenne += (date[temp] - date[temp - 1]);
    }
    moyenne = moyenne / period;
    result = round((moyenne) * 100) / 100;
    std::cout << std::fixed << std::setprecision(2) << "g=" << result;
    return;
}

int Day::get_day()
{
    return day;
}

void Day::change_day(int nbr)
{
    day = day + nbr;
}

int Day::get_period()
{
    return period;
}

void Day::change_period(int nbr)
{
    period = nbr;
}

void Day::make_calcul(float nbr)
{
    date[day] = nbr;
    calcul_g();
    calcul_r();
    calcul_s();
    return;
}

void Day::stop()
{
    std::cout << "Global tendency switched " << switch_count << " times" << std::endl;
    return;
}
