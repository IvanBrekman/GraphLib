//
// Created by IvanBrekman on 28.09.2022
//

#include <cmath>

#include "../Class_Utils/baselib.hpp"

#include "../Class_Window/Window.hpp"
#include "../Class_CoordinateSystem/CoordinateSystem.hpp"

#include "Sphere.hpp"

Sphere::Sphere(Point3D center, double radius, Material material)
: center(center), radius(radius), material(material), __radius_square(pow(radius, 2)) {
}

bool Sphere::intersect_ray(Point3D ray_start, Point3D ray_dir, double& dist) {
    Point3D p  = ray_start;             // ray start point
    Point3D u  = ray_dir.normalize();   // directional vector
    Point3D c  = this->center;          // sphere center
    double  r2 = this->__radius_square; // sphere squared radius

    double alpha      = Point3D::scalar_product(c - p, u);      // coef to nearest ray point to sphere center
    Point3D q         = p + u * alpha;                          //         nearest ray point to sphere center
    double min_dist2  = (q - c).length_square();                // squared min dist from ray to sphere center

    if (min_dist2 > r2) {
        return false;
    }

    double beta  = sqrt(r2 - min_dist2);                        // coef to intersection point
    if ((alpha > beta) || (alpha + beta > 0)) {                 // means that ray intersect sphere
        Point3D q1 = q - u * (beta * (2 * (alpha > beta) - 1)); // nearest ray intersection point
        dist       = (q1 - p).length();                         // squared distance to sphere
        return true;
    }

    /* Means that ray intersect with sphere in NEGATIVE side of ray */

    return false;
}
