/*
** EPITECH PROJECT, 2024
** B-OOP-400-REN-4-1-raytracer-maxence.largeot [WSL: Ubuntu]
** File description:
** color
*/

#pragma once

#include "Interval.hpp"
#include "Vec3.hpp"

using Color = Vec3;

inline double linear_to_gamma(double linear_component)
{
    if (linear_component > 0)
        return sqrt(linear_component);

    return 0;
}

struct Pixel {
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

void write_color(std::ostream& out, const Color& pixel_color);
void write_color(std::ostream& out, const Pixel& pixel_color);
void write_color_multithread(std::string &buffer, const Color &pixel_color, int i);
Pixel color_to_pixel(const Color& pixel_color);
