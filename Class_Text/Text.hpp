//
// Created by IvanBrekman on 24.09.2022
//

#pragma once

#include "../Class_Drawable/Drawable.hpp"
#include "../Class_Point/Point.hpp"

class Window;

class Text : public Drawable, public Moveable {
    private:
        sf::Text m_sfml_text__;
        sf::Font m_sfml_font__;

        const char* m_strText__;
    
    public:
        Text(Point2D mainPoint,  const char* text, int size=30);
        Text(double x, double y, const char* text, int size=30)
        : Text(Point2D(x, y), text, size) {}

        void set_text(const char* text);
        void set_size(double size);

        const char* get_text()  const;
        int         get_size()  const;

        double get_width()      const;
        double get_height()     const;

        void set_fill_color(Color color)                                override;
        void draw_impl_(Window& window, const CoordinateSystem& system) override;
        Point2D center() const                                          override;
};
