//
// Created by IvanBrekman on 16.09.2022
//

#pragma once

#include "../Class_Utils/baselib.hpp"
#include "../Class_Point/Point.hpp"

class Moveable {
    public:
        Moveable(Vec2f mainPoint)
        : m_mainPoint(mainPoint), m_centered(false) {}

        Moveable(double x, double y)
        : Moveable(Vec2f(x, y)) {}

        Moveable()
        : Moveable(0, 0) {}

        // ==================== Getters ====================
        Vec2f main_point() const { return m_mainPoint; }
        bool  centered()   const { return m_centered;  }
        // =================================================

        // ==================== Setters ====================
        Moveable& set_centered(bool centered) { m_centered = centered; return *this; }

        Moveable& move_to_shift(Vec2f shift)      { if (!(IS_INSTANCE(this, Drawable*) && dynamic_cast<Drawable*>(this)->hidden())) move_to_shift_impl_(shift); return *this; }
        Moveable& move_to_point(Vec2f point)      { return move_to_shift(point - main_point());            }
        
        Moveable& move_to_shift(double x, double y) { return move_to_shift(Vec2f(x, y));                  }
        Moveable& move_to_point(double x, double y) { return move_to_shift(Vec2f(x, y) - main_point());    }
        // =================================================

        virtual Vec2f center() const = 0;

        protected:
            Vec2f m_mainPoint;
            bool  m_centered;

        protected:
            virtual void move_to_shift_impl_(Vec2f shift) { m_mainPoint += shift; }
};
