//
// Created by IvanBrekman on 21.09.2022
//

#include <iostream>

#include "../Class_Utils/baselib.hpp"
#include "../Class_Figures/Figures.hpp"

#include "Button.hpp"

Button::Button(Point2D main_point, const char* text, int text_size, Button::Button_Type type)
: Moveable(main_point), type(type), __text(main_point, text, text_size) {
    ASSERT_IF(VALID_PTR(text), "Invalid text ptr", );

    this->set_fill_color(Color::White);
    this->set_button_type(type);
}

double Button::width() const {
    return this->__text.get_width()  + Button::__EXTRA_WIDTH;
}

double Button::height() const {
    return this->__text.get_height() + Button::__EXTRA_HEIGHT;
}

bool Button::is_pressed(Point2D point, Event::MouseEvent::Button_Type button) {
    if (this->m_hidden || button != Event::MouseEvent::Button_Type::LEFT) return false;
    
    return this->__shape->contains(point);
}

void Button::set_button_type(Button::Button_Type type) {
    switch (type) {
        case Button::Button_Type::DEFAULT:
            this->__shape = new Rectangle(this->m_mainPoint, this->width(), this->height());
            break;
        case Button::Button_Type::ELLIPSE:
            this->__shape = new Ellipse(this->m_mainPoint, Point2D(this->width() / 2, this->height() / 2));
            break;
        case Button::Button_Type::CIRCLE:
            this->__shape = new Circle(this->m_mainPoint, this->width() / 2);
            break;
        
        default:
            ASSERT_IF(0, "Unknown Button_Type value", );
            return;
    }

    this->__shape_color = this->m_fillColor;
    this->__shape->set_fill_color(this->__shape_color, Color::Black, 5);
}

void Button::set_button_pressed() {
    this->__shape->set_fill_color(Color::Green, Color::Black, 5);
}

void Button::set_button_released() {
    this->__shape->set_fill_color(this->m_fillColor, Color::Black, 5);
}

void Button::set_button_hovered() {
    if (this->__shape->m_fillColor == Color::Yellow) return;

    this->__shape_color = this->__shape->m_fillColor;
    this->__shape->set_fill_color(Color::Yellow, Color::Black, 5);
}

void Button::draw_impl_(Window& window, const CoordinateSystem& system) {
    Point2D shift = Point2D(Button::__EXTRA_WIDTH / 2, -this->__text.get_height() * Button::__EXTRA_TEXT_COEF + Button::__EXTRA_HEIGHT / 2);

    if (this->m_centered) {
        this->__shape->set_centered(true);

        shift.x -= this->width()  / 2;
        shift.y -= this->height() / 2;
    }

    this->__shape->draw(window, system);

    this->__text.move_to_shift( shift);
    this->__text.draw(window, system);
    this->__text.move_to_shift(-shift);
}

Point2D Button::center() const {
    if (this->m_centered) return this->m_mainPoint;

    return this->m_mainPoint + Point2D(this->width() / 2, this->height() / 2);
}
