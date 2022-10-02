//
// Created by IvanBrekman on 24.09.2022
//

#include "../Class_Window/Window.hpp"

#include "Text.hpp"

Text::Text(Point2D main_point, const char* text, int size)
: Moveable(main_point), __str_text(text) {
    ASSERT_IF(VALID_PTR(text), "Invalid text ptr", );

    this->__sfml_font.loadFromFile("fonts/arialamu.ttf");
    this->__sfml_text = sf::Text(text, this->__sfml_font, size);

    this->set_fill_color(Color::Black);
}

void Text::set_text(const char* text) {
    ASSERT_IF(VALID_PTR(text), "Invalid text ptr", );

    this->__str_text = text;
    this->__sfml_text.setString(text);
}

void Text::set_size(double size) {
    this->__sfml_text.setCharacterSize(size);
}

const char* Text::get_text() {
    return this->__str_text;
}

int Text::get_size() {
    return this->__sfml_text.getCharacterSize();
}

double Text::get_width() {
    return this->__sfml_text.getLocalBounds().width;
}

double Text::get_height() {
    return this->__sfml_text.getLocalBounds().height;
}

void Text::set_fill_color(Color color) {
    Drawable::set_fill_color(color);
    this->__sfml_text.setFillColor(color);
}

void Text::draw_impl_(Window& window, const CoordinateSystem& system) {
    if (this->m_hidden) return;

    Point2D point = this->m_mainPoint;
    if (this->m_centered) {
        point = this->m_mainPoint - Point2D(this->get_width() / 2, this->get_height() / 2);
    }

    Point2D pixel = system.point_to_pixel(point);

    if (system.axis_y_direction == CoordinateSystem::AxisY_Direction::UP)   pixel.y -= this->get_height() * 1.6;
    else                                                                    pixel.y -= this->get_height() * 0.3;
    if (system.axis_x_direction == CoordinateSystem::AxisX_Direction::LEFT) pixel.x -= this->get_width()  * 1.0;

    this->__sfml_text.setPosition(sf::Vector2f(pixel.x, pixel.y));
    window.__sfml_window.draw(this->__sfml_text);
}

Point2D Text::center() {
    return m_mainPoint;
}
