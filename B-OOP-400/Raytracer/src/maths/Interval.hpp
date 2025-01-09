/*
** EPITECH PROJECT, 2024
** B-OOP-400-REN-4-1-raytracer-maxence.largeot [WSL: Ubuntu]
** File description:
** Interval
*/

#pragma once

    #include "Utils.hpp"

class Interval {
    public:
        Interval();
        Interval(double min, double max);
        ~Interval();
    public:
        double size() const;
        bool contains(double x) const;
        bool surrounds(double x) const;
        double clamp(double x) const;
    public:
        double min;
        double max;
        static const Interval empty;
        static const Interval universe;
};
