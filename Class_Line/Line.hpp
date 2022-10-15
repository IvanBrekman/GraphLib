//
// Created by IvanBrekman on 16.09.2022
//

#pragma once

#include "../Class_Drawable/Drawable.hpp"
#include "../Class_Moveable/Moveable.hpp"
#include "../Class_Point/Point.hpp"

// TODO color parameter

class CoordinateSystem;

class Line : public Drawable, public Moveable {
    public:
        Vec2f m_endPoint;
    
    public:
        Line(Vec2f start, Vec2f end)
        : Drawable(), Moveable(start), m_endPoint(end) {}

        Line(double x1, double y1, double x2, double y2)
        : Line(Vec2f(x1, y1), Vec2f(x2, y2)) {}

        double length()  const;
        void   dump()    const;

        void draw_impl_(Window& window, const CoordinateSystem& system) override;

        void    move_to_shift_impl_(Vec2f shift)                      override;
        Vec2f center() const                                          override;
};
