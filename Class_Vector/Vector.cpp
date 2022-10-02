//
// Created by IvanBrekman on 19.09.2022
//

#include <cmath>

#include "../Class_Utils/baselib.hpp"

#include "Vector.hpp"

Vector Vector::get_normal(Normal_Type type) const {
    Vector normal(Point2D(0, 0), Point2D(m_endPoint.y - m_mainPoint.y, m_mainPoint.x - m_endPoint.x));
    normal += m_mainPoint;

    return normal;
}

Vector Vector::operator =(const Vector& vector) {
    m_mainPoint = vector.m_mainPoint;
    m_endPoint  = vector.m_endPoint;
    m_fillColor = vector.m_fillColor;

    return vector;
}

Vector Vector::operator +=(const Point2D& point) {
    m_mainPoint += point;
    m_endPoint  += point;

    return *this;
}

Vector Vector::operator *=(double scalar) {
    m_endPoint = normalize() * scalar + m_mainPoint;

    return *this;
}

Vector Vector::operator /=(double scalar) {
    return *this *= (1 / scalar);
}

Vector Vector::operator +(const Vector& vector) const {
    Vector tmp(vector.m_mainPoint, vector.m_endPoint);
    tmp.move_to_point(m_endPoint);

    return Vector(m_mainPoint, tmp.m_endPoint);
}

Vector Vector::operator -(const Vector& vector) const {
    Vector tmp(vector.m_mainPoint, vector.m_endPoint);
    tmp.move_to_point(m_mainPoint);

    return Vector(tmp.m_endPoint, m_endPoint);
}

Vector Vector::operator *(double scalar) const {
    Vector mult = *this;
    return mult *= scalar;
}

Vector Vector::operator /(double scalar) const  {
    return *this * (1 / scalar);
}

Vector Vector::operator -() const {
    return Vector(m_mainPoint, -normalize() + m_mainPoint);
}

Line Vector::to_line() const {
    return Line(m_mainPoint, m_endPoint);
}

Point2D Vector::normalize() const {
    return m_endPoint - m_mainPoint;
}

void Vector::resize(double new_size) {
    if (m_hidden) return;

    *this *= new_size / length();
}

void Vector::rotate(double angle) {
    if (m_hidden) return;
    
    Point2D oldStart        = m_mainPoint;
    Point2D directionVector = normalize();

    angle = angle - 360 * (int)(angle / 360);

    double radians = angle * M_PI / 180;

    double newX = directionVector.x * cos(radians) - directionVector.y * sin(radians);
    double newY = directionVector.x * sin(radians) + directionVector.y * cos(radians);

    m_mainPoint = Point2D(0, 0);
    m_endPoint  = Point2D(newX, newY);

    move_to_point(oldStart);
}

void Vector::dump() const {
    printf("<Vector: (%.3lf, %.3lf) -> (%.3lf, %.3lf) >\n", m_mainPoint.x, m_mainPoint.y, m_endPoint.x, m_endPoint.y);
}

// @virtual
void Vector::draw_impl_(Window& window, const CoordinateSystem& system) {
    Line::draw_impl_(window, system);

    Vector normalVector = Vector::get_normal(Vector::Normal_Type::LEFT_NORMAL);

    Line lArrow = Vector(( normalVector * m_DRAW_NORMAL_COEF__ - *this) * m_DRAW_ARROW_COEF__).to_line();
    Line rArrow = Vector((-normalVector * m_DRAW_NORMAL_COEF__ - *this) * m_DRAW_ARROW_COEF__).to_line();

    lArrow.set_fill_color(m_fillColor);
    rArrow.set_fill_color(m_fillColor);

    lArrow.draw(window, system);
    rArrow.draw_impl_(window, system);
}

// @virtual
void Vector::move_to_shift_impl_(Point2D shift) {
    if (m_hidden) return;
    
    Point2D baseShift = normalize();

    m_mainPoint += shift;
    m_endPoint   = m_mainPoint + baseShift;
}
