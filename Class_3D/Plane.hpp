//
// Created by IvanBrekman on 28.09.2022
//

#pragma once

#include <limits>

#include "../Class_Point/Point.hpp"

#include "SceneObject.hpp"

const double D_MAX = std::numeric_limits<double>::max();
const double D_MIN = -D_MAX;

class Plane : public SceneObject {
    public:
        Vec3f m_normal;
        double  m_D;

        Vec2f m_xLimits;
        Vec2f m_yLimits;
        Vec2f m_zLimits;
    
    public:
        Plane(Vec3f normal, double D, Material material,
              Vec2f xLimits=Vec2f(D_MIN, D_MAX),
              Vec2f yLimits=Vec2f(D_MIN, D_MAX),
              Vec2f zLimits=Vec2f(D_MIN, D_MAX))
        : SceneObject(material), m_normal(normal), m_D(D), m_xLimits(xLimits), m_yLimits(yLimits), m_zLimits(zLimits) {}

        bool    intersect_ray(Vec3f rayStart, Vec3f rayDir, double& dist) override;
        Vec3f get_normal   (Vec3f intersection)                           override;
};
