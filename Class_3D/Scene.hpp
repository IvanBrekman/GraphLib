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
        Scene(Vec2f mainPoint,    double width, double height, const char* backImgPath=nullptr);
        Scene(double x, double y, double width, double height, const char* backImgPath=nullptr)
        : Scene(Vec2f(x, y), width, height, backImgPath) {}

        ~Scene();

        Color cast_ray         (Vec3f rayStart, Vec3f rayDir, int x, int y, int depth=0);
        bool  intersect_objects(Vec3f rayStart, Vec3f rayDir, Vec3f& intersection, Vec3f& normal, Material& material);

        void append_scene_object (             SceneObject*  object );
        void extend_scene_objects(std::vector <SceneObject*> objects);

        void append_light (             Light*  light );
        void extend_lights(std::vector <Light*> lights);

        void render();

        // ==================== Getters ====================
        double width()  const;
        double height() const;

        PixelMap background() const;

        std::vector<SceneObject*> objects() const;
        std::vector<Light      *> lights () const;
        // =================================================

        // ==================== Setters ====================
        Scene& set_background(PixelMap newBack);
        Scene& set_objects(std::vector<SceneObject*> newObjects);
        Scene& set_lights (std::vector<Light      *> newLights);
        // =================================================

        void draw_impl_(Window& window, const CoordinateSystem& system) override;
        Vec2f center() const                                            override;
    
    private:
        double m_width;
        double m_height;

        PixelMap m_background;

        std::vector<SceneObject*> m_objects;
        std::vector<Light      *> m_lights;

        PixelMap         m_map;
        CoordinateSystem m_system;

        const int        REFLECT_DEPTH      = 4;
        const double     FOV                = M_PI / 3;
        const double     DEFAULT_DEVIATION  = 1e-3;
        const Color      DEFAULT_BACK_COLOR = Color(51, 178, 204);
};

Vec3f reflect(Vec3f lightDir, Vec3f normal);
