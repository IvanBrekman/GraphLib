//
// Created by IvanBrekman on 21.09.2022
//

#include <cmath>

#include "../Class_Utils/baselib.hpp"

#include "Figures.hpp"

// ======================================== Figure ========================================
void Figure::move_to(Point2D shift) {
    this->start_point += shift;
}

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

bool Circle::contains(Point2D point) {
    return (pow(point.x - this->center().x, 2) + pow(point.y - this->center().y, 2)) <= pow(this->radius, 2);
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

bool Rectangle::contains(Point2D point) {
    Point2D min_point = this->start_point;
    Point2D max_point = min_point + Point2D(this->width, this->height);

    return (min_point.x <= point.x && point.x <= max_point.x) &&
           (min_point.y <= point.y && point.y <= max_point.y);
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

bool RegularPolygon::contains(Point2D point) {
    int v_size = this->vertex_amount;

    bool contains = false;

    int j = v_size - 1;

    point -= start_point;

    for (int i = 0; i < v_size; i++) {
        sf::Vector2f vector_pi = this->_sfml_shape.getPoint(i);
        sf::Vector2f vector_pj = this->_sfml_shape.getPoint(j);

        Point2D pi = Point2D(vector_pi.x, vector_pi.y);
        Point2D pj = Point2D(vector_pj.x, vector_pj.y);

        if (
            ((pi.y < point.y && point.y <= pj.y) || (pj.y < point.y && point.y <= pi.y)) &&
            ((pi.x + (point.y - pi.y) / (pj.y - pi.y) * (pj.x - pi.x)) < point.x)
           ) {
            contains ^= 1;
        }
        j = i;
    }

    return contains;
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

bool Polygon::contains(Point2D point) {
    std::vector <Point2D> v      = this->__vertexes;
    int                   v_size = v.size();

    bool contains = false;

    int j = v_size - 1;

    for (int i = 0; i < v_size; i++) {
        if (
            ((v.at(i).y < point.y && point.y <= v.at(j).y) || (v.at(j).y < point.y && point.y <= v.at(i).y)) &&
            ((v.at(i).x + (point.y - v.at(i).y) / (v.at(j).y - v.at(i).y) * (v.at(j).x - v.at(i).x)) < point.x)
           ) {
            contains ^= 1;
        }
        j = i;
    }

    return contains;
}

void Polygon::move_to(Point2D shift) {
    for (int i = 0; i < this->__vertexes.size(); i++) {
        this->__vertexes.at(i) += shift;
    }
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

bool Ellipse::contains(Point2D point) {
    point -= this->center();
    return (pow(point.x, 2) / pow(this->radius.x, 2) + pow(point.y, 2) / pow(this->radius.y, 2)) <= 1;
}

void Ellipse::move_to(Point2D shift) {
    Figure::move_to(shift);
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
