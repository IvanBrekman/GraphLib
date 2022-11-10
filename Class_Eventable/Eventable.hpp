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
        Eventable() {}

        virtual bool on_move   (const Event& event) { m_onMoveFunc   (event, *this); return true; }
        virtual bool on_tick   (const Event& event) { m_onTickFunc   (event, *this); return true; }
        virtual bool on_click  (const Event& event) { m_onClickFunc  (event, *this); return true; }
        virtual bool on_hover  (const Event& event) { m_onHoverFunc  (event, *this); return true; }
        virtual bool on_release(const Event& event) { m_onReleaseFunc(event, *this); return true; }
        virtual bool on_unhover(const Event& event) { m_onUnhoverFunc(event, *this); return true; }

        // ==================== Getters ====================
        // =================================================

        // ==================== Setters ====================
        Eventable& set_on_move_func   (EventFunc_t func) { m_onMoveFunc    = func; return *this; }
        Eventable& set_on_tick_func   (EventFunc_t func) { m_onTickFunc    = func; return *this; }
        Eventable& set_on_click_func  (EventFunc_t func) { m_onClickFunc   = func; return *this; }
        Eventable& set_on_hover_func  (EventFunc_t func) { m_onHoverFunc   = func; return *this; }
        Eventable& set_on_release_func(EventFunc_t func) { m_onReleaseFunc = func; return *this; }
        Eventable& set_on_unhover_func(EventFunc_t func) { m_onUnhoverFunc = func; return *this; }
        // =================================================
    
    protected:
        EventFunc_t m_onMoveFunc    = nothing;
        EventFunc_t m_onTickFunc    = nothing;
        EventFunc_t m_onClickFunc   = nothing;
        EventFunc_t m_onHoverFunc   = nothing;
        EventFunc_t m_onReleaseFunc = nothing;
        EventFunc_t m_onUnhoverFunc = nothing;
};
