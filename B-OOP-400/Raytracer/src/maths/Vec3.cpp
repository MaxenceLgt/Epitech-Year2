/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Vec3
*/

#include "Vec3.hpp"

Vec3::Vec3() : e{0,0,0}
{
}

Vec3::Vec3(double e0, double e1, double e2) : e{e0, e1, e2}
{
}

Vec3::~Vec3()
{
}

double Vec3::x() const
{
    return this->e[0];
}

double Vec3::y() const
{
    return this->e[1];
}
double Vec3::z() const
{
    return this->e[2];
}

Vec3 Vec3::operator-() const
{
    return Vec3(-this->e[0], -this->e[1], -this->e[2]);
}

double Vec3::operator[](int i) const
{
    return this->e[i];
}

double& Vec3::operator[](int i)
{
    return this->e[i];
}

Vec3& Vec3::operator+=(const Vec3& v)
{
    this->e[0] += v.e[0];
    this->e[1] += v.e[1];
    this->e[2] += v.e[2];
    return *this;
}

Vec3& Vec3::operator*=(double t) {
    this->e[0] *= t;
    this->e[1] *= t;
    this->e[2] *= t;
    return *this;
}

Vec3& Vec3::operator/=(double t)
{
    return *this *= 1 / t;
}

double Vec3::length() const
{
    return sqrt(this->length_squared());
}

double Vec3::length_squared() const
{
    return this->e[0] * this->e[0] + this->e[1] * this->e[1] + this->e[2] * this->e[2];
}

bool Vec3::near_zero() const
{
    auto s = 1e-8;

    return (fabs(this->e[0]) < s) && (fabs(this->e[1]) < s) && (fabs(this->e[2]) < s);
}

Vec3 Vec3::parseVec3(const libconfig::Setting &setting)
{
    double x, y, z;

    try {
        x = Vec3::getValue(setting, "x");
        y = Vec3::getValue(setting, "y");
        z = Vec3::getValue(setting, "z");
    } catch (const libconfig::SettingNotFoundException &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        throw e;
    }
    return Vec3(x, y, z);
}

void Vec3::reset()
{
    this->e[0] = 0;
    this->e[1] = 0;
    this->e[2] = 0;
}
double Vec3::getValue(const libconfig::Setting &setting, std::string name)
{
    double value_double = 0.0;
    int value_int = 0;
    bool isintValue = false;

    try {
        if (setting[name.c_str()].getType() == libconfig::Setting::TypeInt) {
            setting.lookupValue(name, value_int);
            isintValue = true;
        }
        else if (setting[name.c_str()].getType() == libconfig::Setting::TypeFloat)
            setting.lookupValue(name, value_double);
    } catch (const libconfig::SettingNotFoundException &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        throw e;
    }
    if (isintValue)
        return value_int;
    return value_double;
}
