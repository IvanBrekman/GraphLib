//
// Created by IvanBrekman on 09.11.2022
//

#include "../Class_Utils/baselib.hpp"

#include "../Class_Window/Window.hpp"

#include "EventManager.hpp"

EventManager::~EventManager() {
    freeStdVector(m_objects);
}

void EventManager::process_event(sf::Event sfml_event, Event& event) const {
    event.system = m_system;

    switch (sfml_event.type) {
        case sf::Event::EventType::Closed:
            event.type = Event::Type::WINDOW_CLOSED;
            break;
        
        case sf::Event::EventType::MouseButtonPressed:
            event.type         = Event::Type::MOUSE_BUTTON_PRESSED;
            event.mouse.pos    = event.get_mouse_button_pos__(sfml_event);
            event.mouse.button = (Event::MouseEvent::Button_Type)sfml_event.mouseButton.button;

            trigger_click(event);

            break;
        
        case sf::Event::EventType::MouseButtonReleased:
            event.type         = Event::Type::MOUSE_BUTTON_RELEASED;
            event.mouse.pos    = event.get_mouse_button_pos__(sfml_event);
            event.mouse.button = (Event::MouseEvent::Button_Type)sfml_event.mouseButton.button;

            trigger_release(event);

            break;
        
        case sf::Event::EventType::MouseMoved:
            event.type         = Event::Type::MOUSE_MOVED;
            event.mouse.pos    = event.get_mouse_move_pos__(sfml_event);

            trigger_move(event);
            
            break;
          
        default:
            LOGN(3, printf(RED "Unassembled Event. EventType: %d\n" NATURAL, sfml_event.type););
            break;
    }

    trigger_tick(event);
}

void EventManager::trigger_move(const Event& event) const {
    trigger_event(event, Eventable::Type::MOVE);
}

void EventManager::trigger_tick(const Event& event) const {
    trigger_event(event, Eventable::Type::TICK);
}

void EventManager::trigger_click(const Event& event) const {
    trigger_event(event, Eventable::Type::CLICK);
}

void EventManager::trigger_release(const Event& event) const {
    trigger_event(event, Eventable::Type::RELEASE);
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
    m_system.~CoordinateSystem();
    m_system = system;

    return *this;
}
// =================================================

void EventManager::trigger_event(const Event& event, Eventable::Type type) const {
    for (int i = m_objects.size() - 1; i >= 0; i--) {
        Widget* widget = m_objects[i];

        bool res = widget->on_event(event, type);

        if (res && type == Eventable::Type::MOVE) {
            for (i--; i >= 0; i--) {
                widget = m_objects[i];

                if (widget->is_hovered()) widget->on_unhover(event);
            }
        }

        if (res) break;
    }
}
