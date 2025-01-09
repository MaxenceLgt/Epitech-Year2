/*
** EPITECH PROJECT, 2024
** raytracer [WSL: Ubuntu]
** File description:
** Checker_tex
*/

#include "CheckerTex.hpp"

Checker_tex::Checker_tex(double scale, shared_ptr<ITexture> even, shared_ptr<ITexture> odd) : inv_scale(1.0 / scale), even(even), odd(odd)
{
}

Checker_tex::Checker_tex(double scale, const Color& c1, const Color& c2) : inv_scale(1.0 / scale), even(make_shared<Solid_color>(c1)), odd(make_shared<Solid_color>(c2))
{
}

Color Checker_tex::value(double u, double v, const Point3& p) const
{
    auto xInteger = int(std::floor(inv_scale * p.x()));
    auto yInteger = int(std::floor(inv_scale * p.y()));
    auto zInteger = int(std::floor(inv_scale * p.z()));

    bool isEven = (xInteger + yInteger + zInteger) % 2 == 0;

    return isEven ? even->value(u, v, p) : odd->value(u, v, p);
}
