//
// Created by IvanBrekman on 16.09.2022
//

#pragma once

#include "../Class_Utils/baselib.hpp"
#include "../Class_Point/Point.hpp"

class Moveable {
    public:
        Vec2f m_mainPoint;
        bool    m_centered;
    
    public:
        Moveable(Vec2f mainPoint)
        : m_mainPoint(mainPoint), m_centered(false) {}

        Moveable(double x, double y)
        : Moveable(Vec2f(x, y)) {}

        Moveable()
        : Moveable(0, 0) {}

        void set_centered(bool centered) { m_centered = centered; }

        void move_to_shift(Vec2f shift)      { if (!(IS_INSTANCE(this, Drawable*) && dynamic_cast<Drawable*>(this)->m_hidden)) move_to_shift_impl_(shift); }
        void move_to_point(Vec2f point)      { move_to_shift(point - m_mainPoint);            }
        
        void move_to_shift(double x, double y) { move_to_shift(Vec2f(x, y));                  }
        void move_to_point(double x, double y) { move_to_shift(Vec2f(x, y) - m_mainPoint);    }

        virtual Vec2f center() const = 0;

        protected:
            virtual void move_to_shift_impl_(Vec2f shift) { m_mainPoint += shift; }
};
