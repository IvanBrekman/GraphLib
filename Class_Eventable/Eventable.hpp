//
// Created by IvanBrekman on 03.11.2022
//

#pragma once

#include "../Class_Event/Event.hpp"

#define ON_EVENT_FUNC(captures, code) [captures] (const Event&, const Eventable&) -> void { code }

class Eventable;
using EventFunc_t = std::function<void (const Event&, const Eventable&)>;

static EventFunc_t nothing = [] (const Event&, const Eventable&) -> void { };

class Eventable {
    public:
        enum Type {
            MOVE    = 0,
            TICK    = 1,
            CLICK   = 2,
            HOVER   = 3,
            RELEASE = 4,
            UNHOVER = 5,

            TYPES_NUM,
        };

    public:
        Eventable() {}

        virtual bool on_move   (const Event& event) { return on_event__(event, Type::MOVE   ); }
        virtual bool on_tick   (const Event& event) { return on_event__(event, Type::TICK   ); }
        virtual bool on_click  (const Event& event) { return on_event__(event, Type::CLICK  ); }
        virtual bool on_hover  (const Event& event) { return on_event__(event, Type::HOVER  ); }
        virtual bool on_release(const Event& event) { return on_event__(event, Type::RELEASE); }
        virtual bool on_unhover(const Event& event) { return on_event__(event, Type::UNHOVER); }

        // ==================== Getters ====================
        // =================================================

        // ==================== Setters ====================
        Eventable& set_on_move_func   (EventFunc_t func) { m_funcs[Type::MOVE   ] = func; return *this; }
        Eventable& set_on_tick_func   (EventFunc_t func) { m_funcs[Type::TICK   ] = func; return *this; }
        Eventable& set_on_click_func  (EventFunc_t func) { m_funcs[Type::CLICK  ] = func; return *this; }
        Eventable& set_on_hover_func  (EventFunc_t func) { m_funcs[Type::HOVER  ] = func; return *this; }
        Eventable& set_on_release_func(EventFunc_t func) { m_funcs[Type::RELEASE] = func; return *this; }
        Eventable& set_on_unhover_func(EventFunc_t func) { m_funcs[Type::UNHOVER] = func; return *this; }
        // =================================================
    
    private:
        EventFunc_t m_funcs[Type::TYPES_NUM] = {
            nothing,        // on_move    func
            nothing,        // on_tick    func

            nothing,        // on_click   func
            nothing,        // on_hover   func
            
            nothing,        // on_release func
            nothing,        // on_unhover func
        };
    
    private:
        bool on_event__(const Event& event, Type type) { m_funcs[type](event, *this); return true; }
};
