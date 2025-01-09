/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Plan
*/

#pragma once

    #include "APrimitive.hpp"

class Trans : public APrimitive {
  public:
    Trans(shared_ptr<IPrimitive> object, const Vec3& offset) : object(object), offset(offset) {};
    bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const;
  private:
    shared_ptr<IPrimitive> object;
    Vec3 offset;
};
