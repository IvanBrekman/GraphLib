//
// Created by IvanBrekman on 24.09.2022
//

#include "../Class_Window/Window.hpp"

#include "Text.hpp"

Text::Text(Vec2f mainPoint, const char* text, size_t size)
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

size_t Text::get_size() const {
    return m_sfml_text.getCharacterSize();
}

size_t Text::width() const {
    return (size_t)(m_sfml_text.getLocalBounds().width);
}

size_t Text::height() const {
    return (size_t)(m_sfml_text.getLocalBounds().height);
}
// =================================================

// ==================== Setters ====================
void Text::set_text(const char* text) {
    ASSERT_IF(VALID_PTR(text), "Invalid text ptr", );

    m_strText = text;
    m_sfml_text.setString(text);
}

void Text::set_size(size_t size) {
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
        point = m_mainPoint - Vec2f(width() / 2, height() / 2);
    }

    Vec2f pixel = system.point_to_pixel(point);
    m_mainPoint.dump();
    point.dump();
    pixel.dump();
    printf("\n");

    if (system.axis_y_direction() == CoordinateSystem::AxisY_Direction::UP)   pixel.y -= height() * (m_centered ? 1.4 : 1.7);
    else                                                                      pixel.y -= height() * 0.3;
    if (system.axis_x_direction() == CoordinateSystem::AxisX_Direction::LEFT) pixel.x -= width()  * 1.0;

    m_sfml_text.setPosition(sf::Vector2f(pixel.x, pixel.y));
    get_sfml_window_(window).draw(m_sfml_text);
}

// @virtual
Vec2f Text::center() const {
    return m_mainPoint;
}
