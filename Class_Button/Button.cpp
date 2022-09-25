//
// Created by IvanBrekman on 21.09.2022
//

#include <iostream>

#include "../Class_Utils/baselib.hpp"

#include "Button.hpp"

Button::Button(Point2D start_point, const char* text, int text_size, Button::Button_Type type)
: start_point(start_point), text(text), type(type), __text(start_point, text, text_size) {
    this->width  = this->__text.get_width()  + 40;
    this->height = this->__text.get_height() + 10;

    this->__text.move_to(Point2D(20, -13));

    this->set_button_type(type);
}

bool Button::is_pressed(Point2D point) {
    return this->__shape->contains(point);
}

Point2D Button::center() {
    if (this->centered) return this->start_point;

    return this->start_point + Point2D(this->width / 2, this->height / 2);
}

void Button::move_to(Point2D shift) {
    this->start_point += shift;
    this->set_button_type(this->type);
}

void Button::hide() {
    this->set_button_released();
    Drawable::hide();
}

void Button::set_button_type(Button::Button_Type type) {
    switch (type) {
        case Button::Button_Type::DEFAULT:
            this->__shape = new Rectangle(this->start_point, this->width, this->height);
            break;
        case Button::Button_Type::ELLIPSE:
            this->__shape = new Ellipse(this->start_point, Point2D(this->width / 2, this->height / 2));
            break;
        case Button::Button_Type::CIRCLE:
            this->height = this->width;
            this->__shape = new Circle(this->start_point, this->width / 2);
            break;
        
        default:
            ASSERT_IF(0, "Unknown Button_Type value", );
            return;
    }

    this->__shape_color = Color::White;
    this->__shape->set_fill_color(this->__shape_color, Color::Black, 5);

    this->__drawing_objects.clear();

    this->__drawing_objects.push_back(this->__shape);
    this->__drawing_objects.push_back(&this->__text);
}

void Button::set_button_pressed() {
    this->__shape->set_fill_color(Color::Green, Color::Black, 5);
}

void Button::set_button_released() {
    this->__shape->set_fill_color(this->__shape_color, Color::Black, 5);
}

void Button::set_button_hovered() {
    if (this->__shape->fill_color == Color::Yellow) return;

    this->__shape_color = this->__shape->fill_color;
    this->__shape->set_fill_color(Color::Yellow, Color::Black, 5);
}

void Button::draw(Window& window, const CoordinateSystem& system) {
    if (this->hidden) return;

    for (Drawable* object : this->__drawing_objects) {
        object->draw(window, system);
    }
}
