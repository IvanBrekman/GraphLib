//
// Created by IvanBrekman on 24.09.2022
//

#include "../Class_Window/Window.hpp"

#include "Text.hpp"

Text::Text(Point2D start_point, const char* text, int size)
: start_point(start_point), text(text), size(size) {
    this->__sfml_font.loadFromFile("fonts/arialamu.ttf");
    this->__sfml_text = sf::Text(text, this->__sfml_font, size);

    printf("Size: %d (%lf %lf)\n", this->__sfml_text.getCharacterSize(), this->__sfml_text.getLocalBounds().width, this->__sfml_text.getLocalBounds().height);

    this->set_fill_color(Color::Black);
}

void Text::move_to(Point2D shift) {
    this->start_point += shift;
}

void Text::set_fill_color(Color color) {
    this->fill_color = color;
    this->__sfml_text.setFillColor(color);
}

void Text::set_text(const char* text) {
    this->text = text;
    this->__sfml_text.setString(text);
}

void Text::set_size(double size) {
    this->size = size;
    this->__sfml_text.setCharacterSize(size);
}

double Text::get_width() {
    return this->__sfml_text.getLocalBounds().width;
}

double Text::get_height() {
    return this->__sfml_text.getLocalBounds().height;
}

void Text::draw(Window& window, const CoordinateSystem& system) {
    Point2D pixel = system.point_to_pixel(this->start_point);

    if (system.axis_y_direction == CoordinateSystem::AxisY_Direction::UP)   pixel.y -= this->get_height() * 2;
    if (system.axis_x_direction == CoordinateSystem::AxisX_Direction::LEFT) pixel.x -= this->get_width()  * 2;

    this->__sfml_text.setPosition(sf::Vector2f(pixel.x, pixel.y));
    window.__sfml_window.draw(this->__sfml_text);
}
