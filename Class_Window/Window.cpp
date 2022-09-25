//
// Created by IvanBrekman on 17.09.2022
//

#include <cassert>

#include "../Class_Utils/baselib.hpp"
#include "../Class_Button/Button.hpp"

#include "Window.hpp"

Window::Window(int width, int height, const char* text, Color color)
: width(width), height(height), color(color) {
    this->__sfml_window.create(sf::VideoMode(width, height), text);

    this->set_coordinate_system_type(Coordinate_System_Type::LEFT_UP);
}

Window::~Window() {
    this->close();
}


bool Window::is_open() const {
    return this->__sfml_window.isOpen();
}

bool Window::poll_event(Event* event) {
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
                if (button->is_pressed(this->__coordinate_system.pixel_to_point(event->mouse.pos))) {
                    button->set_button_pressed();
                }
            }

            break;
        case sf::Event::EventType::MouseButtonReleased:
            event->type         = Event::Type::MOUSE_BUTTON_RELEASED;
            event->mouse.pos    = event->__get_mouse_button_pos(this->__sfml_poll_event);
            event->mouse.button = (Event::MouseEvent::Button_Type)this->__sfml_poll_event.mouseButton.button;

            for (Button* button : this->__buttons) {
                if (button->is_pressed(this->__coordinate_system.pixel_to_point(event->mouse.pos))) {
                    printf("released!!!\n");
                    button->set_button_released();
                }
            }

            break;
        
        case sf::Event::EventType::MouseMoved:
            event->type      = Event::Type::MOUSE_MOVED;
            event->mouse.pos = event->__get_mouse_move_pos(this->__sfml_poll_event);

            for (Button* button : this->__buttons) {
                if (button->is_pressed(this->__coordinate_system.pixel_to_point(event->mouse.pos))) {
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

void Window::set_coordinate_system_type(Coordinate_System_Type type) {
    switch (type) {
        case Coordinate_System_Type::CENTER:
            Window::set_coordinate_system(CoordinateSystem(this->width / 2, this->height / 2, CoordinateSystem::AxisY_Direction::UP));
            break;
        case Coordinate_System_Type::LEFT_UP:
            Window::set_coordinate_system(CoordinateSystem(0, 0));
            break;
        case Coordinate_System_Type::LEFT_BOTTOM:
            Window::set_coordinate_system(CoordinateSystem(0, this->height, CoordinateSystem::AxisY_Direction::UP));
            break;
        
        default:
            ASSERT_IF(0, "Unknown Coordinate_System_Type value", );
            break;
    }
}

void Window::draw_window_coordinate_system() {
    bool save = this->__coordinate_system.hidden;
    this->__coordinate_system.hidden = false;

    this->__coordinate_system.draw_on_window(*this);

    this->__coordinate_system.hidden = save;
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

void Window::append_object(Drawable* object, int index) {
    if (typeid(*object) == typeid(Button)) {
        printf("Button!\n");
        this->__buttons.push_back((Button*)object);
    }
    this->__coordinate_system.append_object(object, index);
}

void Window::extend_objects(std::vector <Drawable*> objects, int index) {
    for (Drawable* object : objects) {
        this->append_object(object, index);
    }
}

void Window::draw(Drawable* object) {
    if (typeid(*object) == typeid(CoordinateSystem)) {
        ((CoordinateSystem*)object)->draw_on_window(*this);
        ((CoordinateSystem*)object)->draw_added_objects(*this);
    } else {
        object->draw(*this, this->__coordinate_system);
    }
}

void Window::draw_added_objects() {
    for (Drawable* object : *this->objects()) {
        this->draw(object);
    }
}
