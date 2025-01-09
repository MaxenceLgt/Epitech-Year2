/*
** EPITECH PROJECT, 2024
** raytracer [WSL: Ubuntu]
** File description:
** lambertian
*/

#include <libconfig.h++>
#include "Lambertian.hpp"

Lambertian::Lambertian(const Color& albedo) : albedo(albedo)
{
}

Lambertian::Lambertian(const libconfig::Setting &settings)
{
    try {
        albedo = Vec3::parseVec3(settings["albedo"]);
        if (settings.exists("color"))
            tex = make_shared<Checker_tex>(0.32, albedo, Vec3::parseVec3(settings["color"]));
        else {
            tex = make_shared<Solid_color>(albedo);
        }
    } catch(const libconfig::SettingNotFoundException &nfex) {
        std::cerr << "Lambertian: Missing 'albedo' setting in configuration." << std::endl;
        std::cerr << "example : Lambertian = { albedo = { x = 0.5; y = 0.5; z= 0.5 } }" << std::endl;
        throw nfex;
    }
}

Lambertian::~Lambertian()
{
}

bool Lambertian::scatter(UNUSED const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const
{
    auto scatter_direction = rec.normal + random_unit_vector();

        if (scatter_direction.near_zero())
        scatter_direction = rec.normal;

    scattered = Ray(rec.p, scatter_direction);
    attenuation = tex->value(rec.u, rec.v, rec.p);;
    return true;
}

extern "C" IMaterial *entryPoint(const libconfig::Setting &settings)
{
    return (new Lambertian(settings));
}
