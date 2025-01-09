/*
** EPITECH PROJECT, 2024
** raytracer [WSL: Ubuntu]
** File description:
** Checker_tex
*/

#include "SolidColor.hpp"

class Checker_tex : public ITexture {
  public:
    Checker_tex(double scale, shared_ptr<ITexture> even, shared_ptr<ITexture> odd);
    Checker_tex(double scale, const Color& c1, const Color& c2);

    Color value(double u, double v, const Point3& p) const;

  private:
    double inv_scale;
    shared_ptr<ITexture> even;
    shared_ptr<ITexture> odd;
};
