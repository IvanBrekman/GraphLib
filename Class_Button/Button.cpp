//
// Created by IvanBrekman on 21.09.2022
//

#include "../Class_Utils/baselib.hpp"

#include "../Class_Figures/Figures.hpp"

#include "Button.hpp"

Button::Button(Point2D start_point, double width, double height, Button::Button_Type type)
: start_point(start_point), width(width), height(height), type(type) {
    this->set_button_type(type);
}

bool Button::is_pressed(Point2D point) {
    return this->__shape->contains(point);
}

void Button::move_to(Point2D shift) {
    this->start_point += shift;
    this->set_button_type(this->type);
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
            this->width = this->height;
            this->__shape = new Circle(this->start_point, this->width / 2);
            break;
        
        default:
            ASSERT_IF(0, "Unknown Button_Type value", );
            return;
    }

    this->__shape_color = Color::White;
    this->__shape->set_figure_color(this->__shape_color, Color::Black, 5);
    
    Rectangle* rect = new Rectangle(start_point + Point2D(width / 3, height / 3), width / 3, height / 3);
    rect->set_figure_color(Color::Red);

    this->__drawing_objects.push_back(this->__shape);
    this->__drawing_objects.push_back(rect);
}

void Button::set_button_pressed() {
    this->__shape_color = this->__shape->fill_color;
    this->__shape->set_figure_color(Color::Green, Color::Black, 5);
}

void Button::set_button_released() {
    this->__shape->set_figure_color(this->__shape_color, Color::Black, 5);
}

void Button::draw(Window& window, const CoordinateSystem& system) {
    for (Drawable* object : this->__drawing_objects) {
        object->draw(window, system);
    }
}
