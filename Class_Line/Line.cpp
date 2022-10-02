//
// Created by IvanBrekman on 16.09.2022
//

#include <cmath>

#include "../Class_Utils/baselib.hpp"
#include "../Class_Window/Window.hpp"
#include "../Class_CoordinateSystem/CoordinateSystem.hpp"

#include "Line.hpp"

double Line::length() const {
    return sqrt(pow(this->m_mainPoint.x - this->end_point.x, 2) + pow(this->m_mainPoint.y - this->end_point.y, 2));
}

void Line::dump() const {
    printf("<Line: (%.3lf, %.3lf) -> (%.3lf, %.3lf) >\n", this->m_mainPoint.x, this->m_mainPoint.y, this->end_point.x, this->end_point.y);
}

void Line::draw_impl_(Window& window, const CoordinateSystem& system) {
    CoordinateSystem draw_system = system;
    
    Line line(system.point_to_pixel(this->m_mainPoint), system.point_to_pixel(this->end_point));

    sf::Vertex vert_line[] = {
        sf::Vertex(line.m_mainPoint.to_sfml_vector()),
        sf::Vertex(line.end_point. to_sfml_vector()),
    };

    vert_line[0].color = this->m_fillColor;
    vert_line[1].color = this->m_fillColor;

    window.__sfml_window.draw(vert_line, 2, sf::Lines);
}

void Line::move_to_shift_impl_(Point2D point) {
    if (this->m_hidden) return;

    this->end_point += point;
}

Point2D Line::center() {
    return m_mainPoint + (end_point - m_mainPoint) * 0.5;
}
