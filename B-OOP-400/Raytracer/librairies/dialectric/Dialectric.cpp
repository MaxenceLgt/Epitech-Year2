/*
** EPITECH PROJECT, 2024
** raytracer [WSL: Ubuntu]
** File description:
** lambertian
*/

#include <libconfig.h++>
#include "Dialectric.hpp"

Dialectric::Dialectric(const libconfig::Setting &settings)
{
    try {
        float tmp_refraction;
        if (!settings.exists("refraction") || !settings.lookupValue("refraction", tmp_refraction))
            throw std::runtime_error("failed to load dialectric material");
        refraction_index = tmp_refraction;
    } catch(const libconfig::SettingNotFoundException &nfex) {
        std::cerr << "Dialectric: Missing 'albedo' setting in configuration." << std::endl;
        std::cerr << "example : Dialectric = { refraction = 0.5 }" << std::endl;
        throw nfex;
    }
}

Dialectric::~Dialectric()
{
}

bool Dialectric::scatter(UNUSED const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const
{
    attenuation = Color(1.0, 1.0, 1.0);
    double ri = rec.front_face ? (1.0/refraction_index) : refraction_index;

    Vec3 unit_direction = unit_vector(r_in.direction());
    double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

    bool cannot_refract = ri * sin_theta > 1.0;
    Vec3 direction;

    if (cannot_refract || (cos_theta > Utils::random_double() && ri > Utils::random_double()))
        direction = reflect(unit_direction, rec.normal);
    else
        direction = refract(unit_direction, rec.normal, ri);

    scattered = Ray(rec.p, direction);
    return true;
}

double Dialectric::reflectance(double cosine, double refraction_index) {
        auto r0 = (1 - refraction_index) / (1 + refraction_index);
        r0 = r0*r0;
        return r0 + (1-r0)*pow((1 - cosine),5);
}

extern "C" IMaterial *entryPoint(const libconfig::Setting &settings)
{
    return (new Dialectric(settings));
}
