//
// Created by IvanBrekman on 28.09.2022
//

#pragma once

#include "../Class_Point/Point.hpp"

struct Material {
    Material(Point3D albedo, Color color, double spec_exp)
    : albedo(albedo), diffuse_color(color), specular_exp(spec_exp) {}
    
    Material()
    : Material(Point3D(1, 0, 0), Color::Black, 100.0) {}

    Color   diffuse_color;
    double  specular_exp;
    Point3D albedo;
};

const Material RUBIN  (Point3D(0.9,  0.1, 0.0), Color( 76.5,  25.5,  25.5),   10.0);
const Material EMERALD(Point3D(0.6,  0.3, 0.1), Color(102.0, 102.0,  76.5),   50.0);
const Material MIRROR (Point3D(0.0, 10.0, 0.8), Color(255.0, 255.0, 255.0), 1425.0);

class Window;
class CoordinateSystem;

class Sphere {
    public:
        Point3D  center;
        double   radius;

        Material material;
    
    private:
        double   __radius_square;
    
    public:
        Sphere(Point3D center, double radius, Material material);

        bool intersect_ray(Point3D ray_start, Point3D ray_dir, double& dist);
};
