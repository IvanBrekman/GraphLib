//
// Created by IvanBrekman on 21.09.2022
//

#include <cmath>

#include "../Class_Utils/baselib.hpp"
#include "../Class_Window/Window.hpp"

#include "Figures.hpp"

// ======================================== Figure ========================================
Figure::Figure(Vec2f mainPoint, bool centered)
: Moveable(mainPoint) {
    m_centered = centered;
}

// ==================== Getters ====================
Color Figure::outline_color() const {
    return m_outlineColor;
}

double Figure::outline_width() const {
    return m_outlineWidth;
}
// =================================================

// ==================== Getters ====================
Figure& Figure::set_fill_color(Color fillColor, Color outlineColor, double width) {
    Drawable::set_fill_color(fillColor);
    m_outlineColor = outlineColor;
    m_outlineWidth = width;

    return *this;
}

Figure& Figure::set_fill_color(Color color) {
    return set_fill_color(color, color, 0);
}
// =================================================

void Figure::set_shape_color_(sf::Shape& shape) {
    shape.setFillColor       (m_fillColor);
    shape.setOutlineColor    (m_outlineColor);
    shape.setOutlineThickness(m_outlineWidth);
}

void Figure::draw_(MainWindow& window, const CoordinateSystem& system, Vec2f pixel, sf::Shape& shape) {
    shape.setPosition(pixel.to_sfml_vector());

    set_shape_color_(shape);
    get_sfml_window_(window).draw(shape);
}
// ========================================================================================

// ======================================== Circle ========================================
Circle::Circle(Vec2f mainPoint, double radius, bool centered)
: Figure(mainPoint, centered), m_radius(radius) {
    m_sfml_shape = sf::CircleShape(radius, Circle::POINTS_ON_DRAW);

    m_centered = centered;
}

// ==================== Getters ====================
double Circle::radius() const {
    return m_radius;
}
// ================================================

// ==================== Setters ====================
Circle& Circle::set_radius(double newRadius) {
    m_radius = newRadius;

    return *this;
}
// =================================================

// @virtual
bool Circle::contains(Vec2f point) {
    return (pow(point.x - center().x, 2) + pow(point.y - center().y, 2)) <= pow(m_radius, 2);
}

// @virtual
void Circle::draw_impl_(MainWindow& window, const CoordinateSystem& system) {
    Vec2f min_point = m_mainPoint;
    if (m_centered) {
        min_point = m_mainPoint - Vec2f(m_radius, m_radius);
    }
    
    Vec2f pixel = system.point_to_pixel(min_point);
    if (system.axis_y_direction() == CoordinateSystem::AxisY_Direction::UP)   pixel.y -= m_radius * 2;
    if (system.axis_x_direction() == CoordinateSystem::AxisX_Direction::LEFT) pixel.x -= m_radius * 2;

    Figure::draw_(window, system, pixel, m_sfml_shape);
}

// @virtual
Vec2f Circle::center() const {
    return m_centered ? m_mainPoint : (m_mainPoint + Vec2f(m_radius, m_radius));
}
// ========================================================================================

// ======================================= Rectangle ======================================
Rectangle::Rectangle(Vec2f main_point, double width, double height)
: Figure(main_point, false), m_width(width), m_height(height) {
    m_sfml_shape = sf::RectangleShape(sf::Vector2f(width, height));
}

// ==================== Getters ====================
double Rectangle::width() const {
    return m_width;
}

double Rectangle::height() const {
    return m_height;
}
// =================================================

// ==================== Setters ====================
Rectangle& Rectangle::set_width(double newWidth) {
    m_width = newWidth;

    return *this;
}

Rectangle& Rectangle::set_height(double newHeight) {
    m_height = newHeight;

    return *this;
}
// =================================================

// @virtual
bool Rectangle::contains(Vec2f point) {
    Vec2f minPoint = m_centered ? (m_mainPoint - Vec2f(m_width / 2, m_height / 2)) : m_mainPoint;
    Vec2f maxPoint = minPoint + Vec2f(m_width, m_height);

    return (minPoint.x <= point.x && point.x <= maxPoint.x) &&
           (minPoint.y <= point.y && point.y <= maxPoint.y);
}

// @virtual
void Rectangle::draw_impl_(MainWindow& window, const CoordinateSystem& system) {
    Vec2f point = m_mainPoint;
    if (m_centered) {
        point = m_mainPoint - Vec2f(m_width / 2, m_height / 2);
    }
    
    Vec2f pixel = system.point_to_pixel(point);
    if (system.axis_y_direction() == CoordinateSystem::AxisY_Direction::UP)   pixel.y -= m_height;
    if (system.axis_x_direction() == CoordinateSystem::AxisX_Direction::LEFT) pixel.x -= m_width;

    Figure::draw_(window, system, pixel, m_sfml_shape);
}

