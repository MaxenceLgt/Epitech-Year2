/*
** EPITECH PROJECT, 2024
** raytracer [WSL: Ubuntu]
** File description:
** Texture
*/

#pragma once

#include "Utils.hpp"
#include "Color.hpp"
#include "Ray.hpp"
#include "HitRecord.hpp"

class ITexture {
  public:
    virtual ~ITexture() = default;

    virtual Color value(double u, double v, const Point3& p) const = 0;
};
