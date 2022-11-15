//
// Created by IvanBrekman on 28.09.2022
//

#pragma once

#include <SFML/Graphics.hpp>

#include "../Class_Drawable/Drawable.hpp"
#include "../Class_Moveable/Moveable.hpp"
#include "../Class_Point/Point.hpp"

class MainWindow;
class CoordinateSystem;

class PixelMap : public Drawable, public Moveable {
    public:
        PixelMap(Vec2f mainPoint,  int width, int height);
        PixelMap(double x, double y, int width, int height)
        : PixelMap(Vec2f(x, y), width, height) {}
        
        PixelMap()
        : PixelMap(0, 0, 1, 1) {}

        ~PixelMap();

        void  set_pixel(int x, int y,  Color color);
        Color get_pixel(int x, int y);
        
        void load_image(const char* path);

        // ==================== Getters ====================
        size_t width()  const;
        size_t height() const;
        // =================================================

        // ==================== Setters ====================
        // =================================================

        void draw_impl_(MainWindow& window, const CoordinateSystem& system) override;
        Vec2f center()  const                                            override;
    
    private:
        size_t m_width;
        size_t m_height;
        
        sf::Uint8*  m_sfml_pixels;
        sf::Texture m_sfml_texture;
        sf::Sprite  m_sfml_sprite;
};
