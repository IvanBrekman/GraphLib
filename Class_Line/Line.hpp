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
        Point2D m_endPoint;
    
    public:
        Line(Point2D start, Point2D end)
        : Drawable(), Moveable(start), m_endPoint(end) {}

        Line(double x1, double y1, double x2, double y2)
        : Line(Point2D(x1, y1), Point2D(x2, y2)) {}

        double length()  const;
        void   dump()    const;

        void draw_impl_(Window& window, const CoordinateSystem& system) override;

        void    move_to_shift_impl_(Point2D shift)                      override;
        Point2D center() const                                          override;
};
