/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Color
*/

#include "Color.hpp"

void write_color(std::ostream& out, const Color& pixel_color)
{
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    static const Interval intensity(0.000, 0.999);
    char rbyte = int(256 * intensity.clamp(r));
    char gbyte = int(256 * intensity.clamp(g));
    char bbyte = int(256 * intensity.clamp(b));

    out << rbyte << gbyte <<  bbyte;
//    out << rbyte << ' ' << gbyte << ' ' << bbyte << std::endl;
}

void write_color_multithread(std::string &buffer, const Color &pixel_color, int i)
{
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    static const Interval intensity(0.000, 0.999);
//    char rbyte = char(256 * intensity.clamp(r));
//    char gbyte = char(256 * intensity.clamp(g));
//    char bbyte = char(256 * intensity.clamp(b));
    (void)i;

//    buffer += std::to_string(rbyte) + ' ' + std::to_string(gbyte) + ' ' + std::to_string(bbyte) + '\n';
    buffer += char(256 * intensity.clamp(r));
    buffer += char(256 * intensity.clamp(g));
    buffer += char(256 * intensity.clamp(b));
}

void write_color(std::ostream& out, const Pixel& pixel_color)
{
//    std::cout << (int)pixel_color.r << (int)pixel_color.g << (int)pixel_color.b << std::endl;
    out << pixel_color.r << pixel_color.g << pixel_color.b;
}

Pixel color_to_pixel(const Color& pixel_color)
{
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    static const Interval intensity(0.000, 0.999);
    unsigned  char rbyte = char(256 * intensity.clamp(r));
    unsigned  char gbyte = char(256 * intensity.clamp(g));
    unsigned  char bbyte = char(256 * intensity.clamp(b));

    return Pixel{rbyte, gbyte, bbyte};
}
