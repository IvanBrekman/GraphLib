//
// Created by IvanBrekman on 28.09.2022
//

#include "../Class_Utils/baselib.hpp"

#include "Plane.hpp"

// ==================== Getters ====================
Vec3f Plane::normal() const {
    return m_normal;
}

double Plane::d() const {
    return m_D;
}

Vec2f Plane::x_limits() const {
    return m_xLimits;
}

Vec2f Plane::y_limits() const {
    return m_yLimits;
}

Vec2f Plane::z_limits() const {
    return m_zLimits;
}
// =================================================

// ==================== Setters ====================
Plane& Plane::set_normal(Vec3f newNormal) {
    m_normal = newNormal;

    return *this;
}

Plane& Plane::set_d(double newD) {
    m_D = newD;

    return *this;
}

Plane& Plane::set_limits(size_t coordIndex, Vec2f limit) {
    switch (coordIndex) {
        case 1:
            m_xLimits = limit;
            break;
        
        case 2:
            m_yLimits = limit;
            break;
        
        case 3:
            m_zLimits = limit;
            break;
        
        default:
            assert(0 && "Incorrect coordIndex value");
    }

    return *this;
}
// =================================================

// @virtual
bool Plane::intersect_ray(Vec3f rayStart, Vec3f rayDir, double& dist) {
    Vec3f  n = m_normal;
    double d = m_D;
    double c = scalarProduct(rayDir, n);

    if (cmpDouble(c, 0) != 0) {
        double  alpha = (d - scalarProduct(rayStart, n)) / c;
        Vec3f q       = rayStart + rayDir * alpha;

        if (
            alpha > 0 &&
            (m_xLimits.x < q.x && q.x < m_xLimits.y) &&
            (m_yLimits.x < q.y && q.y < m_yLimits.y) &&
            (m_zLimits.x < q.z && q.z < m_zLimits.y)
        ) {
            dist = alpha;
            return true;
        }
    }

    return false;
}

// @virtual
Vec3f Plane::get_normal(Vec3f _) {
    return m_normal;
}
