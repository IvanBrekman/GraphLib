//
// Created by IvanBrekman on 19.09.2022
//

#include "../config/baselib.hpp"
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
    this->end = (this->end - this->start) * scalar + this->start;

    return *this;
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

Vector Vector::operator -() const {
    return Vector(this->start, -(this->end - this->start) + this->start);
}

Line Vector::to_line(Color color) const {
    return Line(this->start, this->end, color);
}

void Vector::move_to(Point2D new_start) {
    Point2D shift = this->end - this->start;

    this->start = new_start;
    this->end   = new_start + shift;
}

void Vector::draw(Window& window, const CoordinateSystem& system) {
    if (this->hidden) return;
    
    Line::draw(window, system);

    Vector normal_vector = Vector::get_normal(Vector::Normal_Type::LEFT_NORMAL);

    (( normal_vector * this->__DRAW_NORMAL_COEF - *this) * this->__DRAW_ARROW_COEF).to_line(this->color).draw(window, system);
    ((-normal_vector * this->__DRAW_NORMAL_COEF - *this) * this->__DRAW_ARROW_COEF).to_line(this->color).draw(window, system);
}

void Vector::dump() const {
    printf("<Vector: (%.3lf, %.3lf) -> (%.3lf, %.3lf) >\n", this->start.x, this->start.y, this->end.x, this->end.y);
}
