/*
** EPITECH PROJECT, 2024
** raytracer [WSL: Ubuntu]
** File description:
** lambertian
*/

#include <libconfig.h++>
#include "Diffuselight.hpp"

Diffuselight::Diffuselight(const libconfig::Setting &settings)
{
    try {
        albedo = Vec3::parseVec3(settings["albedo"]);
        tex = make_shared<Solid_color>(albedo);
    } catch(const libconfig::SettingNotFoundException &nfex) {
        std::cerr << "Lambertian: Missing 'albedo' setting in configuration." << std::endl;
        std::cerr << "example : Lambertian = { albedo = { x = 0.5; y = 0.5; z= 0.5 } }" << std::endl;
        throw nfex;
    }
}

Diffuselight::~Diffuselight() = default;


extern "C" IMaterial *entryPoint(const libconfig::Setting &settings)
{
    return (new Diffuselight(settings));
}
