/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Plan
*/

#include "Plan.hpp"

Plan::Plan(const Vec3 &dir, const Point3& center, shared_ptr<IMaterial> mat) : APrimitive(mat), _dir(dir), _center(center)
{
}

Plan::Plan(const Plan &obj) : APrimitive(obj.getMaterial()), _dir(obj._dir), _center(obj._center)
{
}

Plan::Plan(const libconfig::Setting &settings)
{
    Vec3 dir;
    Point3 center;

    if (!settings.exists("direction") || !settings.exists("center")) {
        std::cerr << "invalid Plan settings, example : " << std::endl;
        std::cerr << "plan= (center = {0; 0; 0}; direction = {0; 0; 1})" << std::endl;
        throw Plan::PrimError("Plan: missing dir or center.");
    }
    dir = Vec3::parseVec3(settings["direction"]);
    center = Point3::parseVec3(settings["center"]);
    _dir = dir;
    _center = center;
}

Plan::~Plan()
{
}

bool Plan::hit(const Ray& r, Interval ray_t, HitRecord& rec) const
{
    auto t = dot((this->_center - r.origin()), this->_dir) / dot(r.direction(), this->_dir);
    if (t < ray_t.min || t > ray_t.max)
        return false;
    rec.t = t;
    rec.p = r.at(rec.t);
    rec.set_face_normal(r, this->_dir);
    rec.mat = this->getMaterial();
    return true;
}

Plan &Plan::operator=(const Plan &obj)
{
    if (this == &obj)
        return *this;
    this->_center = obj._center;
    this->_dir = obj._dir;
    this->setMaterial(obj.getMaterial());
    return *this;
}

extern "C" IPrimitive *entryPoint(const libconfig::Setting &settings)
{
    return new Plan(settings);
}
