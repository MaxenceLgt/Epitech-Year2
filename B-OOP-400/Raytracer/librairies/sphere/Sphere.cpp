/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Sphere
*/

#include "Sphere.hpp"

Sphere::Sphere(const Point3& center, double radius, shared_ptr<IMaterial> mat) :  APrimitive(mat), center(center),
radius(fmax(0,radius))
{
}

Sphere::Sphere(const Sphere &obj) : APrimitive(obj.getMaterial()), center(obj.center), radius(obj.radius)
{
}

Sphere::Sphere(const libconfig::Setting &settings) : APrimitive()
{
    try {
        float radius_str = 84;
        settings["center"].lookupValue("x", center[0]);
        settings["center"].lookupValue("y", center[1]);
        settings["center"].lookupValue("z", center[2]);
        if (!settings.lookupValue("radius", radius_str)) {
            std::cerr << "Sphere: error on reading radius." << std::endl;
            throw std::runtime_error("Sphere: error on reading radius.");
        }
        radius = radius_str;
    } catch (const libconfig::SettingNotFoundException &e) {
        std::cerr << "Sphere: error on reading sphere." << std::endl;
        std::cerr << "example : Sphere = { center = { x = 0; y = 0; Z = 0 }; radius = 1;  material = \"metal\"}" << std::endl;
        throw std::runtime_error("Sphere: error on reading sphere.");
    }
}

Sphere::~Sphere()
{
}

bool Sphere::hit(const Ray& r, Interval ray_t, HitRecord& rec) const
{
    Vec3 oc = center - r.origin();
    auto a = r.direction().length_squared();
    auto h = dot(r.direction(), oc);
    auto c = oc.length_squared() - radius*radius;

    auto discriminant = h*h - a*c;
    if (discriminant < 0)
        return false;
    auto sqrtd = sqrt(discriminant);
    auto root = (h - sqrtd) / a;
    if (!ray_t.surrounds(root)) {
        root = (h + sqrtd) / a;
        if (!ray_t.surrounds(root))
            return false;
    }
    rec.t = root;
    rec.p = r.at(rec.t);
    Vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat = this->getMaterial();
    return true;
}

Sphere &Sphere::operator=(const Sphere &obj)
{
    if (this == &obj)
        return *this;
    this->center = obj.center;
    this->radius = obj.radius;
    this->setMaterial(obj.getMaterial());
    return *this;
}

extern "C" IPrimitive *entryPoint(const libconfig::Setting &settings)
{
    return (new Sphere(settings));
}
