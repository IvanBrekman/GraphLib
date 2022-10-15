//
// Created by IvanBrekman on 28.09.2022
//

#include "../Class_Utils/baselib.hpp"

#include "Plane.hpp"

// @virtual
bool Plane::intersect_ray(Vec3f rayStart, Vec3f rayDir, double& dist) {
    Vec3f n = m_normal;
    double  d = m_D;
    double  c = scalarProduct(rayDir, n);

    if (cmpDouble(c, 0) != 0) {
        double  alpha = (d - scalarProduct(rayStart, n)) / c;
        Vec3f q     = rayStart + rayDir * alpha;

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
