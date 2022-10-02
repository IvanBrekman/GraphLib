//
// Created by IvanBrekman on 28.09.2022
//

#include "../Class_Window/Window.hpp"
#include "../Class_CoordinateSystem/CoordinateSystem.hpp"

#include "PixelMap.hpp"

PixelMap::PixelMap(Point2D main_point, int width, int height)
: Drawable(), Moveable(main_point), width(width), height(height) {
    this->__sfml_pixels = new sf::Uint8[width * height * 4];
    this->__sfml_texture.create(width, height);
}

void PixelMap::set_pixel(int x, int y, Color color) {
    sf::Uint8* pixel = this->__sfml_pixels + (x + y * this->width) * 4;

    pixel[0] = color.r;
    pixel[1] = color.g;
    pixel[2] = color.b;
    pixel[3] = color.a;
}

Color PixelMap::get_pixel(int x, int y) {
    sf::Uint8* pixel = this->__sfml_pixels + (x + y * this->width) * 4;

    return Color(pixel[0], pixel[1], pixel[2], pixel[3]);
}

void PixelMap::draw_impl_(Window& window, const CoordinateSystem& system) {
    if (this->m_hidden) return;

    Point2D pixel = system.point_to_pixel(this->m_mainPoint);
    if (system.axis_y_direction == CoordinateSystem::AxisY_Direction::UP)   pixel.y -= this->height;
    if (system.axis_x_direction == CoordinateSystem::AxisX_Direction::LEFT) pixel.x -= this->width;

    this->__sfml_texture.update(this->__sfml_pixels);

    this->__sfml_sprite = sf::Sprite(this->__sfml_texture);
    this->__sfml_sprite.setPosition(pixel.to_sfml_vector());

    Color color = this->get_pixel(0, 0);
    // printf("%d %d %d %d\n", color.r, color.g, color.b, color.a);

    window.__sfml_window.draw(this->__sfml_sprite);
}

Point2D PixelMap::center() {
    return m_mainPoint;
}
