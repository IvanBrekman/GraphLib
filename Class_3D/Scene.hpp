//
// Created by IvanBrekman on 28.09.2022
//

#pragma once

#include <cmath>

#include "../Class_Drawable/Drawable.hpp"
#include "../Class_Moveable/Moveable.hpp"
#include "../Class_PixelMap/PixelMap.hpp"
#include "../Class_CoordinateSystem/CoordinateSystem.hpp"

#include "Sphere.hpp"
#include "Light.hpp"

class Window;

class Scene : public Drawable, public Moveable {
    public:
        double width;
        double height;

        Color  background = Color(51, 178, 204);
    
    private:
        PixelMap         __map;
        CoordinateSystem __system;

        const int        __fov = M_PI / 2;
    
    public:
        Scene(Point2D main_point, double width, double height);
        Scene(double x, double y, double width, double height)
        : Scene(Point2D(x, y), width, height) {}

        Color cast_ray         (Point3D ray_start, Point3D ray_dir, std::vector <Sphere*> spheres, std::vector <Light*> lights);
        bool  intersect_objects(Point3D ray_start, Point3D ray_dir, std::vector <Sphere*> spheres, Point3D& intersection, Point3D& normal, Material& material);

        void render();

        void draw(Window& window, const CoordinateSystem& system) override;
};

double keep_in_range(double min, double max, double val);
