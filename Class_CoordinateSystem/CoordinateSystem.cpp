//
// Created by IvanBrekman on 19.09.2022
//

        // ==================== Setters ====================
#include "CoordinateSystem.hpp"

CoordinateSystem::CoordinateSystem(Vec2f center, AxisY_Direction dirY, AxisX_Direction dirX)
: m_center(center), m_showAxis(false), m_axisXDirection(dirX), m_axisYDirection(dirY), Drawable() {
    set_fill_color(Color::Blue);
    
    double x = dirX * CoordinateSystem::DRAW_AXIS_LENGTH;
    double y = dirY * CoordinateSystem::DRAW_AXIS_LENGTH;

    m_axisX = Vector(center - Vec2f(x, 0), center + Vec2f(x, 0));
    m_axisY = Vector(center - Vec2f(0, y), center + Vec2f(0, y));

    m_axisX.set_fill_color(m_fillColor);
    m_axisY.set_fill_color(m_fillColor);
}

CoordinateSystem::~CoordinateSystem() {
    freeStdVector(m_objects, false);
}

Vec2f CoordinateSystem::point_to_pixel(Vec2f point) const {
    double newX = m_axisXDirection * point.x + m_center.x;
    double newY = m_axisYDirection * point.y + m_center.y;

    return Vec2f(newX, newY);
}

Vec2f CoordinateSystem::pixel_to_point(Vec2f pixel) const {
    double newX = m_axisXDirection * (pixel.x - m_center.x);
    double newY = m_axisYDirection * (pixel.y - m_center.y);

    return Vec2f(newX, newY);
}

CoordinateSystem CoordinateSystem::get_system_by_type(CoordinateSystem::Type type, double width, double height, Vec2f leftUpPixel) {
    switch (type) {
        case CoordinateSystem::Type::CENTER:
            return CoordinateSystem(Vec2f(width / 2, height / 2) + leftUpPixel, CoordinateSystem::AxisY_Direction::UP);
        case CoordinateSystem::Type::LEFT_UP:
            return CoordinateSystem(Vec2f(0, 0)                  + leftUpPixel);
        case CoordinateSystem::Type::LEFT_BOTTOM:
            return CoordinateSystem(Vec2f(0, height)             + leftUpPixel, CoordinateSystem::AxisY_Direction::UP);
        
        default:
            ASSERT_IF(0, "Unknown Coordinate_System_Type value", CoordinateSystem(width, height));
    }
}

void CoordinateSystem::draw_axis(MainWindow& window) {
    if (m_showAxis) {
        m_axisX.draw(window, CoordinateSystem(0, 0));
        m_axisY.draw(window, CoordinateSystem(0, 0));
    }
}

void CoordinateSystem::append_object(Drawable* object, int index) {
    ASSERT_IF(VALID_PTR(object), "Invalid object ptr", );
    
    if (index == CoordinateSystem::LAST_INDEX) m_objects.push_back(object);
    else                                       m_objects.emplace(m_objects.cbegin() + index, object);
}

void CoordinateSystem::extend_objects(std::vector <Drawable*> objects, int index) {
    for (Drawable* object : objects) {
        append_object(object, index++);
    }
}

void CoordinateSystem::dump() const {
    printf(
        "<CoordinateSystem: center - (%5.1lf, %5.1lf) | type - '%4s-%-5s'\n",
        m_center.x, m_center.y,
        m_axisYDirection == CoordinateSystem::AxisY_Direction::UP   ? "UP"   : "DOWN",
        m_axisXDirection == CoordinateSystem::AxisX_Direction::LEFT ? "LEFT" : "RIGHT"
    );
    printf("    AxisX - "); m_axisX.dump();
    printf("    AxisY - "); m_axisY.dump();
    printf(">\n");
}

// ==================== Getters ====================
Vec2f CoordinateSystem::center() const {
    return m_center;
}

bool CoordinateSystem::show_axis() const {
    return m_showAxis;
}

CoordinateSystem::AxisX_Direction CoordinateSystem::axis_x_direction() const {
    return m_axisXDirection;
}

CoordinateSystem::AxisY_Direction CoordinateSystem::axis_y_direction() const {
    return m_axisYDirection;
}

std::vector<Drawable*> CoordinateSystem::objects() const {
    return m_objects;
}
// =================================================

// ==================== Setters ====================
CoordinateSystem& CoordinateSystem::set_center(Vec2f newCenter) {
    if (!m_hidden) {
        m_center = newCenter;
    }

    return *this;
}

CoordinateSystem& CoordinateSystem::set_show_axis(bool showAxisVal) {
    m_showAxis = showAxisVal;
    
    return *this;
}

CoordinateSystem& CoordinateSystem::set_axis_x_direction(CoordinateSystem::AxisX_Direction dir) {
    m_axisXDirection = dir;

    return *this;
}

CoordinateSystem& CoordinateSystem::set_axis_y_direction(CoordinateSystem::AxisY_Direction dir) {
    m_axisYDirection = dir;

    return *this;
}

CoordinateSystem& CoordinateSystem::set_objects(std::vector<Drawable*> objects) {
    m_objects.resize(0);

    for (Drawable* object : objects) {
        m_objects.push_back(object);
    }

    return *this;
}

// @virtual
CoordinateSystem& CoordinateSystem::set_hidden(bool hidden) {
    for (Drawable* object : m_objects) {
        object->set_hidden(hidden);
    }

    return *this;
}
// =================================================

// @virtual
void CoordinateSystem::draw_impl_(MainWindow& window, const CoordinateSystem& system) {
    for (Drawable* object : m_objects) {
        object->draw(window, *this);
    }

    draw_axis(window);
}
