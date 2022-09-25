//
// Created by IvanBrekman on 16.09.2022
//

#include <cmath>

#include "../Class_Utils/baselib.hpp"
#include "../Class_Window/Window.hpp"
#include "../Class_CoordinateSystem/CoordinateSystem.hpp"

#include "Line.hpp"

double Line::length() const {
    return sqrt(pow(this->main_point.x - this->end_point.x, 2) + pow(this->main_point.y - this->end_point.y, 2));
}

void Line::dump() const {
    printf("<Line: (%.3lf, %.3lf) -> (%.3lf, %.3lf) >\n", this->main_point.x, this->main_point.y, this->end_point.x, this->end_point.y);
}

void Line::draw(Window& window, const CoordinateSystem& system) {
    if (this->hidden) return;

    CoordinateSystem draw_system = system;
    
    Line line(system.point_to_pixel(this->main_point), system.point_to_pixel(this->end_point));

    sf::Vertex vert_line[] = {
        sf::Vertex(line.main_point.to_sfml_vector()),
        sf::Vertex(line.end_point. to_sfml_vector()),
    };

    vert_line[0].color = this->fill_color;
    vert_line[1].color = this->fill_color;

    window.__sfml_window.draw(vert_line, 2, sf::Lines);
}

void Line::move_to_shift(Point2D point) {
    if (this->hidden) return;

    this->end_point += point;
}
