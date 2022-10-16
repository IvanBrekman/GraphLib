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
        Sphere(Vec3f center, double radius, Material material)
        : SceneObject(material), m_center(center), m_radius(radius), m_radiusSquare(pow(radius, 2)) {}

        // ==================== Getters ====================
        Vec3f  center() const;
        double radius() const;
        // =================================================

        // ==================== Setters ====================
        Sphere& set_center(Vec3f  newCenter);
        Sphere& set_radius(double newRadius);
        // =================================================
        
        bool  intersect_ray(Vec3f rayStart, Vec3f rayDir, double& dist) override;
        Vec3f get_normal   (Vec3f intersection)                         override;
    
    private:
        Vec3f  m_center;
        double m_radius;
        double m_radiusSquare;
    
};
