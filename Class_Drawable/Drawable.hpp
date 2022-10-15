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
        Drawable(Color color);
        Drawable()
        : Drawable(Color::Black) {}

        void show();
        void hide();
        
        void draw(Window& window, const CoordinateSystem& system);
        void draw(Window& window);

        // ==================== Getters ====================
        Color fill_color() const;
        bool  hidden()     const;
        // =================================================

        // ==================== Setters ====================
        virtual Drawable& set_fill_color(Color color);
        virtual Drawable& set_hidden    (bool hidden);
        // =================================================
    
    protected:
        sf::RenderWindow& get_sfml_window_(Window& window);

        virtual void draw_impl_(Window& window, const CoordinateSystem& system) = 0;

        Color m_fillColor;
        bool  m_hidden;
};
