//
// Created by IvanBrekman on 16.09.2022
//

#pragma once

#include <SFML/Graphics.hpp>

#include "../Class_Color/Color.hpp"

class Window;
class CoordinateSystem;

class Drawable {
    public:
        Color color;
        bool  hidden=false;

    public:
        Drawable()
        : color(Color::Black) {};

        virtual void draw(Window& window, const CoordinateSystem& system) = 0;
        virtual void draw_on_window(Window& window);

        void set_color(Color color) { this->color = color; }

        void show() { this->hidden = false; }
        void hide() { this->hidden = true;  }
};
