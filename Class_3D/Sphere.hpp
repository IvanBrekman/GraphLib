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
        Vec3f  m_center;
        double   m_radius;
    
    private:
        double   m_radiusSquare__;
    
    public:
        Sphere(Vec3f center, double radius, Material material)
        : SceneObject(material), m_center(center), m_radius(radius), m_radiusSquare__(pow(radius, 2)) {}
        
        bool    intersect_ray(Vec3f rayStart, Vec3f rayDir, double& dist) override;
        Vec3f get_normal   (Vec3f intersection)                           override;
};
