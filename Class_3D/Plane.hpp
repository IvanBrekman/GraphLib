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
        Plane(Vec3f normal, double D, Material material,
              Vec2f xLimits=Vec2f(D_MIN, D_MAX),
              Vec2f yLimits=Vec2f(D_MIN, D_MAX),
              Vec2f zLimits=Vec2f(D_MIN, D_MAX))
        : SceneObject(material), m_normal(normal), m_D(D), m_xLimits(xLimits), m_yLimits(yLimits), m_zLimits(zLimits) {}

        // ==================== Getters ====================
        Vec3f  normal()   const;
        double d()        const;

        Vec2f  x_limits() const;
        Vec2f  y_limits() const;
        Vec2f  z_limits() const;
        // =================================================

        // ==================== Setters ====================
        Plane& set_normal(Vec3f  newNormal);
        Plane& set_d     (double newD);

        Plane& set_limits(size_t coordIndex, Vec2f limit);
        // =================================================

        bool  intersect_ray(Vec3f rayStart, Vec3f rayDir, double& dist) override;
        Vec3f get_normal   (Vec3f intersection)                         override;

    private:
        Vec3f  m_normal;
        double m_D;

        Vec2f  m_xLimits;
        Vec2f  m_yLimits;
        Vec2f  m_zLimits;
};
