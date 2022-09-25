//
// Created by IvanBrekman on 24.09.2022
//

#pragma once

#include "../Class_Drawable/Drawable.hpp"
#include "../Class_Point/Point.hpp"

class Window;

class Text : public Drawable, public Moveable {
    public:
        bool centered = false;
    
    private:
        sf::Text __sfml_text;
        sf::Font __sfml_font;

        const char* __str_text;
    
    public:
        Text(Point2D main_point, const char* text, int size=30);
        Text(double x, double y, const char* text, int size=30)
        : Text(Point2D(x, y), text, size) {}

        void set_centered();
        
        void set_text(const char* text);
        void set_size(double size);

        const char* get_text();
        int         get_size();



        double get_width();
        double get_height();

        void set_fill_color(Color color)                          override;
        void draw(Window& window, const CoordinateSystem& system) override;
};
