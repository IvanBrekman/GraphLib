//
// Created by IvanBrekman on 16.09.2022
//

#pragma once

#include <SFML/Graphics.hpp>

#include "../Class_Drawable/Drawable.hpp"
#include "../Class_Point/Point.hpp"

class CoordinateSystem;

class Line : public Drawable {
    public:
        Point2D start;
        Point2D end;

        Line(double x1, double y1, double x2, double y2)
        : start(x1, y1), end(x2, y2), Drawable() {};

        Line(Point2D start, Point2D end)
        : Line(start.x, start.y, end.x, end.y) {}

        double length() const;

        void draw(Window& window, const CoordinateSystem& system) override;

        void dump()     const;

};
