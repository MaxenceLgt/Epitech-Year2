/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Cone
*/

#pragma once

    #include "APrimitive.hpp"

class Cone : public APrimitive {
    public:
        Cone(const double radius, const Point3& center, shared_ptr<IMaterial> mat);
        Cone(const libconfig::Setting &settings);
        Cone(const Cone &obj);
        ~Cone();
    public:
        bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const override;
    public:
        Cone &operator=(const Cone &obj);
    private:
        double _radius;
        Point3 _center;
};

extern "C" IPrimitive *entryPoint(const libconfig::Setting &settings);