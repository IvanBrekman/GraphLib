//
// Created by IvanBrekman on 24.09.2022
//

#pragma once

#include "../Class_Drawable/Drawable.hpp"
#include "../Class_Point/Point.hpp"

class Window;

class Text : public Drawable {
    public:
        const char* text;
        double      size;

        Point2D     start_point;
    
    private:
        sf::Text __sfml_text;
        sf::Font __sfml_font;
    
    public:
        Text(Point2D start_point, const char* text, int size=30);
        Text(double x, double y,  const char* text, int size=30)
        : Text(Point2D(x, y), text, size) {}

        void move_to(Point2D shift);
        void set_fill_color(Color color) override;
        
        void set_text(const char* text);
        void set_size(double size);

        double get_width();
        double get_height();

        void draw(Window& window, const CoordinateSystem& system);
};
