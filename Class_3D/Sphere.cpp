//
// Created by IvanBrekman on 28.09.2022
//

#include <cmath>

#include "../Class_Utils/baselib.hpp"

#include "../Class_Window/Window.hpp"
#include "../Class_CoordinateSystem/CoordinateSystem.hpp"

#include "Sphere.hpp"

// ==================== Getters ====================
Vec3f Sphere::center() const {
    return m_center;
}

double Sphere::radius() const {
    return m_radius;
}
// =================================================

// ==================== Setters ====================
Sphere& Sphere::set_center(Vec3f newCenter) {
    m_center = newCenter;

    return *this;
}

Sphere& Sphere::set_radius(double newRadius) {
    m_radius        = newRadius;
    m_radiusSquare  = newRadius * newRadius;

    return *this;
}
// =================================================

// @virtual
bool Sphere::intersect_ray(Vec3f rayStart, Vec3f rayDir, double& dist) {
    Vec3f  p  = rayStart;                    // ray start point
    Vec3f  u  = rayDir.normalize();          // directional vector
    Vec3f  c  = m_center;                    // sphere center
    double r2 = m_radiusSquare;              // sphere squared radius

    double alpha      = scalarProduct(c - p, u);                // coef to nearest ray point to sphere center
    Vec3f  q          = p + u * alpha;                          //         nearest ray point to sphere center
    double minDist2   = (q - c).length_squared();               // squared min dist from ray to sphere center

    if (minDist2 > r2) {
        return false;
    }

    double beta  = sqrt(r2 - minDist2);                         // coef to intersection point
    if ((alpha > beta) || (alpha + beta > 0)) {                 // means that ray intersect sphere
        Vec3f q1 = q - u * (beta * (2 * (alpha > beta) - 1));   // nearest ray intersection point
        dist     = (q1 - p).length();                           // squared distance to sphere
        return true;
    }

    /* Means that ray intersect with sphere in NEGATIVE side of ray */

    return false;
}

// @virtual
Vec3f Sphere::get_normal(Vec3f intersection) {
    return (intersection - m_center).normalize();
}
