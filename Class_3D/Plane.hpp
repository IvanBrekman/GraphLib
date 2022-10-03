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
        Point3D m_normal;
        double  m_D;

        Point2D m_xLimits;
        Point2D m_yLimits;
        Point2D m_zLimits;
    
    public:
        Plane(Point3D normal, double D, Material material,
              Point2D xLimits=Point2D(D_MIN, D_MAX),
              Point2D yLimits=Point2D(D_MIN, D_MAX),
              Point2D zLimits=Point2D(D_MIN, D_MAX))
        : SceneObject(material), m_normal(normal), m_D(D), m_xLimits(xLimits), m_yLimits(yLimits), m_zLimits(zLimits) {}

        bool    intersect_ray(Point3D rayStart, Point3D rayDir, double& dist) override;
        Point3D get_normal   (Point3D intersection)                           override;
};
