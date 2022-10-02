//
// Created by IvanBrekman on 17.09.2022
//

#include <cassert>
#include <iostream>

#include "../Class_Utils/baselib.hpp"
#include "../Class_Button/Button.hpp"
#include "../Class_WindowView/WindowView.hpp"

#include "Window.hpp"

Window::Window(int width, int height, const char* text, Color color)
: width(width), height(height), color(color) {
    ASSERT_IF(VALID_PTR(text), "Ivalid text ptr", );

    this->__sfml_window.create(sf::VideoMode(width, height), text, sf::Style::Titlebar | sf::Style::Close);

    this->set_coordinate_system_type(CoordinateSystem::Type::LEFT_UP);
}

Window::~Window() {
    this->close();
}


bool Window::is_open() const {
    return this->__sfml_window.isOpen();
}

bool Window::poll_event(Event* event) {
    ASSERT_IF(VALID_PTR(event), "Invalid event ptr", false);

    bool result = this->__sfml_window.pollEvent(this->__sfml_poll_event);
    if (result == 0) return 0;

    switch (this->__sfml_poll_event.type) {
        case sf::Event::EventType::Closed:
            event->type = Event::Type::WINDOW_CLOSED;
            break;
        
        case sf::Event::EventType::MouseButtonPressed:
            event->type         = Event::Type::MOUSE_BUTTON_PRESSED;
            event->mouse.pos    = event->__get_mouse_button_pos(this->__sfml_poll_event);
            event->mouse.button = (Event::MouseEvent::Button_Type)this->__sfml_poll_event.mouseButton.button;

            for (Button* button : this->__buttons) {
                if (button->is_pressed(this->__coordinate_system.pixel_to_point(event->mouse.pos), event->mouse.button)) {
                    button->set_button_pressed();
                }
            }

            break;
        
        case sf::Event::EventType::MouseButtonReleased:
            event->type         = Event::Type::MOUSE_BUTTON_RELEASED;
            event->mouse.pos    = event->__get_mouse_button_pos(this->__sfml_poll_event);
            event->mouse.button = (Event::MouseEvent::Button_Type)this->__sfml_poll_event.mouseButton.button;

            for (Button* button : this->__buttons) {
                button->set_button_released();
                if (button->is_pressed(this->__coordinate_system.pixel_to_point(event->mouse.pos), event->mouse.button)) {
                    button->set_button_hovered();
                }
            }

            break;
        
        case sf::Event::EventType::MouseMoved:
            event->type      = Event::Type::MOUSE_MOVED;
            event->mouse.pos = event->__get_mouse_move_pos(this->__sfml_poll_event);

            for (Button* button : this->__buttons) {
                if (button->is_pressed(this->__coordinate_system.pixel_to_point(event->mouse.pos), Event::MouseEvent::Button_Type::LEFT)) {
                    button->set_button_hovered();
                } else {
                    button->set_button_released();
                }
            }
            
            break;
          
        default:
            LOG1(printf(RED "Unassembled Event. EventType: %d\n" NATURAL, this->__sfml_poll_event.type););
            break;
    }

    return 1;
}

std::vector <Drawable*>* Window::objects() {
    return &this->__coordinate_system.objects;
}

CoordinateSystem* Window::get_system() {
    return &this->__coordinate_system;
}

void Window::set_coordinate_system(CoordinateSystem system) {
    system.objects = this->__coordinate_system.objects;

    this->__coordinate_system = system;
}

void Window::set_coordinate_system_type(CoordinateSystem::Type type) {
    Window::set_coordinate_system(CoordinateSystem::get_system_by_type(type, this->width, this->height));
}

void Window::draw_window_coordinate_system() {
    bool save = this->__coordinate_system.show_axis;
    this->__coordinate_system.show_axis = true;

    this->__coordinate_system.draw_on_window(*this);

    this->__coordinate_system.show_axis = save;
}

void Window::clear() {
    this->__sfml_window.clear(this->color);
}

void Window::display() {
    this->__sfml_window.display();
}

void Window::close() {
    this->__sfml_window.close();
}

void Window::append_view(WindowView* view) {
    this->__views.push_back(view);

    this->extend_objects(view->objects);
}

void Window::extend_views(std::vector <WindowView*> views) {
    for (WindowView* view : views) {
        this->append_view(view);
    }
}

void Window::show_view(WindowView* view) {
    bool has_view = false;
    for (WindowView* window_view : this->__views) {
        if (window_view == view) has_view = true;
        window_view->set_objects_visibility(true);
    }

    if (!has_view) this->__views.push_back(view);
    view->set_objects_visibility(false);
}

void Window::append_object(Drawable* object, int index) {
    ASSERT_IF(VALID_PTR(object), "Invalid object ptr", );
    
    if (IS_INSTANCE(object, Button*)) {
        this->__buttons.push_back(dynamic_cast<Button*>(object));
    }
    this->__coordinate_system.append_object(object, index);
}

void Window::extend_objects(std::vector <Drawable*> objects, int index) {
    for (Drawable* object : objects) {
        this->append_object(object, index);
    }
}

void Window::draw(Drawable* object) {
    ASSERT_IF(VALID_PTR(object), "Invalid object ptr", );
    
    object->draw(*this, this->__coordinate_system);
}

void Window::draw_added_objects() {
    for (Drawable* object : *this->objects()) {
        this->draw(object);
    }
}
