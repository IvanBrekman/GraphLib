//
// Created by IvanBrekman on 16.09.2022
//

#pragma once

#include "../Class_Color/Color.hpp"

// TODO color parameter

class Window;
class CoordinateSystem;

class Drawable {
    public:
        Color m_fillColor;
        bool  m_hidden;

    public:
        Drawable();

        virtual void set_fill_color(Color color);
        virtual void set_hidden    (bool hidden);

        void show();
        void hide();
        
        void draw              (Window& window, const CoordinateSystem& system);
        void draw              (Window& window);
    
    protected:
        virtual void draw_impl_(Window& window, const CoordinateSystem& system) = 0;
};
