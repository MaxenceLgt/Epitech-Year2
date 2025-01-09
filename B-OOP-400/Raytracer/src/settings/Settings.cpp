/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Settings
*/

#include "Settings.hpp"
#include <functional>
#include <map>

static const std::map<std::string, std::function<void (Settings*, const libconfig::Setting &)>> settings_map = {
        {"output", [](Settings* obj, const libconfig::Setting &setting) { return obj->setOutputPath(setting); }},
        {"multithread", [](Settings* obj, const libconfig::Setting &setting) { return obj->setMultithreading(setting); }},
        {"type", [](Settings* obj, const libconfig::Setting &setting) { return obj->setType(setting); }}
};

Settings::Settings(const libconfig::Setting &settings)
{
    if (!settings.exists("settings")) {
        return;
    }
    bool find = false;
    auto &settings_cfg = settings["settings"];

    for (int i = 0; i < settings_cfg.getLength(); i++) {
        auto &setting = settings_cfg[i];
        std::string name = setting.getName();
        for (auto &it : settings_map) {
            if (it.first == name) {
                it.second(this, settings_cfg);
                find = true;
                break;
            }
        }
        if (!find) {
            throw SettingsError("Settings: unknown setting " + name);
        } else
            find = false;
    }
}

void Settings::setOutputPath(const libconfig::Setting &setting)
{
    if (setting["output"].getType() != libconfig::Setting::Type::TypeString) {
        throw SettingsError("Settings: output must be a string");
    }

    setting.lookupValue("output", _output_path);

}

void Settings::setMultithreading(const libconfig::Setting &setting)
{
    if (setting["multithread"].getType() != libconfig::Setting::Type::TypeBoolean) {
        throw SettingsError("Settings: multithread must be a boolean");
    }
    setting.lookupValue("multithread", _multithreading);
}

void Settings::setType(const libconfig::Setting &setting)
{
    if (setting["type"].getType() != libconfig::Setting::Type::TypeString) {
        throw SettingsError("Settings: type must be a string");
    }
    setting.lookupValue("type", _type);
}
