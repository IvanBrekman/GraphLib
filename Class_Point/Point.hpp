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
        Point2D(double x, double y)
        : x(x), y(y) {}

        Point2D operator +=(const Point2D& point);
        Point2D operator -=(const Point2D& point);
        Point2D operator *=(double scalar);

        Point2D operator +(const Point2D& point)    const;
        Point2D operator -(const Point2D& point)    const;
        Point2D operator *(double scalar)           const;
        Point2D operator -()                        const;

        sf::Vector2f to_sfml_vector()               const;

        void dump()                                 const;
};

class Point3D {
    public:
        double x;
        double y;
        double z;
    
    public:
        Point3D(double x, double y, double z)
        : x(x), y(y), z(z) {}

        Point3D operator +=(const Point3D& point);
        Point3D operator -=(const Point3D& point);
        Point3D operator *=(double scalar);

        Point3D operator +(const Point3D& point)    const;
        Point3D operator -(const Point3D& point)    const;
        Point3D operator *(double scalar)           const;
        Point3D operator -()                        const;

        static double scalar_product(const Point3D& v1, const Point3D& v2);
        double  length_square()                     const;
        double  length()                            const;
        Point3D normalize()                         const;

        sf::Vector3f to_sfml_vector()               const;

        void dump()                                 const;
};
