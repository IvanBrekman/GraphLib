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

    m_sfml_window.create(sf::VideoMode(width, height), text, sf::Style::Titlebar | sf::Style::Close);

    set_coordinate_system_type(CoordinateSystem::Type::LEFT_UP);
}

Window::~Window() {
    close();
}


bool Window::is_open() const {
    return m_sfml_window.isOpen();
}

bool Window::poll_event(Event* event) {
    ASSERT_IF(VALID_PTR(event), "Invalid event ptr", false);

    bool result = m_sfml_window.pollEvent(m_sfml_pollEvent);
    if (result == 0) return 0;

    switch (m_sfml_pollEvent.type) {
        case sf::Event::EventType::Closed:
            event->type = Event::Type::WINDOW_CLOSED;
            break;
        
        case sf::Event::EventType::MouseButtonPressed:
            event->type         = Event::Type::MOUSE_BUTTON_PRESSED;
            event->mouse.pos    = event->get_mouse_button_pos__(m_sfml_pollEvent);
            event->mouse.button = (Event::MouseEvent::Button_Type)m_sfml_pollEvent.mouseButton.button;

            for (Button* button : m_buttons) {
                if (button->is_pressed(m_coordinateSystem.pixel_to_point(event->mouse.pos), event->mouse.button)) {
                    button->set_button_pressed();
                }
            }

            break;
        
        case sf::Event::EventType::MouseButtonReleased:
            event->type         = Event::Type::MOUSE_BUTTON_RELEASED;
            event->mouse.pos    = event->get_mouse_button_pos__(m_sfml_pollEvent);
            event->mouse.button = (Event::MouseEvent::Button_Type)m_sfml_pollEvent.mouseButton.button;

            for (Button* button : m_buttons) {
                button->set_button_released();
                if (button->is_pressed(m_coordinateSystem.pixel_to_point(event->mouse.pos), event->mouse.button)) {
                    button->set_button_hovered();
                }
            }

            break;
        
        case sf::Event::EventType::MouseMoved:
            event->type      = Event::Type::MOUSE_MOVED;
            event->mouse.pos = event->get_mouse_move_pos__(m_sfml_pollEvent);

            for (Button* button : m_buttons) {
                if (button->is_pressed(m_coordinateSystem.pixel_to_point(event->mouse.pos), Event::MouseEvent::Button_Type::LEFT)) {
                    button->set_button_hovered();
                } else {
                    button->set_button_released();
                }
            }
            
            break;
          
        default:
            LOG1(printf(RED "Unassembled Event. EventType: %d\n" NATURAL, m_sfml_pollEvent.type););
            break;
    }

    return 1;
}

void Window::draw_window_coordinate_system() {
    bool save = m_coordinateSystem.show_axis();
    m_coordinateSystem.set_show_axis(true);

    m_coordinateSystem.draw(*this);

    m_coordinateSystem.set_show_axis(save);
}

void Window::clear() {
    m_sfml_window.clear(m_color);
}

void Window::display() {
    m_sfml_window.display();
}

void Window::close() {
    m_sfml_window.close();
}

void Window::append_view(WindowView* view) {
    m_views.push_back(view);

    extend_objects(view->objects());
}

void Window::extend_views(std::vector <WindowView*> views) {
    for (WindowView* view : views) {
        append_view(view);
    }
}

void Window::show_view(WindowView* view) {
    bool has_view = false;
    for (WindowView* window_view : m_views) {
        if (window_view == view) has_view = true;
        window_view->set_hidden(true);
    }

    if (!has_view) m_views.push_back(view);
    view->set_hidden(false);
}

void Window::append_object(Drawable* object, int index) {
    ASSERT_IF(VALID_PTR(object), "Invalid object ptr", );
    
    if (IS_INSTANCE(object, Button*)) {
        m_buttons.push_back(dynamic_cast<Button*>(object));
    }
    m_coordinateSystem.append_object(object, index);
}

void Window::extend_objects(std::vector <Drawable*> objects, int index) {
    for (Drawable* object : objects) {
        append_object(object, index);
    }
}

void Window::draw(Drawable* object) {
    ASSERT_IF(VALID_PTR(object), "Invalid object ptr", );
    
    object->draw(*this, m_coordinateSystem);
}

void Window::draw_added_objects() {
    for (Drawable* object : objects()) {
        draw(object);
    }
}

// ==================== Getters ====================
size_t Window::width() const {
    return m_width;
}

size_t Window::height() const {
    return m_height;
}

Color Window::color() const {
    return m_color;
}

std::vector<Drawable*> Window::objects() const {
    return m_coordinateSystem.objects();
}

CoordinateSystem Window::coordinate_system() const {
    return m_coordinateSystem;
}
// =================================================

// ==================== Setters ====================
Window& Window::set_color(Color newColor) {
    m_color = newColor;

    return *this;
}

Window& Window::set_coordinate_system(CoordinateSystem system) {
    system.set_objects(m_coordinateSystem.objects());

    m_coordinateSystem = system;

    return *this;
}

Window& Window::set_coordinate_system_type(CoordinateSystem::Type type) {
    Window::set_coordinate_system(CoordinateSystem::get_system_by_type(type, m_width, m_height));

    return *this;
}
// =================================================
