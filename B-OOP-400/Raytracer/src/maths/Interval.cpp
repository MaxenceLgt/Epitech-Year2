/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Interval
*/

#include "Interval.hpp"

Interval::Interval() : min(+infinity), max(-infinity)
{

}

Interval::Interval(double min, double max) : min(min), max(max)
{

}

Interval::~Interval()
{

}

double Interval::size() const
{
    return this->max - this->min;
}

bool Interval::contains(double x) const
{
    return this->min <= x && x <= this->max;
}

bool Interval::surrounds(double x) const
{
    return this->min < x && x < this->max;
}

double Interval::clamp(double x) const
{
    if (x < this->min)
        return this->min;
    if (x > this->max)
        return this->max;
    return x;
}
