/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Plan
*/

#include "Trans.hpp"

bool Trans::hit(const Ray& r, Interval ray_t, HitRecord& rec) const
{
    Ray offset_r(r.origin() - offset, r.direction());

    if (!object->hit(offset_r, ray_t, rec))
        return false;
    rec.p += offset;

    return true;
}
