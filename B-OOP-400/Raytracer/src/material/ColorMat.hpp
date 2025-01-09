/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** ColorMat
*/


#include "IMaterial.hpp"
#define UNUSED __attribute__((unused))

class ColorMat : IMaterial {
    public:
        ColorMat(const Color &color) : _color(color) {}
        bool scatter(UNUSED const Ray &ray, const HitRecord &record, Color &attenuation, Ray &scattered) const override;

    private:
        Color _color;
};
