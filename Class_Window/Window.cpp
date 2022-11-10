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

bool Window::poll_event() {
    bool result = m_sfml_window.pollEvent(m_sfml_pollEvent);
    if (result == 0) return false;

    Event event = Event();
    m_manager.process_event(m_sfml_pollEvent, event);

    if (event.type == Event::Type::WINDOW_CLOSED) close();

    return true;
}

void Window::draw_window_coordinate_system() {
    CoordinateSystem system = m_manager.system();

    bool save = system.show_axis();
    system.set_show_axis(true);

    system.draw(*this);

    system.set_show_axis(save);
}

void Window::clear() {
    m_sfml_window.clear(m_color);
}

void Window::display() {
    draw_added_objects();
    m_sfml_window.display();
}

void Window::close() {
    m_sfml_window.close();
}

void Window::append_view(WindowView* view) {
    m_views.push_back(view);

    extend_objects(view->objects());
}

void Window::extend_views(std::vector<WindowView*> views) {
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

void Window::append_object(Widget* object, int index) {
    ASSERT_IF(VALID_PTR(object), "Invalid object ptr", );

    m_manager.add_widget(object);
}

void Window::extend_objects(std::vector<Widget*> objects, int index) {
    for (Widget* object : objects) {
        append_object(object, index);
    }
}

void Window::draw(Widget* object) {
    ASSERT_IF(VALID_PTR(object), "Invalid object ptr", );
    
    object->draw(*this, m_manager.system());
}

void Window::draw_added_objects() {
    for (Widget* object : objects()) {
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

std::vector<Widget*> Window::objects() const {
    return m_manager.objects();
}

CoordinateSystem Window::coordinate_system() const {
    return m_manager.system();
}
// =================================================

// ==================== Setters ====================
Window& Window::set_color(Color newColor) {
    m_color = newColor;

    return *this;
}

Window& Window::set_coordinate_system(CoordinateSystem system) {
    system.set_objects(m_manager.system().objects());

    m_manager.set_system(system);

    return *this;
}

Window& Window::set_coordinate_system_type(CoordinateSystem::Type type) {
    Window::set_coordinate_system(CoordinateSystem::get_system_by_type(type, m_width, m_height));

    return *this;
}
// =================================================
