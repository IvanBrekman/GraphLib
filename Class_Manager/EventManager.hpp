//
// Created by IvanBrekman on 03.11.2022
//

#pragma once

#include "../Class_Event/Event.hpp"
#include "../Class_Widget/Widget.hpp"
#include "../Class_CoordinateSystem/CoordinateSystem.hpp"

class EventManager {
    public:
        EventManager()
        : m_objects(), m_system(0, 0) {}

        ~EventManager();

        void process_event(sf::Event sfml_event, Event& event)          const;
        void trigger_event  (const Event& event, Eventable::Type type)  const;

        void trigger_move   (const Event& event)                        const;
        void trigger_tick   (const Event& event)                        const;
        void trigger_click  (const Event& event)                        const;
        void trigger_release(const Event& event)                        const;

        void add_widget(Widget* widget);

        // ==================== Getters ====================
        std::vector<Widget*> objects() const;
        CoordinateSystem     system()  const;
        // =================================================

        // ==================== Setters ====================
        EventManager& set_system(CoordinateSystem system);
        // =================================================
    
    private:
        std::vector<Widget*> m_objects;
        CoordinateSystem     m_system;
};
