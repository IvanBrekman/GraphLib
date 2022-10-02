//
// Created by IvanBrekman on 19.09.2022
//

#include <cmath>

#include "../Class_Utils/baselib.hpp"

#include "Vector.hpp"

Vector Vector::get_normal(Normal_Type type) const {
    Vector normal(Point2D(0, 0), Point2D(this->end_point.y - this->m_mainPoint.y, this->m_mainPoint.x - this->end_point.x));
    normal += this->m_mainPoint;

    return normal;
}

Vector Vector::operator =(const Vector& vector) {
    this->m_mainPoint = vector.m_mainPoint;
    this->end_point  = vector.end_point;
    this->m_fillColor = vector.m_fillColor;

    return vector;
}

Vector Vector::operator +=(const Point2D& point) {
    this->m_mainPoint += point;
    this->end_point  += point;

    return *this;
}

Vector Vector::operator *=(double scalar) {
    this->end_point = this->normalize() * scalar + this->m_mainPoint;

    return *this;
}

Vector Vector::operator /=(double scalar) {
    return *this *= (1 / scalar);
}

Vector Vector::operator +(const Vector& vector) const {
    Vector tmp(vector.m_mainPoint, vector.end_point);
    tmp.move_to_point(this->end_point);

    return Vector(this->m_mainPoint, tmp.end_point);
}

Vector Vector::operator -(const Vector& vector) const {
    Vector tmp(vector.m_mainPoint, vector.end_point);
    tmp.move_to_point(this->m_mainPoint);

    return Vector(tmp.end_point, this->end_point);
}

Vector Vector::operator *(double scalar) const {
    Vector mult = *this;
    return mult *= scalar;
}

Vector Vector::operator /(double scalar) const  {
    return *this * (1 / scalar);
}

Vector Vector::operator -() const {
    return Vector(this->m_mainPoint, -this->normalize() + this->m_mainPoint);
}

Line Vector::to_line() const {
    return Line(this->m_mainPoint, this->end_point);
}

Point2D Vector::normalize() const {
    return this->end_point - this->m_mainPoint;
}

void Vector::resize(double new_size) {
    if (this->m_hidden) return;

    *this *= new_size / this->length();
}

void Vector::rotate(double angle) {
    if (this->m_hidden) return;
    
    Point2D old_start        = this->m_mainPoint;
    Point2D direction_vector = this->normalize();

    angle = angle - 360 * (int)(angle / 360);

    double radians = angle * M_PI / 180;

    double new_x = direction_vector.x * cos(radians) - direction_vector.y * sin(radians);
    double new_y = direction_vector.x * sin(radians) + direction_vector.y * cos(radians);

    this->m_mainPoint = Point2D(0, 0);
    this->end_point  = Point2D(new_x, new_y);

    this->move_to_point(old_start);
}

void Vector::dump() const {
    printf("<Vector: (%.3lf, %.3lf) -> (%.3lf, %.3lf) >\n", this->m_mainPoint.x, this->m_mainPoint.y, this->end_point.x, this->end_point.y);
}

void Vector::draw_impl_(Window& window, const CoordinateSystem& system) {
    Line::draw_impl_(window, system);

    Vector normal_vector = Vector::get_normal(Vector::Normal_Type::LEFT_NORMAL);

    Line l_arrow = Vector(( normal_vector * this->__DRAW_NORMAL_COEF - *this) * this->__DRAW_ARROW_COEF).to_line();
    Line r_arrow = Vector((-normal_vector * this->__DRAW_NORMAL_COEF - *this) * this->__DRAW_ARROW_COEF).to_line();

    l_arrow.set_fill_color(this->m_fillColor);
    r_arrow.set_fill_color(this->m_fillColor);

    l_arrow.draw(window, system);
    r_arrow.draw_impl_(window, system);
}

void Vector::move_to_shift_impl_(Point2D shift) {
    if (this->m_hidden) return;
    
    Point2D base_shift = this->normalize();

    this->m_mainPoint += shift;
    this->end_point   = this->m_mainPoint + base_shift;
}
