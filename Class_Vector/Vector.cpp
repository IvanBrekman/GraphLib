//
// Created by IvanBrekman on 19.09.2022
//

#include <cmath>

#include "../Class_Utils/baselib.hpp"

#include "Vector.hpp"

Vector Vector::get_normal(Normal_Type type) const {
    Vector normal(Point2D(0, 0), Point2D(this->end_point.y - this->main_point.y, this->main_point.x - this->end_point.x));
    normal += this->main_point;

    return normal;
}

Vector Vector::operator =(const Vector& vector) {
    this->main_point = vector.main_point;
    this->end_point  = vector.end_point;
    this->fill_color = vector.fill_color;

    return vector;
}

Vector Vector::operator +=(const Point2D& point) {
    this->main_point += point;
    this->end_point  += point;

    return *this;
}

Vector Vector::operator *=(double scalar) {
    this->end_point = this->normalize() * scalar + this->main_point;

    return *this;
}

Vector Vector::operator /=(double scalar) {
    return *this *= (1 / scalar);
}

Vector Vector::operator +(const Vector& vector) const {
    Vector tmp(vector.main_point, vector.end_point);
    tmp.move_to_point(this->end_point);

    return Vector(this->main_point, tmp.end_point);
}

Vector Vector::operator -(const Vector& vector) const {
    Vector tmp(vector.main_point, vector.end_point);
    tmp.move_to_point(this->main_point);

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
    return Vector(this->main_point, -this->normalize() + this->main_point);
}

Line Vector::to_line() const {
    return Line(this->main_point, this->end_point);
}

Point2D Vector::normalize() const {
    return this->end_point - this->main_point;
}

void Vector::resize(double new_size) {
    if (this->hidden) return;

    *this *= new_size / this->length();
}

void Vector::rotate(double angle) {
    if (this->hidden) return;
    
    Point2D old_start        = this->main_point;
    Point2D direction_vector = this->normalize();

    angle = angle - 360 * (int)(angle / 360);

    double radians = angle * M_PI / 180;

    double new_x = direction_vector.x * cos(radians) - direction_vector.y * sin(radians);
    double new_y = direction_vector.x * sin(radians) + direction_vector.y * cos(radians);

    this->main_point = Point2D(0, 0);
    this->end_point  = Point2D(new_x, new_y);

    this->move_to_point(old_start);
}

void Vector::dump() const {
    printf("<Vector: (%.3lf, %.3lf) -> (%.3lf, %.3lf) >\n", this->main_point.x, this->main_point.y, this->end_point.x, this->end_point.y);
}

void Vector::draw_impl_(Window& window, const CoordinateSystem& system) {
    Line::draw_impl_(window, system);

    Vector normal_vector = Vector::get_normal(Vector::Normal_Type::LEFT_NORMAL);

    Line l_arrow = Vector(( normal_vector * this->__DRAW_NORMAL_COEF - *this) * this->__DRAW_ARROW_COEF).to_line();
    Line r_arrow = Vector((-normal_vector * this->__DRAW_NORMAL_COEF - *this) * this->__DRAW_ARROW_COEF).to_line();

    l_arrow.set_fill_color(this->fill_color);
    r_arrow.set_fill_color(this->fill_color);

    l_arrow.draw(window, system);
    r_arrow.draw_impl_(window, system);
}

void Vector::move_to_shift(Point2D shift) {
    if (this->hidden) return;
    
    Point2D base_shift = this->normalize();

    this->main_point += shift;
    this->end_point   = this->main_point + base_shift;
}
