//
// Created by IvanBrekman on 21.09.2022
//

#include <cmath>

#include "../Class_Utils/baselib.hpp"
#include "../Class_Window/Window.hpp"

#include "Figures.hpp"

// ======================================== Figure ========================================
Figure::Figure(Point2D mainPoint, bool centered)
: Moveable(mainPoint) {
    m_centered = centered;
}

void Figure::set_fill_color(Color fillColor, Color outlineColor, double width) {
    Drawable::set_fill_color(fillColor);
    m_outlineColor = outlineColor;
    m_outlineWidth = width;
}

void Figure::set_fill_color(Color color) {
    set_fill_color(color, color, 0);
}

void Figure::set_shape_color_(sf::Shape& shape) {
    shape.setFillColor       (m_fillColor);
    shape.setOutlineColor    (m_outlineColor);
    shape.setOutlineThickness(m_outlineWidth);
}

void Figure::draw(Window& window, const CoordinateSystem& system, Point2D pixel, sf::Shape& shape) {
    shape.setPosition(pixel.to_sfml_vector());

    set_shape_color_(shape);
    get_sfml_window_(window).draw(shape);
}
// ========================================================================================

// ======================================== Circle ========================================
Circle::Circle(Point2D mainPoint, double radius, bool centered)
: Figure(mainPoint, centered), m_radius(radius) {
    m_sfml_shape_ = sf::CircleShape(radius, Circle::POINTS_ON_DRAW__);

    m_centered = centered;
}

// @virtual
bool Circle::contains(Point2D point) {
    return (pow(point.x - center().x, 2) + pow(point.y - center().y, 2)) <= pow(m_radius, 2);
}

// @virtual
void Circle::draw_impl_(Window& window, const CoordinateSystem& system) {
    Point2D min_point = m_mainPoint;
    if (m_centered) {
        min_point = m_mainPoint - Point2D(m_radius, m_radius);
    }
    
    Point2D pixel = system.point_to_pixel(min_point);
    if (system.m_axisYDirection == CoordinateSystem::AxisY_Direction::UP)   pixel.y -= m_radius * 2;
    if (system.m_axisXDirection == CoordinateSystem::AxisX_Direction::LEFT) pixel.x -= m_radius * 2;

    Figure::draw(window, system, pixel, m_sfml_shape_);
}

// @virtual
Point2D Circle::center() const {
    return m_centered ? m_mainPoint : (m_mainPoint + Point2D(m_radius, m_radius));
}
// ========================================================================================

// ======================================= Rectangle ======================================
Rectangle::Rectangle(Point2D main_point, double width, double height)
: Figure(main_point, false), m_width(width), m_height(height) {
    m_sfml_shape__ = sf::RectangleShape(sf::Vector2f(width, height));
}

// @virtual
bool Rectangle::contains(Point2D point) {
    Point2D minPoint = m_centered ? (m_mainPoint - Point2D(m_width / 2, m_height / 2)) : m_mainPoint;
    Point2D maxPoint = minPoint + Point2D(m_width, m_height);

    return (minPoint.x <= point.x && point.x <= maxPoint.x) &&
           (minPoint.y <= point.y && point.y <= maxPoint.y);
}

// @virtual
void Rectangle::draw_impl_(Window& window, const CoordinateSystem& system) {
    Point2D point = m_mainPoint;
    if (m_centered) {
        point = m_mainPoint - Point2D(m_width / 2, m_height / 2);
    }
    
    Point2D pixel = system.point_to_pixel(point);
    if (system.m_axisYDirection == CoordinateSystem::AxisY_Direction::UP)   pixel.y -= m_height;
    if (system.m_axisXDirection == CoordinateSystem::AxisX_Direction::LEFT) pixel.x -= m_width;

    Figure::draw(window, system, pixel, m_sfml_shape__);
}

// @virtual
Point2D Rectangle::center() const {
    return m_centered ? m_mainPoint : (m_mainPoint + Point2D(m_width / 2, m_height / 2));
}
// ========================================================================================

