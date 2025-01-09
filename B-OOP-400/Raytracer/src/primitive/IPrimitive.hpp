/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** IPrimitive
*/

#pragma once

    #include "Ray.hpp"
    #include "Interval.hpp"
    #include "HitRecord.hpp"
#include "IMaterial.hpp"

class IPrimitive {
    public:
        virtual ~IPrimitive() = default;
    public:
        virtual bool hit(const Ray &ray, Interval ray_t, HitRecord &rec) const = 0;
};
