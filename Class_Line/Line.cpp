//
// Created by IvanBrekman on 16.09.2022
//

#include <cmath>

#include "../Class_Utils/baselib.hpp"
#include "../Class_Window/Window.hpp"
#include "../Class_CoordinateSystem/CoordinateSystem.hpp"

#include "Line.hpp"

double Line::length() const {
    return sqrt(pow(main_point().x - m_endPoint.x, 2) + pow(main_point().y - m_endPoint.y, 2));
}

void Line::dump() const {
    printf("<Line: (%.3lf, %.3lf) -> (%.3lf, %.3lf) >\n", main_point().x, main_point().y, m_endPoint.x, m_endPoint.y);
}

// @virtual
void Line::draw_impl_(Window& window, const CoordinateSystem& system) {
    Line line(system.point_to_pixel(main_point()), system.point_to_pixel(m_endPoint));

    sf::Vertex vertLine[] = {
        sf::Vertex(line.main_point().to_sfml_vector()),
        sf::Vertex(line.m_endPoint. to_sfml_vector()),
    };

    vertLine[0].color = m_fillColor;
    vertLine[1].color = m_fillColor;

    get_sfml_window_(window).draw(vertLine, 2, sf::Lines);
}

// @virtual
void Line::move_to_shift_impl_(Vec2f point) {
    m_endPoint += point;
}

// @virtual
Vec2f Line::center() const {
    if (centered()) return main_point();
    return main_point() + (m_endPoint - main_point()) * 0.5;
}
