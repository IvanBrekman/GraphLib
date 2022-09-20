//
// Created by IvanBrekman on 17.09.2022
//

#include <cassert>

#include "../config/baselib.hpp"
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
    bool result = this->__sfml_window.pollEvent(this->__poll_event);
    if (result == 0) return 0;

    switch (this->__poll_event.type) {
        case sf::Event::EventType::Closed:
            event->type = Event::Type::WINDOW_CLOSED;
            break;
        
        default:
            LOG1(printf(RED "Unassembled Event. EventType: %d\n" NATURAL, this->__poll_event.type););
            break;
    }

    return 1;
}

void Window::set_coordinate_system(CoordinateSystem system) {
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
    this->__coordinate_system.draw_on_window(*this);
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
    if (index == Window::__LAST_INDEX) this->objects.push_back(object);
    else                               this->objects.emplace(this->objects.cbegin() + index, object);
}

void Window::extend_objects(std::vector <Drawable*> objects, int index) {
    for (Drawable* object : objects) {
        this->append_object(object);
    }
}

void Window::draw(Drawable* object) {
    if (typeid(*object) == typeid(CoordinateSystem)) {
        ((CoordinateSystem*)object)->draw_on_window(*this);
    } else {
        object->draw(*this, this->__coordinate_system);
    }
}

void Window::draw_added_objects() {
    for (Drawable* object : this->objects) {
        this->draw(object);
    }
}
