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

double Button::width() {
    return this->__text.get_width()  + Button::__EXTRA_WIDTH;
}

double Button::height() {
    return this->__text.get_height() + Button::__EXTRA_HEIGHT;
}

bool Button::is_pressed(Point2D point, Event::MouseEvent::Button_Type button) {
    if (this->hidden || button != Event::MouseEvent::Button_Type::LEFT) return false;
    
    return this->__shape->contains(point);
}

Point2D Button::center() {
    if (this->centered) return this->main_point;

    return this->main_point + Point2D(this->width() / 2, this->height() / 2);
}

void Button::set_button_type(Button::Button_Type type) {
    switch (type) {
        case Button::Button_Type::DEFAULT:
            this->__shape = new Rectangle(this->main_point, this->width(), this->height());
            break;
        case Button::Button_Type::ELLIPSE:
            this->__shape = new Ellipse(this->main_point, Point2D(this->width() / 2, this->height() / 2));
            break;
        case Button::Button_Type::CIRCLE:
            this->__shape = new Circle(this->main_point, this->width() / 2);
            break;
        
        default:
            ASSERT_IF(0, "Unknown Button_Type value", );
            return;
    }

    this->__shape_color = this->fill_color;
    this->__shape->set_fill_color(this->__shape_color, Color::Black, 5);
}

void Button::set_button_pressed() {
    this->__shape->set_fill_color(Color::Green, Color::Black, 5);
}

void Button::set_button_released() {
    this->__shape->set_fill_color(this->fill_color, Color::Black, 5);
}

void Button::set_button_hovered() {
    if (this->__shape->fill_color == Color::Yellow) return;

    this->__shape_color = this->__shape->fill_color;
    this->__shape->set_fill_color(Color::Yellow, Color::Black, 5);
}

void Button::set_centered() {
    if (this->hidden) return;

    this->centered = true;
}

void Button::draw(Window& window, const CoordinateSystem& system) {
    if (this->hidden) return;

    Point2D shift = Point2D(Button::__EXTRA_WIDTH / 2, -this->__text.get_height() * Button::__EXTRA_TEXT_COEF + Button::__EXTRA_HEIGHT / 2);

    if (this->centered) {
        this->__shape->set_centered();

        shift.x -= this->width()  / 2;
        shift.y -= this->height() / 2;
    }

    this->__shape->draw(window, system);

    this->__text.move_to_shift( shift);
    this->__text.draw(window, system);
    this->__text.move_to_shift(-shift);
}
