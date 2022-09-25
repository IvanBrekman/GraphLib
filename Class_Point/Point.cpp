//
// Created by IvanBrekman on 19.09.2022
//

#include <cstdio>

#include "Point.hpp"

Point2D Point2D::operator +=(const Point2D& point) {
    this->x += point.x;
    this->y += point.y;

    return *this;
}

Point2D Point2D::operator -=(const Point2D& point) {
    return *this += -(Point2D)point;
}

Point2D Point2D::operator *=(double scalar) {
    this->x *= scalar;
    this->y *= scalar;

    return *this;
}

Point2D Point2D::operator +(const Point2D& point) const {
    Point2D new_point = *this;
    return new_point += point;
}

Point2D Point2D::operator -(const Point2D& point) const {
    return *this + -point;
}

Point2D Point2D::operator *(double scalar) const {
    return Point2D(this->x, this->y) *= scalar;
}

Point2D Point2D::operator -() const {
    return Point2D(-this->x, -this->y);
}

sf::Vector2f Point2D::to_sfml_vector() const {
    return sf::Vector2f(this->x, this->y);
}

void Point2D::dump() const {
    printf("<Point2D: (%.3lf, %.3lf) >\n", this->x, this->y);
}
