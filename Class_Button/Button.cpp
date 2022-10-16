//
// Created by IvanBrekman on 21.09.2022
//

#include <iostream>

#include "../Class_Utils/baselib.hpp"
#include "../Class_Figures/Figures.hpp"

#include "Button.hpp"

Button::Button(Vec2f mainPoint, const char* text, int textSize, Button::Button_Type type)
: Moveable(mainPoint), m_type(type), m_text(mainPoint, text, textSize) {
    ASSERT_IF(VALID_PTR(text), "Invalid text ptr", );

    set_fill_color(Color::White);
    set_button_type(type);
}

bool Button::is_pressed(Vec2f point, Event::MouseEvent::Button_Type button) {
    if (m_hidden || button != Event::MouseEvent::Button_Type::LEFT) return false;
    
    return m_shape->contains(point);
}

// ==================== Getters ====================
double Button::width() const {
    return m_text.get_width()  + Button::EXTRA_WIDTH;
}

double Button::height() const {
    return m_text.get_height() + Button::EXTRA_HEIGHT;
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

    m_shapeColor = m_fillColor;
    m_shape->set_fill_color(m_shapeColor, Color::Black, 5);
}

void Button::set_button_pressed() {
    m_shape->set_fill_color(Color::Green,   Color::Black, 5);
}

void Button::set_button_released() {
    m_shape->set_fill_color(m_fillColor,    Color::Black, 5);
}

void Button::set_button_hovered() {
    if (m_shape->fill_color() == Color::Yellow) return;

    m_shapeColor = m_shape->fill_color();
    m_shape->set_fill_color(Color::Yellow,  Color::Black, 5);
}
// =================================================

// @virtual
void Button::draw_impl_(Window& window, const CoordinateSystem& system) {
    Vec2f shift = Vec2f(Button::EXTRA_WIDTH / 2, -m_text.get_height() * Button::EXTRA_TEXT_COEF + Button::EXTRA_HEIGHT / 2);

    if (m_centered) {
        m_shape->set_centered(true);

        shift.x -= width()  / 2;
        shift.y -= height() / 2;
    }

    m_shape->draw_impl_(window, system);

    m_text.move_to_shift( shift);
    m_text.draw(window, system);
    m_text.move_to_shift(-shift);
}

// @virtual
Vec2f Button::center() const {
    if (m_centered) return m_mainPoint;

    return m_mainPoint + Vec2f(width() / 2, height() / 2);
}
