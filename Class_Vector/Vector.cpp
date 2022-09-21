//
// Created by IvanBrekman on 19.09.2022
//

#include <cmath>

#include "../Class_Utils/baselib.hpp"
#include "Vector.hpp"

Vector Vector::get_normal(Normal_Type type) const {
    Vector normal(Point2D(0, 0), Point2D(this->end.y - this->start.y, this->start.x - this->end.x));
    normal += this->start;

    return normal;
}

Vector Vector::operator =(const Vector& vector) {
    this->start = vector.start;
    this->end   = vector.end;
    this->color = vector.color;

    return vector;
}

Vector Vector::operator +=(const Point2D& point) {
    this->start += point;
    this->end   += point;

    return *this;
}

Vector Vector::operator *=(double scalar) {
    this->end = this->normalize() * scalar + this->start;

    return *this;
}

Vector Vector::operator /=(double scalar) {
    return *this *= (1 / scalar);
}

Vector Vector::operator +(const Vector& vector) const {
    Vector tmp(vector.start, vector.end);
    tmp.move_to(this->end);

    return Vector(this->start, tmp.end);
}

Vector Vector::operator -(const Vector& vector) const {
    Vector tmp(vector.start, vector.end);
    tmp.move_to(this->start);

    return Vector(tmp.end, this->end);
}

Vector Vector::operator *(double scalar) const {
    Vector mult = *this;
    return mult *= scalar;
}

Vector Vector::operator /(double scalar) const  {
    return *this * (1 / scalar);
}

Vector Vector::operator -() const {
    return Vector(this->start, -this->normalize() + this->start);
}

Line Vector::to_line() const {
    return Line(this->start, this->end);
}

Point2D Vector::normalize() const {
    return this->end - this->start;
}

void Vector::move_to(Point2D new_start) {
    Point2D shift = this->normalize();

    this->start = new_start;
    this->end   = new_start + shift;
}

void Vector::resize(double new_size) {
    *this *= new_size / this->length();
}

void Vector::rotate(double angle) {
    Point2D old_start        = this->start;
    Point2D direction_vector = this->normalize();

    angle = angle - 360 * (int)(angle / 360);

    double radians = angle * M_PI / 180;

    double new_x = direction_vector.x * cos(radians) - direction_vector.y * sin(radians);
    double new_y = direction_vector.x * sin(radians) + direction_vector.y * cos(radians);

    this->start = Point2D(0, 0);
    this->end   = Point2D(new_x, new_y);

    this->move_to(old_start);
}

void Vector::draw(Window& window, const CoordinateSystem& system) {
    if (this->hidden) return;

    Line::draw(window, system);

    Vector normal_vector = Vector::get_normal(Vector::Normal_Type::LEFT_NORMAL);

    Line l_arrow = Vector(( normal_vector * this->__DRAW_NORMAL_COEF - *this) * this->__DRAW_ARROW_COEF).to_line();
    Line r_arrow = Vector((-normal_vector * this->__DRAW_NORMAL_COEF - *this) * this->__DRAW_ARROW_COEF).to_line();

    l_arrow.set_color(this->color);
    r_arrow.set_color(this->color);

    l_arrow.draw(window, system);
    r_arrow.draw(window, system);
}

void Vector::dump() const {
    printf("<Vector: (%.3lf, %.3lf) -> (%.3lf, %.3lf) >\n", this->start.x, this->start.y, this->end.x, this->end.y);
}
