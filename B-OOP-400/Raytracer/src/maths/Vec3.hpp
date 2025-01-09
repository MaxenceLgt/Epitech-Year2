/*
** EPITECH PROJECT, 2024
** B-OOP-400-REN-4-1-raytracer-maxence.largeot [WSL: Ubuntu]
** File description:
** Vec3
*/

#pragma once

#include "Utils.hpp"
#include <libconfig.h++>

class Vec3 {
    public:
        Vec3();
        Vec3(double e0, double e1, double e2);
        ~Vec3();
    public:
        double x() const;
        double y() const;
        double z() const;
        double length() const;
        double length_squared() const;
        bool near_zero() const;
        static Vec3 parseVec3(const libconfig::Setting &setting);
        void reset();
        static double getValue(const libconfig::Setting &setting, std::string name);
    public:
        Vec3 operator-() const;
        double operator[](int i) const;
        double& operator[](int i);
        Vec3& operator+=(const Vec3& v);
        Vec3& operator*=(double t);
        Vec3& operator/=(double t);
    public:
        static Vec3 random() {
            return Vec3(Utils::random_double(), Utils::random_double(), Utils::random_double());
        };
        static Vec3 random(double min, double max) {
            return Vec3(Utils::random_double(min,max), Utils::random_double(min,max), Utils::random_double(min,max));
        };
    public:
        double e[3];
};

// point3 is just an alias for Vec3, but useful for geometric clarity in the code.
using Point3 = Vec3;

// Vector Utility Functions

inline std::ostream& operator<<(std::ostream& out, const Vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline Vec3 operator+(const Vec3& u, const Vec3& v) {
    return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline Vec3 operator-(const Vec3& u, const Vec3& v) {
    return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline Vec3 operator*(const Vec3& u, const Vec3& v) {
    return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline Vec3 operator*(double t, const Vec3& v) {
    return Vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline Vec3 operator*(const Vec3& v, double t) {
    return t * v;
}

inline Vec3 operator/(const Vec3& v, double t) {
    return (1/t) * v;
}

inline double dot(const Vec3& u, const Vec3& v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

inline Vec3 cross(const Vec3& u, const Vec3& v) {
    return Vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline Vec3 unit_vector(const Vec3& v) {
    return v / v.length();
}

inline Vec3 random_in_unit_sphere() {
    while (true) {
        auto p = Vec3::random(-1,1);
        if (p.length_squared() < 1)
            return p;
    }
}

inline Vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

inline Vec3 random_on_hemisphere(const Vec3& normal) {
    Vec3 on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return on_unit_sphere;
    else
        return -on_unit_sphere;
}

inline Vec3 reflect(const Vec3& v, const Vec3& n) {
    return v - 2*dot(v,n)*n;
}

inline Vec3 refract(const Vec3& uv, const Vec3& n, double etai_over_etat) {
    auto cos_theta = fmin(dot(-uv, n), 1.0);
    Vec3 r_out_perp =  etai_over_etat * (uv + cos_theta*n);
    Vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}

inline Vec3 random_in_unit_disk() {
    while (true) {
        auto p = Vec3(Utils::random_double(-1,1), Utils::random_double(-1,1), 0);
        if (p.length_squared() < 1)
            return p;
    }
}
