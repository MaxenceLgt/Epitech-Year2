/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** ColorMat
*/

#include "ColorMat.hpp"

bool ColorMat::scatter(UNUSED const Ray &ray, const HitRecord &record, Color &attenuation, Ray &scattered) const
{
    attenuation = _color;
    scattered = Ray(record.p, record.normal);
    return true;
}
