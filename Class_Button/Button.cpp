//
// Created by IvanBrekman on 21.09.2022
//

#include <iostream>

#include "../Class_Utils/baselib.hpp"
#include "../Class_Figures/Figures.hpp"

#include "Button.hpp"

Button::Button(Vec2f mainPoint, const char* text, int textSize, Button::Button_Type type)
: Widget(mainPoint, 0, 0), m_type(type), m_text(mainPoint, text, textSize) {
    ASSERT_IF(VALID_PTR(text), "Invalid text ptr", );

    set_fill_color(Color::White);
    set_button_type(type);

    m_width  = width();
    m_height = height();
}

// ==================== Getters ====================
size_t Button::width() const {
    return m_text.width()  + Button::EXTRA_WIDTH;
}

size_t Button::height() const {
    return m_text.height() + Button::EXTRA_HEIGHT;
}
// =================================================

// ==================== Setters ====================
void Button::set_button_type(Button::Button_Type type) {
    switch (type) {
        case Button::Button_Type::DEFAULT:
            m_shape = new Rectangle(m_mainPoint, width(), height());
            break;
        case Button::Button_Type::ELLIPSE:
            m_shape = new Ellipse(m_mainPoint, Vec2f(width() / 2, height() / 2));
            break;
        case Button::Button_Type::CIRCLE:
            m_shape = new Circle(m_mainPoint, width() / 2);
            break;
        
        default:
            ASSERT_IF(0, "Unknown Button_Type value", );
            return;
    }

    m_shape->set_fill_color(m_fillColor, Color::Black, Button::FRAME_WIDTH);
}
// =================================================

// @virtual
bool Button::on_click(const Event& event) {
    if (!Widget::on_click(event)) return false;

    m_shape->set_fill_color(Button::CLICK_COLOR, Button::FRAME_COLOR, Button::FRAME_WIDTH);

    return true;
}

// @virtual
bool Button::on_hover(const Event& event) {
    if (!Widget::on_hover(event)) return false;

    m_shape->set_fill_color(is_clicked() ? Button::CLICK_COLOR : Button::HOVER_COLOR, Button::FRAME_COLOR, Button::FRAME_WIDTH);

    return true;
}

// @virtual
bool Button::on_release(const Event& event) {
    if (!Widget::on_release(event)) return false;

    m_shape->set_fill_color(is_hovered() ? Button::HOVER_COLOR : m_fillColor, Button::FRAME_COLOR, Button::FRAME_WIDTH);

    return true;
}

// @virtual
bool Button::on_unhover(const Event& event) {
    if (!Widget::on_unhover(event)) return false;

    m_shape->set_fill_color(is_clicked() ? Button::CLICK_COLOR : m_fillColor, Button::FRAME_COLOR, Button::FRAME_WIDTH);

    return true;
}

// @virtual
bool Button::contains(Vec2f pixel, CoordinateSystem system) {
    return m_shape->contains(system.pixel_to_point(pixel));
}

// @virtual
void Button::draw_impl_(Window& window, const CoordinateSystem& system) {
    Vec2f shift = Vec2f(0, 0);

    if (m_centered) {
        m_shape->set_centered(true);
        m_text.set_centered(true);
    } else {
        shift = Vec2f(Button::EXTRA_WIDTH / 2.0, system.axis_y_direction() * (Button::EXTRA_HEIGHT / 2.0));
    }

    m_shape->draw_impl_(window, system);

    m_text.move_to_shift( shift);
    m_text.draw(window, system);
    m_text.move_to_shift(-shift);
}

// @virtual
Vec2f Button::center() const {
    if (m_centered) return m_mainPoint;

    return m_mainPoint + Vec2f(width() / 2.0, height() / 2.0);
}
