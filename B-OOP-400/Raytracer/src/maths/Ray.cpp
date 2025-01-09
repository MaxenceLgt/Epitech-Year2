/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Ray
*/

#include "Ray.hpp"

Ray::Ray()
{
}

Ray::Ray(const Point3& origin, const Vec3& direction) : orig(origin), dir(direction)
{

}

Ray::~Ray()
{
}

const Point3& Ray::origin() const
{
    return this->orig;
}

const Vec3& Ray::direction() const
{
    return this->dir;
}

Point3 Ray::at(double t) const
{
    return this->orig + t * this->dir;
}
