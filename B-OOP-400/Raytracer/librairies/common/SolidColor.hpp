/*
** EPITECH PROJECT, 2024
** B-OOP-400-REN-4-1-raytracer-maxence.largeot [WSL: Ubuntu]
** File description:
** material
*/

#pragma once

#include "ITexture.hpp"
#define UNUSED __attribute__((unused))

class Solid_color : public ITexture {
  public:
    Solid_color(const Color& albedo);

    Solid_color(double red, double green, double blue);

    Color value(double u, double v, const Point3& p) const;

  private:
    Color albedo;
};
