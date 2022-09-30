//
// Created by IvanBrekman on 28.09.2022
//

#pragma once

#include "../Class_Point/Point.hpp"

struct Material {
    Material(Color color) : diffuse_color(color) {}
    Material() : Material(Color::Black) {}

    Color diffuse_color;
};

const Material RUBIN  (Color(155,  17,  30));
const Material EMERALD(Color( 80, 200, 120));

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
