/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Cylinder
*/

#include "Cylinder.hpp"

Cylinder::Cylinder(double radius, const Point3& center, shared_ptr<IMaterial> mat) : APrimitive(mat), _radius(fmax(0,radius)), _center(center)
{
}

Cylinder::Cylinder(const libconfig::Setting &settings)
{
    try {
        float radius_str = 84;
        settings["center"].lookupValue("x", _center[0]);
        settings["center"].lookupValue("y", _center[1]);
        settings["center"].lookupValue("z", _center[2]);
        if (!settings.lookupValue("radius", radius_str)) {
            std::cerr << "Cylinder: error on reading radius." << std::endl;
            throw std::runtime_error("Cylinder: error on reading radius.");
        }
        _radius = radius_str;
    } catch (const libconfig::SettingNotFoundException &e) {
        std::cerr << "Cylinder: error on reading sphere." << std::endl;
        std::cerr << "example : Cylinder = { center = { x = 0; y = 0; Z = 0 }; radius = 1;  material = \"metal\"}" << std::endl;
        throw std::runtime_error("Cylinder: error on reading sphere.");
    }
}

Cylinder::Cylinder(const Cylinder &obj) : APrimitive(obj.getMaterial()), _radius(obj._radius), _center(obj._center)
{
}

Cylinder::~Cylinder()
{
}

bool Cylinder::hit(const Ray& r, Interval ray_t, HitRecord& rec) const
{
    Vec3 oc = r.origin() - this->_center;
    double a = r.direction().x() * r.direction().x() + r.direction().z() * r.direction().z();
    double b = 2 * (oc.x() * r.direction().x() + oc.z() * r.direction().z());
    double c = oc.x() * oc.x() + oc.z() * oc.z() - _radius * _radius;

    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return false;
    double sqrtd = sqrt(discriminant);
    double root = (-b - sqrtd) / (2 * a);
    if (root < ray_t.min || root > ray_t.max) {
        root = (-b + sqrtd) / (2 * a);
        if (root < ray_t.min || root > ray_t.max)
            return false;
    }
    rec.t = root;
    rec.p = r.at(rec.t);
    double normeSqX = (rec.p.x() - this->_center.x()) * (rec.p.x() - this->_center.x());
    double normeSqY = (rec.p.y() - this->_center.y()) * (rec.p.y() - this->_center.y());
    double normeSqZ = (rec.p.z() - this->_center.z()) * (rec.p.z() - this->_center.z());
    double norme = sqrt(normeSqX + normeSqY + normeSqZ);
    Vec3 outward_normal = (rec.p - _center) / norme;
    rec.set_face_normal(r, outward_normal);
    get_cylinder_uv(outward_normal, rec.u, rec.v);
    rec.mat = this->getMaterial();
    return true;
}

Cylinder &Cylinder::operator=(const Cylinder &obj)
{
    if (this == &obj)
        return *this;
    this->_radius = obj._radius;
    this->_center = obj._center;
    this->setMaterial(obj.getMaterial());
    return *this;
}

extern "C" IPrimitive *entryPoint(const libconfig::Setting &settings)
{
    return (new Cylinder(settings));
}
