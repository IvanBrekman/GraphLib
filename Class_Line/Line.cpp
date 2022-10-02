//
// Created by IvanBrekman on 16.09.2022
//

#include <cmath>

#include "../Class_Utils/baselib.hpp"
#include "../Class_Window/Window.hpp"
#include "../Class_CoordinateSystem/CoordinateSystem.hpp"

#include "Line.hpp"

double Line::length() const {
    return sqrt(pow(m_mainPoint.x - m_endPoint.x, 2) + pow(m_mainPoint.y - m_endPoint.y, 2));
}

void Line::dump() const {
    printf("<Line: (%.3lf, %.3lf) -> (%.3lf, %.3lf) >\n", m_mainPoint.x, m_mainPoint.y, m_endPoint.x, m_endPoint.y);
}

// @virtual
void Line::draw_impl_(Window& window, const CoordinateSystem& system) {
    Line line(system.point_to_pixel(m_mainPoint), system.point_to_pixel(m_endPoint));

    sf::Vertex vertLine[] = {
        sf::Vertex(line.m_mainPoint.to_sfml_vector()),
        sf::Vertex(line.m_endPoint. to_sfml_vector()),
    };

    vertLine[0].color = m_fillColor;
    vertLine[1].color = m_fillColor;

    window.__sfml_window.draw(vertLine, 2, sf::Lines);
}

// @virtual
void Line::move_to_shift_impl_(Point2D point) {
    m_endPoint += point;
}

// @virtual
Point2D Line::center() const {
    return m_mainPoint + (m_endPoint - m_mainPoint) * 0.5;
}
