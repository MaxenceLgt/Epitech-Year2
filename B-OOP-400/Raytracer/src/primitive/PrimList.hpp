/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** PrimList
*/

#pragma once

    #include <vector>
    #include <memory.h>
    #include "IPrimitive.hpp"

    #define UNUSED __attribute__((unused))

class PrimList : public IPrimitive {
    public:
        PrimList();
        PrimList(shared_ptr<IPrimitive> object);
        PrimList(const PrimList &obj);
        ~PrimList();
    public:
        void clear();
        void add(shared_ptr<IPrimitive> object);
        bool hit(const Ray &ray, Interval ray_t, HitRecord &rec) const override;
        int size() const;
    public:
        PrimList &operator=(const PrimList &obj);
    public:
        std::vector<shared_ptr<IPrimitive>> objects;
};
