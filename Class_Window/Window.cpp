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
: m_width(width), m_height(height), m_color(color) {
    ASSERT_IF(VALID_PTR(text), "Ivalid text ptr", );

    m_sfml_window__.create(sf::VideoMode(width, height), text, sf::Style::Titlebar | sf::Style::Close);

    set_coordinate_system_type(CoordinateSystem::Type::LEFT_UP);
}

Window::~Window() {
    close();
}


bool Window::is_open() const {
    return m_sfml_window__.isOpen();
}

bool Window::poll_event(Event* event) {
    ASSERT_IF(VALID_PTR(event), "Invalid event ptr", false);

    bool result = m_sfml_window__.pollEvent(m_sfml_pollEvent__);
    if (result == 0) return 0;

    switch (m_sfml_pollEvent__.type) {
        case sf::Event::EventType::Closed:
            event->m_type = Event::Type::WINDOW_CLOSED;
            break;
        
        case sf::Event::EventType::MouseButtonPressed:
            event->m_type         = Event::Type::MOUSE_BUTTON_PRESSED;
            event->mouse.m_pos    = event->get_mouse_button_pos__(m_sfml_pollEvent__);
            event->mouse.m_button = (Event::MouseEvent::Button_Type)m_sfml_pollEvent__.mouseButton.button;

            for (Button* button : m_buttons__) {
                if (button->is_pressed(m_coordinateSystem__.pixel_to_point(event->mouse.m_pos), event->mouse.m_button)) {
                    button->set_button_pressed();
                }
            }

            break;
        
        case sf::Event::EventType::MouseButtonReleased:
            event->m_type         = Event::Type::MOUSE_BUTTON_RELEASED;
            event->mouse.m_pos    = event->get_mouse_button_pos__(m_sfml_pollEvent__);
            event->mouse.m_button = (Event::MouseEvent::Button_Type)m_sfml_pollEvent__.mouseButton.button;

            for (Button* button : m_buttons__) {
                button->set_button_released();
                if (button->is_pressed(m_coordinateSystem__.pixel_to_point(event->mouse.m_pos), event->mouse.m_button)) {
                    button->set_button_hovered();
                }
            }

            break;
        
        case sf::Event::EventType::MouseMoved:
            event->m_type      = Event::Type::MOUSE_MOVED;
            event->mouse.m_pos = event->get_mouse_move_pos__(m_sfml_pollEvent__);

            for (Button* button : m_buttons__) {
                if (button->is_pressed(m_coordinateSystem__.pixel_to_point(event->mouse.m_pos), Event::MouseEvent::Button_Type::LEFT)) {
                    button->set_button_hovered();
                } else {
                    button->set_button_released();
                }
            }
            
            break;
          
        default:
            LOG1(printf(RED "Unassembled Event. EventType: %d\n" NATURAL, m_sfml_pollEvent__.type););
            break;
    }

    return 1;
}

std::vector <Drawable*>* Window::objects() {
    return &m_coordinateSystem__.m_objects;
}

CoordinateSystem* Window::get_system() {
    return &m_coordinateSystem__;
}

void Window::set_coordinate_system(CoordinateSystem system) {
    system.m_objects = m_coordinateSystem__.m_objects;

    m_coordinateSystem__ = system;
}

void Window::set_coordinate_system_type(CoordinateSystem::Type type) {
    Window::set_coordinate_system(CoordinateSystem::get_system_by_type(type, m_width, m_height));
}

void Window::draw_window_coordinate_system() {
    bool save = m_coordinateSystem__.m_showAxis;
    m_coordinateSystem__.m_showAxis = true;

    m_coordinateSystem__.draw(*this);

    m_coordinateSystem__.m_showAxis = save;
}

void Window::clear() {
    m_sfml_window__.clear(m_color);
}

void Window::display() {
    m_sfml_window__.display();
}

void Window::close() {
    m_sfml_window__.close();
}

void Window::append_view(WindowView* view) {
    m_views__.push_back(view);

    extend_objects(view->m_objects);
}

void Window::extend_views(std::vector <WindowView*> views) {
    for (WindowView* view : views) {
        append_view(view);
    }
}

void Window::show_view(WindowView* view) {
    bool has_view = false;
    for (WindowView* window_view : m_views__) {
        if (window_view == view) has_view = true;
        window_view->set_objects_visibility(true);
    }

    if (!has_view) m_views__.push_back(view);
    view->set_objects_visibility(false);
}

void Window::append_object(Drawable* object, int index) {
    ASSERT_IF(VALID_PTR(object), "Invalid object ptr", );
    
    if (IS_INSTANCE(object, Button*)) {
        m_buttons__.push_back(dynamic_cast<Button*>(object));
    }
    m_coordinateSystem__.append_object(object, index);
}

void Window::extend_objects(std::vector <Drawable*> objects, int index) {
    for (Drawable* object : objects) {
        append_object(object, index);
    }
}

void Window::draw(Drawable* object) {
    ASSERT_IF(VALID_PTR(object), "Invalid object ptr", );
    
    object->draw(*this, m_coordinateSystem__);
}

void Window::draw_added_objects() {
    for (Drawable* object : *objects()) {
        draw(object);
    }
}
