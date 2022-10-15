//
// Created by IvanBrekman on 24.09.2022
//

#include "../Class_Window/Window.hpp"

#include "Text.hpp"

Text::Text(Vec2f mainPoint, const char* text, int size)
: Moveable(mainPoint), m_strText__(text) {
    ASSERT_IF(VALID_PTR(text), "Invalid text ptr", );

    m_sfml_font__.loadFromFile("fonts/arialamu.ttf");
    m_sfml_text__ = sf::Text(text, m_sfml_font__, size);

    set_fill_color(Color::Black);
}

void Text::set_text(const char* text) {
    ASSERT_IF(VALID_PTR(text), "Invalid text ptr", );

    m_strText__ = text;
    m_sfml_text__.setString(text);
}

void Text::set_size(double size) {
    m_sfml_text__.setCharacterSize(size);
}

const char* Text::get_text() const {
    return m_strText__;
}

int Text::get_size() const {
    return m_sfml_text__.getCharacterSize();
}

double Text::get_width() const {
    return m_sfml_text__.getLocalBounds().width;
}

double Text::get_height() const {
    return m_sfml_text__.getLocalBounds().height;
}

Text& Text::set_fill_color(Color color) {
    Drawable::set_fill_color(color);
    m_sfml_text__.setFillColor(color);

    return *this;
}

void Text::draw_impl_(Window& window, const CoordinateSystem& system) {
    Vec2f point = m_mainPoint;
    if (m_centered) {
        point = m_mainPoint - Vec2f(get_width() / 2, get_height() / 2);
    }

    Vec2f pixel = system.point_to_pixel(point);

    if (system.m_axisYDirection == CoordinateSystem::AxisY_Direction::UP)   pixel.y -= get_height() * 1.6;
    else                                                                    pixel.y -= get_height() * 0.3;
    if (system.m_axisXDirection == CoordinateSystem::AxisX_Direction::LEFT) pixel.x -= get_width()  * 1.0;

    m_sfml_text__.setPosition(sf::Vector2f(pixel.x, pixel.y));
    get_sfml_window_(window).draw(m_sfml_text__);
}

Vec2f Text::center() const {
    return m_mainPoint;
}
