//
// Created by IvanBrekman on 16.09.2022
//

#pragma once

#include "../Class_Utils/baselib.hpp"
#include "../Class_Point/Point.hpp"

class Moveable {
    public:
        Point2D main_point;
    
    public:
        Moveable()
        : main_point(0, 0) {}

        Moveable(Point2D main_point)
        : main_point(main_point) {}

        Moveable(double x, double y)
        : main_point(x, y) {}

        virtual void move_to_shift(Point2D shift)      { 
            if (IS_INSTANCE(this, Drawable*) && dynamic_cast<Drawable*>(this)->m_hidden) return;
            this->main_point += shift;                     
        }
                void move_to_point(Point2D point)      { this->move_to_shift(point - this->main_point); }
                
                void move_to_shift(double x, double y) { this->move_to_shift(Point2D(x, y));            }
                void move_to_point(double x, double y) { this->move_to_point(Point2D(x, y));            }
};
