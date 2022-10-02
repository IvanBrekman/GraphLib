//
// Created by IvanBrekman on 19.09.2022
//

#include "CoordinateSystem.hpp"

CoordinateSystem::CoordinateSystem(Point2D center, AxisY_Direction dirY, AxisX_Direction dirX)
: m_center(center), m_showAxis(false), m_axisXDirection(dirX), m_axisYDirection(dirY), Drawable() {
    set_fill_color(Color::Blue);

    double x = dirX * CoordinateSystem::DRAW_AXIS_LENGTH__;
    double y = dirY * CoordinateSystem::DRAW_AXIS_LENGTH__;

    m_axisX__ = Vector(center - Point2D(x, 0), center + Point2D(x, 0));
    m_axisY__ = Vector(center - Point2D(0, y), center + Point2D(0, y));

    m_axisX__.set_fill_color(m_fillColor);
    m_axisY__.set_fill_color(m_fillColor);
}

Point2D CoordinateSystem::point_to_pixel(Point2D point) const {
    double newX = m_axisXDirection * point.x + m_center.x;
    double newY = m_axisYDirection * point.y + m_center.y;

    return Point2D(newX, newY);
}

Point2D CoordinateSystem::pixel_to_point(Point2D pixel) const {
    double newX = m_axisXDirection * (pixel.x - m_center.x);
    double newY = m_axisYDirection * (pixel.y - m_center.y);

    return Point2D(newX, newY);
}

CoordinateSystem CoordinateSystem::get_system_by_type(CoordinateSystem::Type type, double width, double height) {
    switch (type) {
        case CoordinateSystem::Type::CENTER:
            return CoordinateSystem(width / 2, height / 2, CoordinateSystem::AxisY_Direction::UP);
        case CoordinateSystem::Type::LEFT_UP:
            return CoordinateSystem(0, 0);
        case CoordinateSystem::Type::LEFT_BOTTOM:
            return CoordinateSystem(0, height, CoordinateSystem::AxisY_Direction::UP);
        
        default:
            ASSERT_IF(0, "Unknown Coordinate_System_Type value", CoordinateSystem(width, height));
    }
}

void CoordinateSystem::set_show_axis(bool showAxisVal) {
    m_showAxis = showAxisVal;
}

void CoordinateSystem::draw_axis(Window& window) {
    if (m_showAxis) {
        m_axisX__.draw(window, CoordinateSystem(0, 0));
        m_axisY__.draw(window, CoordinateSystem(0, 0));
    }
}

void CoordinateSystem::append_object(Drawable* object, int index) {
    ASSERT_IF(VALID_PTR(object), "Invalid object ptr", );
    
    if (index == CoordinateSystem::LAST_INDEX__) m_objects.push_back(object);
    else                                         m_objects.emplace(m_objects.cbegin() + index, object);
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
    printf("    AxisX - "); m_axisX__.dump();
    printf("    AxisY - "); m_axisY__.dump();
    printf(">\n");
}

void CoordinateSystem::set_hidden(bool hidden) {
    for (Drawable* object : m_objects) {
        object->set_hidden(hidden);
    }
}

void CoordinateSystem::draw_impl_(Window& window, const CoordinateSystem& system) {
    for (Drawable* object : m_objects) {
        object->draw(window, *this);
    }

    draw_axis(window);
}
