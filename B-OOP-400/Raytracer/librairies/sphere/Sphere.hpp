/*
** EPITECH PROJECT, 2024
** B-OOP-400-REN-4-1-raytracer-maxence.largeot [WSL: Ubuntu]
** File description:
** Sphere
*/

#pragma once

  #include <libconfig.h++>
  #include "APrimitive.hpp"
  #include "Utils.hpp"

class Sphere : public APrimitive {
  public:
    Sphere(const Point3& center, double radius, shared_ptr<IMaterial> mat);
    Sphere(const libconfig::Setting &settings);
    Sphere(const Sphere &obj);
    ~Sphere();
  public:
    bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const override;
  public:
    Sphere &operator=(const Sphere &obj);
  private:
    Point3 center;
    double radius;
    Color color;
};

extern "C" IPrimitive *entryPoint(const libconfig::Setting &settings);
