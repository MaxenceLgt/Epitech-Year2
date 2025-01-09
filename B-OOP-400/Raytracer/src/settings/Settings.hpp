/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Settings
*/

#pragma once
#include "Utils.hpp"

class Settings {
    public:
    Settings(const libconfig::Setting &settings);
    ~Settings() = default;
    void setOutputPath(const libconfig::Setting &setting);
    void setMultithreading(const libconfig::Setting &setting);
    void setType(const libconfig::Setting &setting);
    [[nodiscard]] const std::string &getOutputPath() const { return _output_path; };
    [[nodiscard]] bool getMultithreading() const { return _multithreading; };
    [[nodiscard]] const std::string &getType() const { return _type; };

    private:
    std::string _output_path = "Rendu.ppm";
    bool _multithreading = false;
    std::string _type   = "ppm";

    class SettingsError : public std::exception {
        public:
        explicit SettingsError(std::string message) : _message(std::move(message)) {};
        const char *what() const noexcept override { return _message.c_str(); };
        private:
        std::string _message;
    };
};
