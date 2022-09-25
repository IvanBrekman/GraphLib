//
// Created by IvanBrekman on 19.09.2022
//

#pragma once

#include <SFML/Graphics.hpp>

class Point2D {
    public:
        double x;
        double y;
    
    public:
        Point2D(double x, double y) : x(x), y(y) {}

        Point2D operator +=(const Point2D& point);
        Point2D operator -=(const Point2D& point);
        Point2D operator *=(double scalar);

        Point2D operator +(const Point2D& point)    const;
        Point2D operator -(const Point2D& point)    const;
        Point2D operator *(double scalar)           const;
        Point2D operator -()                        const;

        sf::Vector2f to_sfml_vector()               const;

        void dump() const;
};
