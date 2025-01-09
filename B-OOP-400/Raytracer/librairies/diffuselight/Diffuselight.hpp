/*
** EPITECH PROJECT, 2024
** B-OOP-400-REN-4-1-raytracer-maxence.largeot [WSL: Ubuntu]
** File description:
** material
*/

#pragma once

  #include <libconfig.h++>
  #include "Vec3.hpp"
  #include "../common/CheckerTex.hpp"
  #include "IMaterial.hpp"
  #define UNUSED __attribute__((unused))

class Diffuselight : public IMaterial {
  public:
    Diffuselight(const libconfig::Setting &settings);
    ~Diffuselight();

    Color emitted(double u, double v, const Point3& p) const {
        return tex->value(u, v, p);
    }

    bool scatter(UNUSED const Ray& r_in,UNUSED const HitRecord& rec,UNUSED Color& attenuation,UNUSED Ray& scattered) const override {
      return false;
    };

  private:
    Color albedo;
    shared_ptr<ITexture> tex;
};

extern "C" IMaterial *entryPoint(const libconfig::Setting &settings);
