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

class Metal : public IMaterial {
  public:
    Metal(const Color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}
    Metal(const libconfig::Setting &settings);
    ~Metal();
  public:
    bool scatter(UNUSED const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override;
  private:
    Color albedo;
    double fuzz;
};

extern "C" IMaterial *entryPoint(const libconfig::Setting &settings);
