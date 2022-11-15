//
// Created by IvanBrekman on 17.09.2022
//

#include <cassert>
#include <iostream>

#include "../Class_Utils/baselib.hpp"
#include "../Class_Button/Button.hpp"
#include "../Class_WindowView/WindowView.hpp"

#include "Window.hpp"

Window::Window(Vec2f mainPoint, size_t width, size_t height, Window* parent)
: Widget(mainPoint, width, height, parent), m_childrenManager() {
    set_parent(parent);
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

    if (IS_INSTANCE(object, Window*)) dynamic_cast<Window*>(object)->set_parent(this);
    else                                                    object ->set_parent(this);

    m_childrenManager.add_widget(object);
}

void Window::extend_objects(std::vector<Widget*> objects, int index) {
    for (Widget* object : objects) {
        append_object(object, index);
    }
}

// ==================== Getters ====================
Vec2f Window::left_up_pixel() const {
    Vec2f left_up(0, 0);

    if (VALID_PTR(m_parent)) {
        bool xCoef = !(m_parent->m_childrenManager.system().axis_x_direction() + 1);
        bool yCoef = !(m_parent->m_childrenManager.system().axis_y_direction() + 1);

        left_up = m_mainPoint + Vec2f(m_width * xCoef, m_height * yCoef);
        left_up = m_parent->m_childrenManager.system().point_to_pixel(left_up);
    }

    return left_up;
}

std::vector<Widget*> Window::objects() const {
    return m_childrenManager.objects();
}

CoordinateSystem Window::system() const {
    return m_childrenManager.system();
}
// =================================================

// ==================== Setters ====================
Window& Window::set_coordinate_system(CoordinateSystem system) {
    system.set_objects(m_childrenManager.system().objects());

    m_childrenManager.set_system(system);

    return *this;
}

Window& Window::set_coordinate_system_type(CoordinateSystem::Type type) {
    Window::set_coordinate_system(CoordinateSystem::get_system_by_type(type, m_width, m_height, left_up_pixel()));

    return *this;
}

Window& Window::set_parent(Window* parent) {
    Widget::set_parent(parent);

    Vec2f a = system().center();

    CoordinateSystem newSystem = CoordinateSystem(left_up_pixel() + system().center(), system().axis_y_direction(), system().axis_x_direction());
    m_childrenManager.set_system(newSystem);

    return *this;
}
// =================================================

// @virtual
bool Window::on_event(const Event& event, Eventable::Type type) {
    if (!Widget::on_event(event, type)) return false;

    Event e(event);
    e.system = m_childrenManager.system();

    m_childrenManager.trigger_event(e, type);

    return true;
}

// @virtual
Vec2f Window::center() const {
    return m_centered ? m_mainPoint : (m_mainPoint + Vec2f(m_width / 2, m_height / 2));
}

void Window::draw_impl_(MainWindow& window, const CoordinateSystem& system) {
    Rectangle rect = Rectangle(m_mainPoint, m_width, m_height);
    rect.set_fill_color(Color::White, Color::Black, 5);
    if (m_centered) rect.set_centered(true);

    rect.draw(window, system);
}

MainWindow::MainWindow(size_t width, size_t height, const char* text, Color color)
: Window(0, 0, width, height), m_mainManager() {
    ASSERT_IF(VALID_PTR(text), "Ivalid text ptr", );

    m_mainManager.set_system(CoordinateSystem(0, 0));
    m_mainManager.add_widget(this);

    Drawable::set_fill_color(color);
    m_sfml_window.create(sf::VideoMode(width, height), text, sf::Style::Titlebar | sf::Style::Close);

    set_coordinate_system_type(CoordinateSystem::Type::LEFT_UP);
}

MainWindow::~MainWindow() {
    close();
}


bool MainWindow::is_open() const {
    return m_sfml_window.isOpen();
}

bool MainWindow::poll_event() {
    bool result = m_sfml_window.pollEvent(m_sfml_pollEvent);
    if (result == 0) return false;

    Event event = Event();
    m_mainManager.process_event(m_sfml_pollEvent, event);

    if (event.type == Event::Type::WINDOW_CLOSED) close();

    return true;
}

void MainWindow::draw_window_coordinate_system() {
    CoordinateSystem system = m_childrenManager.system();

    bool save = system.show_axis();
    system.set_show_axis(true);

    system.draw(*this);

    system.set_show_axis(save);
}

void MainWindow::clear() {
    m_sfml_window.clear(m_fillColor);
}

void MainWindow::display() {
    draw_added_objects();
    m_sfml_window.display();
}

void MainWindow::close() {
    m_sfml_window.close();
}

void MainWindow::draw(Widget* object) {
    ASSERT_IF(VALID_PTR(object), "Invalid object ptr", );
    
    object->draw(*this, m_childrenManager.system());
}

void MainWindow::draw_added_objects() {
    for (Widget* object : objects()) {
        draw(object);
    }
}
