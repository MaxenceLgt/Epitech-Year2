/*
** EPITECH PROJECT, 2024
** B-OOP-400-REN-4-1-raytracer-maxence.largeot [WSL: Ubuntu]
** File description:
** utils
*/

#pragma once

    #include <cmath>
    #include <iostream>
    #include <limits>
    #include <cstdlib>
    #include <memory>
    #include <vector>
    #include <thread>
    #include <libconfig.h++>

using std::fabs;
using std::make_shared;
using std::shared_ptr;
using std::sqrt;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

class Utils {
    public:
        static double degrees_to_radians(double degrees);
        static double random_double();
        static double random_double(double min, double max);
        static double settings_get_double(const libconfig::Setting &setting, const char *name);
        static int settings_get_int(const libconfig::Setting &setting, const char *name);
        static double settings_get_ratio(const libconfig::Setting &setting);
};
