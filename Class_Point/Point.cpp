//
// Created by IvanBrekman on 19.09.2022
//

#include <cstdio>
#include <cmath>

#include "Point.hpp"

// ======================================== Point2D ========================================
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
// =========================================================================================

// ======================================== Point3D ========================================
Point3D Point3D::operator +=(const Point3D& point) {
    this->x += point.x;
    this->y += point.y;
    this->z += point.z;

    return *this;
}

Point3D Point3D::operator -=(const Point3D& point) {
    return *this += -(Point3D)point;
}

Point3D Point3D::operator *=(double scalar) {
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;

    return *this;
}

Point3D Point3D::operator +(const Point3D& point) const {
    Point3D new_point = *this;
    return new_point += point;
}

Point3D Point3D::operator -(const Point3D& point) const {
    return *this + -point;
}

Point3D Point3D::operator *(double scalar) const {
    return Point3D(this->x, this->y, this->z) *= scalar;
}

Point3D Point3D::operator -() const {
    return Point3D(-this->x, -this->y, -this->z);
}

double Point3D::scalar_product(const Point3D& v1, const Point3D& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

double Point3D::length_square() const {
    return pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2);
}

double Point3D::length() const {
    return sqrt(this->length_square());
}

Point3D Point3D::normalize() const {
    return *this * (1 / this->length());
}

sf::Vector3f Point3D::to_sfml_vector() const {
    return sf::Vector3f(this->x, this->y, this->z);
}

void Point3D::dump() const {
    printf("<Point3D: (%.3lf, %.3lf, %.3lf) >\n", this->x, this->y, this->z);
}
// =========================================================================================