// ==================================== RegularPolygon ====================================
RegularPolygon::RegularPolygon(Point2D mainPoint, double radius, double vAmount, bool centered)
: Circle(mainPoint, radius, centered), vertexAmount(vAmount) {
    m_sfml_shape_.setPointCount(vAmount);
}

// @virtual
bool RegularPolygon::contains(Point2D point) {
    int vSize = vertexAmount;

    bool contains = false;

    point -= m_mainPoint;

    for (int i = 0, j = vSize - 1; i < vSize; i++) {
        sf::Vector2f vectorPi = m_sfml_shape_.getPoint(i);
        sf::Vector2f vectorPj = m_sfml_shape_.getPoint(j);

        Point2D pi = Point2D(vectorPi.x, vectorPi.y);
        Point2D pj = Point2D(vectorPj.x, vectorPj.y);

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
Polygon::Polygon(Point2D* vertexes, int vertexesAmount)
: Figure() {
    ASSERT_IF(VALID_PTR(vertexes), "Ivalid vertexes ptr", );

    m_sfml_shape_.setPointCount(vertexesAmount);

    for (int i = 0; i < vertexesAmount; i++) {
        m_vertexes__.push_back(vertexes[i]);
    }
}

std::vector <Point2D>* Polygon::get_vertexes() {
    return &m_vertexes__;
}

Point2D Polygon::get_vertex(int index) {
    return m_vertexes__.at(index);
}

// @virtual
bool Polygon::contains(Point2D point) {
    std::vector <Point2D> v      = m_vertexes__;
    int                   vSize = v.size();

    bool contains = false;

    for (int i = 0, j = vSize - 1; i < vSize; i++) {
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

// @virtual
void Polygon::draw_impl_(Window& window, const CoordinateSystem& system) {
    if (m_hidden) return;
    
    int i = 0;
    for (Point2D point : m_vertexes__) {
        Point2D pixel = system.point_to_pixel(point);

        m_sfml_shape_.setPoint(i++, pixel.to_sfml_vector());
    }

    set_shape_color_(m_sfml_shape_);
    get_sfml_window_(window).draw(m_sfml_shape_);
}

// @virtual
Point2D Polygon::center() const {
    return m_vertexes__.at(0);
}

// @virtual
void Polygon::move_to_shift_impl_(Point2D shift) {
    if (m_hidden) return;
    
    for (int i = 0; i < m_vertexes__.size(); i++) {
        m_vertexes__.at(i) += shift;
    }
}
// ========================================================================================

// ======================================= Ellipse ========================================
Ellipse::Ellipse(Point2D mainPoint, Point2D radius, bool centered)
: Polygon(mainPoint, centered), m_radius(radius) {
    m_sfml_shape_.setPointCount(Ellipse::POINTS_ON_DRAW__);
}

// @virtual
bool Ellipse::contains(Point2D point) {
    point -= center();
    return (pow(point.x, 2) / pow(m_radius.x, 2) + pow(point.y, 2) / pow(m_radius.y, 2)) <= 1;
}

// @virtual
void Ellipse::draw_impl_(Window& window, const CoordinateSystem& system) {
    for (int i = 0; i < Ellipse::POINTS_ON_DRAW__; i++) {
        Point2D pixel = system.point_to_pixel(get_point__(i));
        m_sfml_shape_.setPoint(i, pixel.to_sfml_vector());
    }

    set_shape_color_(m_sfml_shape_);
    get_sfml_window_(window).draw(m_sfml_shape_);
}

// @virtual
Point2D Ellipse::center() const {
    return m_centered ? m_mainPoint : (m_mainPoint + m_radius);
}


// @virtual
void Ellipse::move_to_shift_impl_(Point2D shift) {
    if (m_hidden) return;
    
    Figure::move_to_shift(shift);
}

Point2D Ellipse::get_point__(int index) {
    float angle = index * 2 * M_PI / Ellipse::POINTS_ON_DRAW__ - M_PI / 2;
    float x = std::cos(angle) * m_radius.x;
    float y = std::sin(angle) * m_radius.y;

    Point2D point = m_mainPoint + Point2D(m_radius.x + x, m_radius.y + y);

    return m_centered ? (point - m_radius) : point;
}
// ========================================================================================
