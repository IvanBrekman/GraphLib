//
// Created by IvanBrekman on 28.09.2022
//

#pragma once

#include <cmath>

#include "../Class_Drawable/Drawable.hpp"
#include "../Class_Moveable/Moveable.hpp"
#include "../Class_PixelMap/PixelMap.hpp"
#include "../Class_CoordinateSystem/CoordinateSystem.hpp"

#include "SceneObject.hpp"
#include "Light.hpp"

class Window;

class Scene : public Drawable, public Moveable {
    public:
        double m_width;
        double m_height;

        Color  m_background = Color(51, 178, 204);

        std::vector <SceneObject*> m_objects;
        std::vector <Light      *> m_lights;
    
    private:
        PixelMap         m_map__;
        CoordinateSystem m_system__;

        const int        REFLECT_DEPTH__     = 4;
        const double     FOV__               = M_PI / 3;
        const double     DEFAULT_DEVIATION__ = 1e-3;
    
    public:
        Scene(Point2D mainPoint,  double width, double height);
        Scene(double x, double y, double width, double height)
        : Scene(Point2D(x, y), width, height) {}

        Color cast_ray         (Point3D rayStart, Point3D rayDir, int depth=0);
        bool  intersect_objects(Point3D rayStart, Point3D rayDir, Point3D& intersection, Point3D& normal, Material& material);

        void append_scene_object (             SceneObject*  object );
        void extend_scene_objects(std::vector <SceneObject*> objects);

        void append_light (             Light*  light );
        void extend_lights(std::vector <Light*> lights);

        void render();

        void draw_impl_(Window& window, const CoordinateSystem& system) override;
        Point2D center() const                                          override;
};

Point3D reflect(Point3D lightDir, Point3D normal);
