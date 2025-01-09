/*
** EPITECH PROJECT, 2024
** B-OOP-400-REN-4-1-raytracer-maxence.largeot [WSL: Ubuntu]
** File description:
** material
*/

#pragma once

  #include <libconfig.h++>
  #include "Vec3.hpp"
  #include "IMaterial.hpp"
  #define UNUSED __attribute__((unused))

class Dialectric : public IMaterial {
  public:
    Dialectric(const Color& albedo);
    Dialectric(const libconfig::Setting &settings);
    ~Dialectric();
  public:
    bool scatter(UNUSED const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override;
    double reflectance(double cosine, double refraction_index);
  private:
    double refraction_index;
};

extern "C" IMaterial *entryPoint(const libconfig::Setting &settings);
