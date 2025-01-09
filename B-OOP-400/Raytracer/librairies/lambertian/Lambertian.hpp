/*
** EPITECH PROJECT, 2024
** B-OOP-400-REN-4-1-raytracer-maxence.largeot [WSL: Ubuntu]
** File description:
** material
*/

#pragma once

  #include <libconfig.h++>
  #include "CheckerTex.hpp"
  #include "Vec3.hpp"
  #include "IMaterial.hpp"
  #define UNUSED __attribute__((unused))

class Lambertian : public IMaterial {
  public:
    Lambertian(const Color& albedo);
    Lambertian(const libconfig::Setting &settings);
    ~Lambertian();
  public:
    bool scatter(UNUSED const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override;
  private:
    Color albedo;
    shared_ptr<ITexture> tex;
};

extern "C" IMaterial *entryPoint(const libconfig::Setting &settings);
