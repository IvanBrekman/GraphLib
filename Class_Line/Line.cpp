//
// Created by IvanBrekman on 16.09.2022
//

#include <cmath>

#include "../Class_Utils/baselib.hpp"

#include "Line.hpp"

#include "../Class_Window/Window.hpp"
#include "../Class_CoordinateSystem/CoordinateSystem.hpp"

double Line::length() const {
    return sqrt(pow(this->start.x - this->end.x, 2) + pow(this->start.y - this->end.y, 2));
}

void Line::draw(Window& window, const CoordinateSystem& system) {
    if (this->hidden) return;

    CoordinateSystem draw_system = system;
    
    Line line(system.point_to_pixel(this->start), system.point_to_pixel(this->end));

    sf::Vertex vert_line[] = {
        sf::Vertex(sf::Vector2f(line.start.x, line.start.y)),
        sf::Vertex(sf::Vector2f(line.end.x,   line.end.y)),
    };

    vert_line[0].color = this->fill_color;
    vert_line[1].color = this->fill_color;

    window.__sfml_window.draw(vert_line, 2, sf::Lines);
}

void Line::dump() const {
    printf("<Line: (%.3lf, %.3lf) -> (%.3lf, %.3lf) >\n", this->start.x, this->start.y, this->end.x, this->end.y);
}
