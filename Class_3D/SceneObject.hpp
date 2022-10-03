//
// Created by IvanBrekman on 28.09.2022
//

#pragma once

#include "../Class_Point/Point.hpp"
#include "../Class_Color/Color.hpp"

struct Material {
    Material(Point3D albedo, Color color, double specExp)
    : albedo(albedo), diffuseColor(color), specularExp(specExp) {}
    
    Material()
    : Material(Point3D(1, 0, 0), Color::Black, 100.0) {}

    Color   diffuseColor;
    double  specularExp;
    Point3D albedo;
};

const Material RUBIN  (Point3D(0.9,  0.1, 0.0), Color( 76.5,  25.5,  25.5),   10.0);
const Material EMERALD(Point3D(0.6,  0.3, 0.1), Color(102.0, 102.0,  76.5),   50.0);
const Material MIRROR (Point3D(0.0, 10.0, 0.8), Color(255.0, 255.0, 255.0), 1425.0);

class SceneObject {
    public:
        Material m_material;

    public:
        SceneObject() {}
        SceneObject(Material material)
        : m_material(material) {}

        virtual bool    intersect_ray(Point3D rayStart, Point3D rayDir, double& dist) = 0;
        virtual Point3D get_normal   (Point3D intersection) = 0;
};
