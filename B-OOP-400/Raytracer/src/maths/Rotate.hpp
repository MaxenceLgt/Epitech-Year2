/*
** EPITECH PROJECT, 2024
** raytracer [WSL: Ubuntu]
** File description:
** rotate
*/

#pragma once 

    #include "APrimitive.hpp"

class Rotate : public APrimitive {
  public:
    Rotate(shared_ptr<APrimitive> object, double angle) : object(object) {
        auto radians = Utils::degrees_to_radians(angle);
        sin_theta = sin(radians);
        cos_theta = cos(radians);
    };

    bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const;

    private:
        shared_ptr<APrimitive> object;
        double sin_theta;
        double cos_theta;
};
