//
// Created by IvanBrekman on 19.09.2022
//

#pragma once

#include "../Class_Vector/Vector.hpp"
#include "../Class_Point/Point.hpp"

class CoordinateSystem : public Drawable {

    public:
        enum AxisX_Direction {
            RIGHT   =  1,
            LEFT    = -1
        };
        enum AxisY_Direction {
            UP      = -1,
            DOWN    =  1
        };
        enum Type {
            CENTER      = 0,
            LEFT_UP     = 1,
            LEFT_BOTTOM = 2
        };

        Vec2f m_center;
        bool    m_showAxis;

        AxisX_Direction m_axisXDirection;
        AxisY_Direction m_axisYDirection;

        std::vector <Drawable*> m_objects = std::vector <Drawable*>();

        static const int LAST_INDEX       = -1;
    
    private:
        Vector m_axisX__;
        Vector m_axisY__;

        static const int DRAW_AXIS_LENGTH__ = 100;
    
    public:
        CoordinateSystem()
        : CoordinateSystem(0, 0) {}

        CoordinateSystem(Vec2f center,     AxisY_Direction dirY=AxisY_Direction::DOWN, AxisX_Direction dirX=AxisX_Direction::RIGHT);
        CoordinateSystem(double x, double y, AxisY_Direction dirY=AxisY_Direction::DOWN, AxisX_Direction dirX=AxisX_Direction::RIGHT)
        : CoordinateSystem(Vec2f(x, y), dirY, dirX) {};

        Vec2f point_to_pixel(Vec2f point)   const;
        Vec2f pixel_to_point(Vec2f pixel)   const;

        static CoordinateSystem get_system_by_type(Type type, double width, double height);

        void set_show_axis(bool showAxisVal);
        void draw_axis(Window& window);

        void append_object (Drawable*               object,  int index=CoordinateSystem::LAST_INDEX);
        void extend_objects(std::vector <Drawable*> objects, int index=CoordinateSystem::LAST_INDEX);

        void dump()                             const;

        void set_hidden(bool hidden)                                    override;

    private:
        void draw_impl_(Window& window, const CoordinateSystem& system) override;
};
