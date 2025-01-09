/*
** EPITECH PROJECT, 2024
** B-OOP-400-REN-4-1-Raytracer-maxence.largeot [WSL: Ubuntu]
** File description:
** Ray
*/

#pragma once

  #include "Vec3.hpp"

class Ray {
  public:
    Ray();
    Ray(const Point3& origin, const Vec3& direction);
    ~Ray();
  public:
    const Point3& origin() const;
    const Vec3& direction() const;
    Point3 at(double t) const;
  private:
    Point3 orig;
    Vec3 dir;
};
