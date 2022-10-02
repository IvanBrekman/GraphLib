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

        std::vector <Sphere*> spheres;
        std::vector <Light *> lights;
    
    private:
        PixelMap         __map;
        CoordinateSystem __system;

        const int        __FOV               = M_PI / 2;
        const int        __REFLECT_DEPTH     = 4;
        const double     __DEFAULT_DEVIATION = 1e-3;
    
    public:
        Scene(Point2D main_point, double width, double height);
        Scene(double x, double y, double width, double height)
        : Scene(Point2D(x, y), width, height) {}

        Color cast_ray         (Point3D ray_start, Point3D ray_dir, std::vector <Sphere*> spheres, std::vector <Light*> lights, int depth=0);
        bool  intersect_objects(Point3D ray_start, Point3D ray_dir, std::vector <Sphere*> spheres, Point3D& intersection, Point3D& normal, Material& material);

        void append_sphere (             Sphere*  sphere );
        void extend_spheres(std::vector <Sphere*> spheres);

        void append_light (             Light*  light );
        void extend_lights(std::vector <Light*> lights);

        void render();

        void draw_impl_(Window& window, const CoordinateSystem& system) override;
};

double  keep_in_range(double min, double max, double val);

Point3D reflect(Point3D light_dir, Point3D normal);
