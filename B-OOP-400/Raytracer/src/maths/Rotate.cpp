/*
** EPITECH PROJECT, 2024
** raytracer [WSL: Ubuntu]
** File description:
** rotate
*/

#include "Rotate.hpp"

bool Rotate::hit(const Ray& r, Interval ray_t, HitRecord& rec) const
{
    auto origin = r.origin();
    auto direction = r.direction();

    origin[0] = cos_theta*r.origin()[0] - sin_theta*r.origin()[2];
    origin[2] = sin_theta*r.origin()[0] + cos_theta*r.origin()[2];

    direction[0] = cos_theta*r.direction()[0] - sin_theta*r.direction()[2];
    direction[2] = sin_theta*r.direction()[0] + cos_theta*r.direction()[2];

    Ray rotated_r(origin, direction);

    if (!object->hit(rotated_r, ray_t, rec))
        return false;

    auto p = rec.p;
    p[0] =  cos_theta*rec.p[0] + sin_theta*rec.p[2];
    p[2] = -sin_theta*rec.p[0] + cos_theta*rec.p[2];

    auto normal = rec.normal;
    normal[0] =  cos_theta*rec.normal[0] + sin_theta*rec.normal[2];
    normal[2] = -sin_theta*rec.normal[0] + cos_theta*rec.normal[2];

    rec.p = p;
    rec.normal = normal;

    return true;
}