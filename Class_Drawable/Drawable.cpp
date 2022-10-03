//
// Created by IvanBrekman on 16.09.2022
//

#include "../Class_Window/Window.hpp"

#include "Drawable.hpp"

Drawable::Drawable() {
    m_fillColor = Color::Black;
    m_hidden    = false;
}

// @virtual
void Drawable::set_fill_color(Color color) {
    m_fillColor = color;
}

// @virtual
void Drawable::set_hidden(bool hidden) {
    m_hidden = hidden;
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
        draw(window, window.__coordinate_system);
    }
}

sf::RenderWindow& Drawable::get_sfml_window_(Window& window) {
    return window.__sfml_window;
}
