//
// Created by IvanBrekman on 24.09.2022
//

#pragma once

#include "../Class_Drawable/Drawable.hpp"
#include "../Class_Point/Point.hpp"

class Window;

class Text : public Drawable, public Moveable {
    public:
        Text(Vec2f mainPoint,    const char* text, size_t size=30);
        Text(double x, double y, const char* text, size_t size=30)
        : Text(Vec2f(x, y), text, size) {}

        // ==================== Getters ====================
        const char* get_text()  const;
        size_t      get_size()  const;

        size_t width()      const;
        size_t height()     const;
        // =================================================

        // ==================== Setters ====================
        void set_text(const char* text);
        void set_size(size_t      size);
        // =================================================

        Text& set_fill_color(Color color)                                override;
        void  draw_impl_(Window& window, const CoordinateSystem& system) override;
        Vec2f center()          const                                    override;
    
    private:
        sf::Text m_sfml_text;
        sf::Font m_sfml_font;

        const char* m_strText;
};
