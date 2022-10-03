//
// Created by IvanBrekman on 28.09.2022
//

#pragma once

#include <SFML/Graphics.hpp>

#include "../Class_Drawable/Drawable.hpp"
#include "../Class_Moveable/Moveable.hpp"
#include "../Class_Point/Point.hpp"

class Window;
class CoordinateSystem;

class PixelMap : public Drawable, public Moveable {
    public:
        int m_width;
        int m_height;
    
    private:
        sf::Uint8*  m_sfml_pixels__;
        sf::Texture m_sfml_texture__;
        sf::Sprite  m_sfml_sprite__;
    
    public:
        PixelMap(Point2D mainPoint,  int width, int height);
        PixelMap(double x, double y, int width, int height)
        : PixelMap(Point2D(x, y), width, height) {}
        
        PixelMap()
        : PixelMap(0, 0, 1, 1) {}

        void  set_pixel(int x, int y,  Color color);
        Color get_pixel(int x, int y);
        
        void load_image(const char* path);

        void draw_impl_(Window& window, const CoordinateSystem& system) override;
        Point2D center() const                                          override;
};
