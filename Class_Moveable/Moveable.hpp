//
// Created by IvanBrekman on 16.09.2022
//

#pragma once

#include "../Class_Utils/baselib.hpp"
#include "../Class_Point/Point.hpp"

class Moveable {
    public:
        Point2D m_mainPoint;
        bool    m_centered;
    
    public:
        Moveable(Point2D mainPoint)
        : m_mainPoint(mainPoint), m_centered(false) {}

        Moveable(double x, double y)
        : Moveable(Point2D(x, y)) {}

        Moveable()
        : Moveable(0, 0) {}

        void set_centered(bool centered) { m_centered = centered; }

        void move_to_shift(Point2D shift)      { if (!(IS_INSTANCE(this, Drawable*) && dynamic_cast<Drawable*>(this)->m_hidden)) move_to_shift_impl_(shift); }
        void move_to_point(Point2D point)      { move_to_shift(point - m_mainPoint);            }
        
        void move_to_shift(double x, double y) { move_to_shift(Point2D(x, y));                  }
        void move_to_point(double x, double y) { move_to_shift(Point2D(x, y) - m_mainPoint);    }

        virtual Point2D center() = 0;

        protected:
            virtual void move_to_shift_impl_(Point2D shift) { m_mainPoint += shift; }
};
