//
// Created by IvanBrekman on 21.09.2022
//

#include <iostream>

#include "../Class_Utils/baselib.hpp"
#include "../Class_Figures/Figures.hpp"

#include "Button.hpp"

Button::Button(Point2D mainPoint, const char* text, int textSize, Button::Button_Type type)
: Moveable(mainPoint), m_type(type), m_text__(mainPoint, text, textSize) {
    ASSERT_IF(VALID_PTR(text), "Invalid text ptr", );

    set_fill_color(Color::White);
    set_button_type(type);
}

double Button::width() const {
    return m_text__.get_width()  + Button::EXTRA_WIDTH__;
}

double Button::height() const {
    return m_text__.get_height() + Button::EXTRA_HEIGHT__;
}

bool Button::is_pressed(Point2D point, Event::MouseEvent::Button_Type button) {
    if (m_hidden || button != Event::MouseEvent::Button_Type::LEFT) return false;
    
    return m_shape__->contains(point);
}

void Button::set_button_type(Button::Button_Type type) {
    switch (type) {
        case Button::Button_Type::DEFAULT:
            m_shape__ = new Rectangle(m_mainPoint, width(), height());
            break;
        case Button::Button_Type::ELLIPSE:
            m_shape__ = new Ellipse(m_mainPoint, Point2D(width() / 2, height() / 2));
            break;
        case Button::Button_Type::CIRCLE:
            m_shape__ = new Circle(m_mainPoint, width() / 2);
            break;
        
        default:
            ASSERT_IF(0, "Unknown Button_Type value", );
            return;
    }

    m_shapeColor__ = m_fillColor;
    m_shape__->set_fill_color(m_shapeColor__, Color::Black, 5);
}

void Button::set_button_pressed() {
    m_shape__->set_fill_color(Color::Green,   Color::Black, 5);
}

void Button::set_button_released() {
    m_shape__->set_fill_color(m_fillColor,    Color::Black, 5);
}

void Button::set_button_hovered() {
    if (m_shape__->m_fillColor == Color::Yellow) return;

    m_shapeColor__ = m_shape__->m_fillColor;
    m_shape__->set_fill_color(Color::Yellow,  Color::Black, 5);
}

// @virtual
void Button::draw_impl_(Window& window, const CoordinateSystem& system) {
    Point2D shift = Point2D(Button::EXTRA_WIDTH__ / 2, -m_text__.get_height() * Button::EXTRA_TEXT_COEF__ + Button::EXTRA_HEIGHT__ / 2);

    if (m_centered) {
        m_shape__->set_centered(true);

        shift.x -= width()  / 2;
        shift.y -= height() / 2;
    }

    m_shape__->draw_impl_(window, system);

    m_text__.move_to_shift( shift);
    m_text__.draw(window, system);
    m_text__.move_to_shift(-shift);
}

// @virtual
Point2D Button::center() const {
    if (m_centered) return m_mainPoint;

    return m_mainPoint + Point2D(width() / 2, height() / 2);
}
