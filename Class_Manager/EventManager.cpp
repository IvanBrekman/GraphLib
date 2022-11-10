//
// Created by IvanBrekman on 09.11.2022
//

#include "../Class_Utils/baselib.hpp"

#include "EventManager.hpp"

EventManager::~EventManager() {
    freeStdVector(m_objects);
}

void EventManager::process_event(sf::Event sfml_event, Event& event) const {
    switch (sfml_event.type) {
        case sf::Event::EventType::Closed:
            event.type = Event::Type::WINDOW_CLOSED;
            break;
        
        case sf::Event::EventType::MouseButtonPressed:
            event.type         = Event::Type::MOUSE_BUTTON_PRESSED;
            event.mouse.pos    = event.get_mouse_button_pos__(sfml_event);
            event.mouse.button = (Event::MouseEvent::Button_Type)sfml_event.mouseButton.button;
            event.mouse.system = m_system;

            process_click(event);

            break;
        
        case sf::Event::EventType::MouseButtonReleased:
            event.type         = Event::Type::MOUSE_BUTTON_RELEASED;
            event.mouse.pos    = event.get_mouse_button_pos__(sfml_event);
            event.mouse.button = (Event::MouseEvent::Button_Type)sfml_event.mouseButton.button;
            event.mouse.system = m_system;

            process_release(event);

            break;
        
        case sf::Event::EventType::MouseMoved:
            event.type         = Event::Type::MOUSE_MOVED;
            event.mouse.pos    = event.get_mouse_move_pos__(sfml_event);
            event.mouse.system = m_system;

            process_move(event);
            
            break;
          
        default:
            LOGN(3, printf(RED "Unassembled Event. EventType: %d\n" NATURAL, sfml_event.type););
            break;
    }

    process_tick(event);
}

void EventManager::process_move(const Event& event) const {
    for (Widget* widget : m_objects) {
        widget->on_move(event);
    }
}

void EventManager::process_tick(const Event& event) const {
    for (Widget* widget : m_objects) {
        widget->on_tick(event);
    }
}

void EventManager::process_click(const Event& event) const {
    for (Widget* widget : m_objects) {
        widget->on_click(event);
    }
}

void EventManager::process_release(const Event& event) const {
    for (Widget* widget : m_objects) {
        widget->on_release(event);
    }
}

void EventManager::add_widget(Widget* widget) {
    ASSERT_IF(VALID_PTR(widget), "Invalid widget ptr", );

    m_objects.push_back(widget);
}

// ==================== Getters ====================
std::vector<Widget*> EventManager::objects() const {
    return m_objects;
}

CoordinateSystem EventManager::system() const {
    return m_system;
}
// =================================================

// ==================== Setters ====================
EventManager& EventManager::set_system(CoordinateSystem system) {
    m_system = system;

    return *this;
}
// =================================================
