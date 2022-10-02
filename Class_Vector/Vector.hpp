//
// Created by IvanBrekman on 19.09.2022
//

#pragma once

#include "../Class_Line/Line.hpp"
#include "../Class_Point/Point.hpp"

// TODO color parameter

class Vector : public Line {
    public:
        enum Normal_Type {
            LEFT_NORMAL  =  1,
            RIGHT_NORMAL = -1
        };
    
    private:
        const double __DRAW_NORMAL_COEF = 0.2;
        const double __DRAW_ARROW_COEF  = 0.15;

    public:
        Vector()
        : Line(0, 0, 0, 0) {};
        
        Vector(double x1, double y1, double x2, double y2)
        : Line(x1, y1, x2, y2) {}

        Vector(Point2D start, Point2D end)
        : Vector(start.x, start.y, end.x, end.y) {}

        Vector get_normal(Normal_Type type)     const;

        Vector operator  =(const Vector&  vector);
        Vector operator +=(const Point2D& point);
        Vector operator *=(double scalar);
        Vector operator /=(double scalar);

        Vector operator +(const Vector& vector) const;
        Vector operator -(const Vector& vector) const;
        Vector operator *(double scalar)        const;
        Vector operator /(double scalar)        const;
        Vector operator -()                     const;

        Line    to_line()                       const;

        Point2D normalize()                     const;

        void resize(double new_size);
        void rotate(double angle);
        void dump()                             const;
        
        void draw_impl_(Window& window, const CoordinateSystem& system) override;

        void move_to_shift_impl_(Point2D shift)                         override;
};
