/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** PrimList
*/

#include "PrimList.hpp"

PrimList::PrimList()
{
}

PrimList::PrimList(const PrimList &obj)
{
    this->objects = obj.objects;
}

PrimList::PrimList(shared_ptr<IPrimitive> object)
{
    this->add(object);
}

PrimList::~PrimList()
{
}

void PrimList::clear()
{
    this->objects.clear();
}

void PrimList::add(shared_ptr<IPrimitive> object)
{
    this->objects.push_back(object);
}

bool PrimList::hit(const Ray &ray, Interval ray_t, HitRecord &rec) const
{
    HitRecord temp_rec;
    bool hit_anything = false;
    auto closest_so_far = ray_t.max;

    for (const auto& object : this->objects) {
        if (object->hit(ray, Interval(ray_t.min, closest_so_far), temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}

int PrimList::size() const
{
    return this->objects.size();
}

PrimList &PrimList::operator=(const PrimList &obj)
{
    if (this == &obj)
        return *this;
    
    this->objects = obj.objects;
    return *this;
}
