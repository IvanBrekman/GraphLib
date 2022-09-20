//
// Created by IvanBrekman on 19.09.2022
//

#pragma once

#include "../Class_Vector/Vector.hpp"
#include "../Class_Point/Point.hpp"

class CoordinateSystem : public Drawable {
    friend class Window;

    public:
        enum AxisX_Direction {
            RIGHT   =  1,
            LEFT    = -1
        };
        enum AxisY_Direction {
            UP      = -1,
            DOWN    =  1
        };

        Point2D center;

        AxisX_Direction axis_x_direction;
        AxisY_Direction axis_y_direction;

        std::vector <Drawable*> objects = std::vector <Drawable*>();

    
    private:
        Vector __axis_x;
        Vector __axis_y;

        static const int __LAST_INDEX       = -1;
        static const int __DRAW_AXIS_LENGTH = 100;
    
    public:
        CoordinateSystem()
        : CoordinateSystem(0, 0) {}

        CoordinateSystem(Point2D center,     AxisY_Direction diry=AxisY_Direction::DOWN, AxisX_Direction dirx=AxisX_Direction::RIGHT);
        CoordinateSystem(double x, double y, AxisY_Direction diry=AxisY_Direction::DOWN, AxisX_Direction dirx=AxisX_Direction::RIGHT)
        : CoordinateSystem(Point2D(x, y), diry, dirx) {};

        Point2D point_to_pixel(Point2D point)   const;


        void append_object (Drawable*               object,  int index=CoordinateSystem::__LAST_INDEX);
        void extend_objects(std::vector <Drawable*> objects, int index=CoordinateSystem::__LAST_INDEX);

        void draw_on_window    (Window& window);
        void draw_added_objects(Window& window);

        void dump()                             const;

    private:
        void draw(Window& window, const CoordinateSystem& system) override;
};
