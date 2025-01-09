/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Plan
*/

#pragma once

    #include "APrimitive.hpp"

class Plan : public APrimitive {
  public:
    Plan(const Vec3 &dir, const Point3& center, shared_ptr<IMaterial> mat);
    Plan(const libconfig::Setting &settings);
    Plan(const Plan &obj);
    ~Plan();
  public:
    bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const override;
  public:
    Plan &operator=(const Plan &obj);
  private:
    Vec3 _dir;
    Point3 _center;
};

extern "C" IPrimitive *entryPoint(const libconfig::Setting &settings);
