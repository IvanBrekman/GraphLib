//
// Created by IvanBrekman on 16.09.2022
//

#pragma once

#include "../Class_Color/Color.hpp"

class MainWindow;
class CoordinateSystem;

class Drawable {
    public:
        Drawable(Color color);
        Drawable()
        : Drawable(Color::Black) {}

        void show();
        void hide();
        
        void draw(MainWindow& window, const CoordinateSystem& system);
        void draw(MainWindow& window);

        // ==================== Getters ====================
        Color fill_color() const;
        bool  hidden()     const;
        // =================================================

        // ==================== Setters ====================
        virtual Drawable& set_fill_color(Color color);
        virtual Drawable& set_hidden    (bool hidden);
        // =================================================
    
    protected:
        Color m_fillColor;
        bool  m_hidden;

    protected:
        sf::RenderWindow& get_sfml_window_(MainWindow& window);

        virtual void draw_impl_(MainWindow& window, const CoordinateSystem& system) = 0;
};
