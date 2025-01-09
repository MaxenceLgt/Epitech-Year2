/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** APrimitive
*/

#pragma once

    #include <utility>

#include "IPrimitive.hpp"

class APrimitive : public IPrimitive {
    public:
        APrimitive() = default;
        explicit APrimitive(shared_ptr<IMaterial> _mat) : mat(_mat) {}
        APrimitive(const APrimitive &obj) : mat(obj.mat) {}
        ~APrimitive() = default;
    public:
        shared_ptr<IMaterial> getMaterial() const {return mat;}
        void setMaterial(shared_ptr<IMaterial> _mat) {mat = _mat;};
        virtual bool hit(const Ray &ray, Interval ray_t, HitRecord &rec) const override = 0;
    public:
        APrimitive &operator=(const APrimitive &obj);
    public:
        class PrimError : public std::exception {
            public:
                PrimError(std::string msg) : _msg(msg) {};
                ~PrimError() {};
            private:
                const char *what() const noexcept override {return _msg.c_str();};
            private:
                std::string _msg;
        };
    private:
        shared_ptr<IMaterial> mat;
};