// @virtual
Vec2f Rectangle::center() const {
    return m_centered ? m_mainPoint : (m_mainPoint + Vec2f(m_width / 2, m_height / 2));
}
// ========================================================================================

// ==================================== RegularPolygon ====================================
RegularPolygon::RegularPolygon(Vec2f mainPoint, double radius, double vAmount, bool centered)
: Circle(mainPoint, radius, centered), m_vertexAmount(vAmount) {
    m_sfml_shape.setPointCount(vAmount);
}

// ==================== Getters ====================
double RegularPolygon::vertex_amount() const {
    return m_vertexAmount;
}
// =================================================

// ==================== Setters ====================
RegularPolygon& RegularPolygon::set_vertex_amount(double newVertexAmount) {
    m_vertexAmount = newVertexAmount;
    m_sfml_shape.setPointCount(newVertexAmount);

    return *this;
}
// =================================================

// @virtual
bool RegularPolygon::contains(Vec2f point) {
    int vSize = m_vertexAmount;

    bool contains = false;

    point -= m_mainPoint;

    for (int i = 0, j = vSize - 1; i < vSize; i++) {
        sf::Vector2f vectorPi = m_sfml_shape.getPoint(i);
        sf::Vector2f vectorPj = m_sfml_shape.getPoint(j);

        Vec2f pi = Vec2f(vectorPi.x, vectorPi.y);
        Vec2f pj = Vec2f(vectorPj.x, vectorPj.y);

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
Polygon::Polygon(Vec2f* vertexes, int vertexesAmount)
: Figure() {
    ASSERT_IF(VALID_PTR(vertexes), "Ivalid vertexes ptr", );

    m_sfml_shape.setPointCount(vertexesAmount);

    for (int i = 0; i < vertexesAmount; i++) {
        m_vertexes.push_back(vertexes[i]);
    }
}

std::vector <Vec2f>* Polygon::get_vertexes() {
    return &m_vertexes;
}

Vec2f Polygon::get_vertex(int index) {
    return m_vertexes.at(index);
}

// @virtual
bool Polygon::contains(Vec2f point) {
    std::vector <Vec2f> v     = m_vertexes;
    int                 vSize = v.size();

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
void Polygon::draw_impl_(MainWindow& window, const CoordinateSystem& system) {    
    int i = 0;
    for (Vec2f point : m_vertexes) {
        Vec2f pixel = system.point_to_pixel(point);

        m_sfml_shape.setPoint(i++, pixel.to_sfml_vector());
    }

    set_shape_color_(m_sfml_shape);
    get_sfml_window_(window).draw(m_sfml_shape);
}

// @virtual
Vec2f Polygon::center() const {
    return m_vertexes.at(0);
}

// @virtual
void Polygon::move_to_shift_impl_(Vec2f shift) {    
    for (int i = 0; i < m_vertexes.size(); i++) {
        m_vertexes.at(i) += shift;
    }
}
// ========================================================================================

// ======================================= Ellipse ========================================
Ellipse::Ellipse(Vec2f mainPoint, Vec2f radius, bool centered)
: Polygon(mainPoint, centered), m_radius(radius) {
    m_sfml_shape.setPointCount(Ellipse::POINTS_ON_DRAW);
}

// ==================== Getters ====================
Vec2f Ellipse::radius() const {
    return m_radius;
}
// =================================================

// ==================== Setters ====================
Ellipse& Ellipse::set_radius(Vec2f newRadius) {
    m_radius = newRadius;

    return *this;
}
// =================================================

// @virtual
bool Ellipse::contains(Vec2f point) {
    point -= center();
    return (pow(point.x, 2) / pow(m_radius.x, 2) + pow(point.y, 2) / pow(m_radius.y, 2)) <= 1;
}

// @virtual
void Ellipse::draw_impl_(MainWindow& window, const CoordinateSystem& system) {
    for (int i = 0; i < Ellipse::POINTS_ON_DRAW; i++) {
        Vec2f pixel = system.point_to_pixel(get_point__(i));
        m_sfml_shape.setPoint(i, pixel.to_sfml_vector());
    }

    set_shape_color_(m_sfml_shape);
    get_sfml_window_(window).draw(m_sfml_shape);
}

// @virtual
Vec2f Ellipse::center() const {
    return m_centered ? m_mainPoint : (m_mainPoint + m_radius);
}


// @virtual
void Ellipse::move_to_shift_impl_(Vec2f shift) {
    Figure::move_to_shift(shift);
}

Vec2f Ellipse::get_point__(int index) {
    float angle = index * 2 * M_PI / Ellipse::POINTS_ON_DRAW - M_PI / 2;
    float x = std::cos(angle) * m_radius.x;
    float y = std::sin(angle) * m_radius.y;

    Vec2f point = m_mainPoint + Vec2f(m_radius.x + x, m_radius.y + y);

    return m_centered ? (point - m_radius) : point;
}
// ========================================================================================
