//
// Created by IvanBrekman on 16.09.2022
//

#pragma once

#include <SFML/Graphics.hpp>

#include "../Class_Color/Color.hpp"

// TODO overload draw
// TODO color parameter

class Window;
class CoordinateSystem;

class Drawable {
    public:
        Color fill_color;
        bool  hidden=false;

    public:
        Drawable()
        : fill_color(Color::Black) {};

        virtual void set_fill_color(Color color) { this->fill_color = color; }

        virtual void show() { this->hidden = false; }
        virtual void hide() { this->hidden = true;  }

        virtual void draw          (Window& window, const CoordinateSystem& system) = 0;
        virtual void draw_on_window(Window& window);
};
