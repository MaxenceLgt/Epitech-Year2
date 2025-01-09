/*
** EPITECH PROJECT, 2024
** raytracer [WSL: Ubuntu]
** File description:
** lambertian
*/

#include <libconfig.h++>
#include "Metal.hpp"

Metal::Metal(const libconfig::Setting &settings)
{
    try {
        float tmp_fuzz;
        albedo = Vec3::parseVec3(settings["albedo"]);
        if (!settings.exists("fuzz") || !settings.lookupValue("fuzz", tmp_fuzz))
            throw std::runtime_error("failed to load metal material");
        fuzz = tmp_fuzz;
    } catch(const libconfig::SettingNotFoundException &nfex) {
        std::cerr << "Metal: Missing 'albedo' setting in configuration." << std::endl;
        std::cerr << "example : Metal = { albedo = { x = 0.5; y = 0.5; z= 0.5 }; fuzz = 0.5 }" << std::endl;
        throw nfex;
    }
}

Metal::~Metal()
{
}

bool Metal::scatter(UNUSED const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const
{
    Vec3 reflected = reflect(r_in.direction(), rec.normal);
    reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
    scattered = Ray(rec.p, reflected);
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
}

extern "C" IMaterial *entryPoint(const libconfig::Setting &settings)
{
    return (new Metal(settings));
}
