//
// Created by IvanBrekman on 21.09.2022
//

#include <cmath>

#include "../Class_Utils/baselib.hpp"

#include "Figures.hpp"

// ======================================== Figure ========================================
void Figure::set_figure_color(Color fill_color, Color outline_color, double width) {
    this->fill_color    = fill_color;
    this->outline_color = outline_color;
    this->outline_width = width;
}

void Figure::draw(Window& window, const CoordinateSystem& system, Point2D pixel, sf::Shape& shape) {
    shape.setPosition(sf::Vector2f(pixel.x, pixel.y));

    this->_set_shape_color(shape);
    this->_get_sfml_window(window)->draw(shape);
}

void Figure::_set_shape_color(sf::Shape& shape) {
    shape.setFillColor       (this->fill_color);
    shape.setOutlineColor    (this->outline_color);
    shape.setOutlineThickness(this->outline_width);
}
// ========================================================================================

// ======================================== Circle ========================================
Circle::Circle(Point2D start_point, double radius, bool centered)
: Figure(start_point), radius(radius) {
    this->_sfml_shape = sf::CircleShape(radius, Circle::__POINTS_ON_DRAW);

    this->centered = centered;
    if (centered) Circle::move_center_to_start_point();
}

Point2D Circle::center() {
    return this->centered ? this->start_point : (this->start_point + Point2D(radius, radius));
}

void Circle::draw(Window& window, const CoordinateSystem& system) {
    double shift = sqrt(pow(this->radius, 2) + (this->radius, 2));

    Point2D min_point = this->start_point;
    if (this->centered) {
        min_point = this->start_point - Point2D(shift, shift);
    }
    
    Point2D pixel = system.point_to_pixel(min_point);
    if (system.axis_y_direction == CoordinateSystem::AxisY_Direction::UP)   pixel.y -= this->radius * 2;
    if (system.axis_x_direction == CoordinateSystem::AxisX_Direction::LEFT) pixel.x -= this->radius * 2;

    Figure::draw(window, system, pixel, this->_sfml_shape);
}
// ========================================================================================

// ======================================= Rectangle ======================================
Rectangle::Rectangle(Point2D start_point, double width, double height)
: Figure(start_point), width(width), height(height) {
    this->__sfml_shape = sf::RectangleShape(sf::Vector2f(width, height));
}

Point2D Rectangle::center() {
    return this->start_point + Point2D(this->width / 2, this->height / 2);
}

void Rectangle::draw(Window& window, const CoordinateSystem& system) {
    Point2D pixel = system.point_to_pixel(this->start_point);
    if (system.axis_y_direction == CoordinateSystem::AxisY_Direction::UP)   pixel.y -= this->height;
    if (system.axis_x_direction == CoordinateSystem::AxisX_Direction::LEFT) pixel.x -= this->width;

    Figure::draw(window, system, pixel, this->__sfml_shape);
}
// ========================================================================================

// ==================================== RegularPolygon ====================================
RegularPolygon::RegularPolygon(Point2D start_point, double radius, double v_amount, bool centered)
: Circle(start_point, radius, centered), vertex_amount(v_amount) {
    this->_sfml_shape.setPointCount(v_amount);
}
// ========================================================================================

// ======================================= Polygon ========================================
Polygon::Polygon(Point2D* vertexes, int vertexes_amount)
: Figure() {
    ASSERT_IF(VALID_PTR(vertexes), "Ivalid vertexes ptr", );

    this->_sfml_shape.setPointCount(vertexes_amount);

    for (int i = 0; i < vertexes_amount; i++) {
        this->__vertexes.push_back(vertexes[i]);
    }
}

std::vector <Point2D>* Polygon::get_vertexes() {
    return &this->__vertexes;
}

Point2D Polygon::get_vertex(int index) {
    return this->__vertexes.at(index);
}

Point2D Polygon::center() {
    return this->__vertexes.at(0);
}

void Polygon::draw(Window& window, const CoordinateSystem& system) {
    int i = 0;
    for (Point2D point : this->__vertexes) {
        Point2D pixel = system.point_to_pixel(point);

        this->_sfml_shape.setPoint(i++, sf::Vector2f(pixel.x, pixel.y));
    }

    this->_set_shape_color(this->_sfml_shape);
    this->_get_sfml_window(window)->draw(this->_sfml_shape);
}
// ========================================================================================

// ======================================= Ellipse ========================================
Ellipse::Ellipse(Point2D start_point, Point2D radius, bool centered)
: Polygon(start_point), radius(radius), centered(centered) {
    this->_sfml_shape.setPointCount(Ellipse::__POINTS_ON_DRAW);
}

Point2D Ellipse::center() {
    return this->centered ? this->start_point : (this->start_point + this->radius);
}

void Ellipse::draw(Window& window, const CoordinateSystem& system) {
    for (int i = 0; i < Ellipse::__POINTS_ON_DRAW; i++) {
        Point2D pixel = system.point_to_pixel(this->__get_point(i));
        this->_sfml_shape.setPoint(i, sf::Vector2f(pixel.x, pixel.y));
    }

    this->_set_shape_color(this->_sfml_shape);
    this->_get_sfml_window(window)->draw(this->_sfml_shape);
}

Point2D Ellipse::__get_point(int index) {
    float angle = index * 2 * M_PI / Ellipse::__POINTS_ON_DRAW - M_PI / 2;
    float x = std::cos(angle) * this->radius.x;
    float y = std::sin(angle) * this->radius.y;

    Point2D point = this->start_point + Point2D(radius.x + x, radius.y + y);

    return this->centered ? (point - this->radius) : point;
}
// ========================================================================================
