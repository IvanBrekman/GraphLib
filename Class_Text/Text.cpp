//
// Created by IvanBrekman on 24.09.2022
//

#include "../Class_Window/Window.hpp"

#include "Text.hpp"

Text::Text(Vec2f mainPoint, const char* text, int size)
: Moveable(mainPoint), m_strText(text) {
    ASSERT_IF(VALID_PTR(text), "Invalid text ptr", );

    m_sfml_font.loadFromFile("fonts/arialamu.ttf");
    m_sfml_text = sf::Text(text, m_sfml_font, size);

    set_fill_color(Color::Black);
}

// ==================== Getters ====================
const char* Text::get_text() const {
    return m_strText;
}

int Text::get_size() const {
    return m_sfml_text.getCharacterSize();
}

double Text::get_width() const {
    return m_sfml_text.getLocalBounds().width;
}

double Text::get_height() const {
    return m_sfml_text.getLocalBounds().height;
}
// =================================================

// ==================== Setters ====================
void Text::set_text(const char* text) {
    ASSERT_IF(VALID_PTR(text), "Invalid text ptr", );

    m_strText = text;
    m_sfml_text.setString(text);
}

void Text::set_size(double size) {
    m_sfml_text.setCharacterSize(size);
}
// =================================================

// @virtual
Text& Text::set_fill_color(Color color) {
    Drawable::set_fill_color(color);
    m_sfml_text.setFillColor(color);

    return *this;
}

// @virtual
void Text::draw_impl_(Window& window, const CoordinateSystem& system) {
    Vec2f point = m_mainPoint;
    if (m_centered) {
        point = m_mainPoint - Vec2f(get_width() / 2, get_height() / 2);
    }

    Vec2f pixel = system.point_to_pixel(point);

    if (system.axis_y_direction() == CoordinateSystem::AxisY_Direction::UP)   pixel.y -= get_height() * 1.6;
    else                                                                    pixel.y -= get_height() * 0.3;
    if (system.axis_x_direction() == CoordinateSystem::AxisX_Direction::LEFT) pixel.x -= get_width()  * 1.0;

    m_sfml_text.setPosition(sf::Vector2f(pixel.x, pixel.y));
    get_sfml_window_(window).draw(m_sfml_text);
}

// @virtual
Vec2f Text::center() const {
    return m_mainPoint;
}
