/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Cylinder
*/

#pragma once

    #include "APrimitive.hpp"

class Cylinder : public APrimitive {
    public:
        Cylinder(double radius, const Point3& center, shared_ptr<IMaterial> mat);
        Cylinder(const libconfig::Setting &settings);
        Cylinder(const Cylinder &obj);
        ~Cylinder();
    public:
        bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const override;
    public:
        Cylinder &operator=(const Cylinder &obj);
    private:
        static void get_cylinder_uv(const Vec3 &p, double &u, double &v) {
            double theta = std::acos(-p.y());
            double phi = atan2(-p.z(), p.x()) + M_PI;
            u = phi / (2 * M_PI);
            v = theta / M_PI;
        };
        double _radius;
        Point3 _center;
};

extern "C" IPrimitive *entryPoint(const libconfig::Setting &settings);
