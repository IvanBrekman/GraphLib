//
// Created by IvanBrekman on 28.09.2022
//

#pragma once

#include <cmath>

#include "../Class_Point/Point.hpp"

#include "SceneObject.hpp"

class Window;
class CoordinateSystem;

class Sphere : public SceneObject {
    public:
        Point3D  m_center;
        double   m_radius;
    
    private:
        double   m_radiusSquare__;
    
    public:
        Sphere(Point3D center, double radius, Material material)
        : SceneObject(material), m_center(center), m_radius(radius), m_radiusSquare__(pow(radius, 2)) {}
        
        bool    intersect_ray(Point3D rayStart, Point3D rayDir, double& dist) override;
        Point3D get_normal   (Point3D intersection)                           override;
};
