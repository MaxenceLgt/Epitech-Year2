/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** builder
*/

#pragma once

#include <iostream>
#include <libconfig.h++>
#include <map>
#include <utility>
#include "IMaterial.hpp"
#include "CLibEncapsulation.hpp"
#include "PrimList.hpp"
#include "ColorMat.hpp"
#include "APrimitive.hpp"
#include "Camera.hpp"
#include "Settings.hpp"

class Builder {
    public:
        Builder(std::string path);
        Builder(const char *path);
        ~Builder() {};
        std::map<std::string, shared_ptr<IMaterial>> getMaterials();
        PrimList getPrimitives(std::map<std::string, shared_ptr<IMaterial>> &materials);
        Camera getCamera();
        Settings getSettings();

    template<class Type>
    Type getObjectFromLib(std::string &name, const libconfig::Setting &settings)
    {
        std::string path = pluginPath + name + ".so";

        if (access(path.c_str(), F_OK) == -1) {
            throw BuilderError("Builder error: " + name + " not found");
        }
        CLibEncapsulation lib(path);
        Type object = lib.getElement<Type>( settings);

        if (lib.failed)
            throw BuilderError("Builder error: " + lib.getError());
        return object;
    }
    private:
        libconfig::Config _cfg;
        std::string pluginPath = "./plugins/";
        void setMaterials(std::map<std::string, shared_ptr<IMaterial>> &materials, std::shared_ptr<APrimitive> primitive, const libconfig::Setting &material);
        void setColor(const libconfig::Setting &setting, std::shared_ptr<APrimitive> &primitive);
        void setTransform(const libconfig::Setting &setting, std::shared_ptr<APrimitive> &primitive);


    public:
        class BuilderError : public std::exception {
            public:
                explicit BuilderError(std::string message) : _message(std::move(message)) {};
                const char *what() const noexcept override { return _message.c_str(); };
            private:
                std::string _message;
        };
};
