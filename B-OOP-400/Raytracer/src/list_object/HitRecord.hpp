/*
** EPITECH PROJECT, 2024
** B-OOP-400-REN-4-1-raytracer-maxence.largeot [WSL: Ubuntu]
** File description:
** hittable
*/

#pragma once

  #include "Ray.hpp"
  #include "Interval.hpp"

class IMaterial;

class HitRecord {
  public:
    HitRecord();
    ~HitRecord();
  public:
    void set_face_normal(const Ray& r, const Vec3& outward_normal);
  public:
    Point3 p;
    Vec3 normal;
    shared_ptr<IMaterial> mat;
    double t;
    double u;
    double v;
    bool front_face;
};
