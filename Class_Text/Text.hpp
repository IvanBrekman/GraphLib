//
// Created by IvanBrekman on 24.09.2022
//

#pragma once

#include "../Class_Drawable/Drawable.hpp"
#include "../Class_Point/Point.hpp"

class Window;

class Text : public Drawable, public Moveable {
    public:
        Text(Vec2f mainPoint,  const char* text, int size=30);
        Text(double x, double y, const char* text, int size=30)
        : Text(Vec2f(x, y), text, size) {}

        // ==================== Getters ====================
        const char* get_text()  const;
        int         get_size()  const;

        double get_width()      const;
        double get_height()     const;
        // =================================================

        // ==================== Setters ====================
        void set_text(const char* text);
        void set_size(double size);
        // =================================================

        Text& set_fill_color(Color color)                                override;
        void  draw_impl_(Window& window, const CoordinateSystem& system) override;
        Vec2f center()          const                                    override;
    
    private:
        sf::Text m_sfml_text;
        sf::Font m_sfml_font;

        const char* m_strText;
};
