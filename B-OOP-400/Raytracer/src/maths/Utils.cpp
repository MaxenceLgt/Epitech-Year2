/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** utils
*/

#include "Utils.hpp"

double Utils::degrees_to_radians(double degrees)
{
    return degrees * pi / 180.0;
}

double Utils::random_double()
{
    return rand() / (RAND_MAX + 1.0);
}

double Utils::random_double(double min, double max)
{
    return min + (max - min) * random_double();
}

double Utils::settings_get_double(const libconfig::Setting &setting, const char *name)
{
    double d_value;
    int i_value;

    if (setting[name].getType() == libconfig::Setting::TypeInt) {
        setting.lookupValue(name, i_value);
        d_value = i_value;
    } else {
        setting.lookupValue(name, d_value);
    }
    return d_value;
}

int Utils::settings_get_int(const libconfig::Setting &setting, const char *name)
{
    int i_value;
    double d_value;

    if (setting[name].getType() == libconfig::Setting::TypeInt) {
        setting.lookupValue(name, i_value);
    } else {
        setting.lookupValue(name, d_value);
        i_value = d_value;
    }
    return i_value;
}

double Utils::settings_get_ratio(const libconfig::Setting &setting)
{
    double ratio;

    if (!setting.exists("width") || !setting.exists("height"))
        throw std::runtime_error("Missing width or height in ratio settings");

    ratio = settings_get_double(setting, "width") / settings_get_double(setting, "height");
    return ratio;
}
