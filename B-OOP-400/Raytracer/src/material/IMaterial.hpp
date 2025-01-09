/*
** EPITECH PROJECT, 2024
** B-OOP-400-REN-4-1-raytracer-maxence.largeot [WSL: Ubuntu]
** File description:
** Imateril
*/

#pragma once

    #include "Utils.hpp"
    #include "Color.hpp"
    #include "Ray.hpp"
    #include "HitRecord.hpp"
    #define UNUSED __attribute__((unused))

class IMaterial {
  public:
    virtual ~IMaterial() = default;

    virtual Color emitted(UNUSED double u,UNUSED double v,UNUSED const Point3& p) const {
      return Color(0,0,0);
    }

    virtual bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered
    ) const = 0;
};
