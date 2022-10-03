//
// Created by IvanBrekman on 28.09.2022
//

#include "../Class_Utils/baselib.hpp"

#include "Plane.hpp"

// @virtual
bool Plane::intersect_ray(Point3D rayStart, Point3D rayDir, double& dist) {
    Point3D n = m_normal;
    double  d = m_D;
    double  c = Point3D::scalar_product(rayDir, n);

    if (cmpDouble(c, 0) != 0) {
        double  alpha = (d - Point3D::scalar_product(rayStart, n)) / c;
        Point3D q     = rayStart + rayDir * alpha;

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
Point3D Plane::get_normal(Point3D _) {
    return m_normal;
}
