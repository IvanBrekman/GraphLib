//
// Created by IvanBrekman on 16.09.2022
//

#include "../Class_Window/Window.hpp"

#include "Drawable.hpp"

Drawable::Drawable(Color color) {
    m_fillColor = color;
    m_hidden    = false;
}

void Drawable::show() {
    set_hidden(false);
}

void Drawable::hide() {
    set_hidden(true);
}

void Drawable::draw(Window& window, const CoordinateSystem& system) {
    if (!m_hidden) {
        draw_impl_(window, system);
    }
}

void Drawable::draw(Window& window) {
    if (!m_hidden) {
        draw_impl_(window, window.coordinate_system());
    }
}

// ==================== Getters ====================
Color Drawable::fill_color() const {
    return m_fillColor;
}

bool Drawable::hidden() const {
    return m_hidden;
}
// =================================================

// ==================== Setters ====================
// @virtual
Drawable& Drawable::set_fill_color(Color color) {
    m_fillColor = color;

    return *this;
}

// @virtual
Drawable& Drawable::set_hidden(bool hidden) {
    m_hidden = hidden;

    return *this;
}
// =================================================

sf::RenderWindow& Drawable::get_sfml_window_(Window& window) {
    return window.m_sfml_window;
}
